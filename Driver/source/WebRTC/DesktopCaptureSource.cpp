#include "DesktopCaptureSource.h"

DesktopCaptureSource::DesktopCaptureSource(std::unique_ptr<webrtc::DesktopCapturer> capturer)
    : capturer(std::move(capturer)) {}

DesktopCaptureSource::~DesktopCaptureSource() {
    capturing = false;
    if (capture_thread) {
        capture_thread->Stop();
    }
}

void DesktopCaptureSource::Start() {
    capturing = true;
    callback = std::make_unique<CaptureCallback>(this);
    capturer->Start(callback.get());

    owned_capture_thread = rtc::Thread::Create();
    owned_capture_thread->SetName("ScreenCaptureThread", nullptr);
    owned_capture_thread->Start();
    capture_thread = owned_capture_thread.get();

    capture_thread->PostTask([this]() {
        const int fps = 30;
        const int interval_ms = 1000 / fps;
        while (capturing) {
            capturer->CaptureFrame();
            rtc::Thread::Current()->SleepMs(interval_ms);
        }
    });
}

void DesktopCaptureSource::Stop()
{
    capturing = false;
    if (capture_thread) {
        capture_thread->Stop();
    }
}

void DesktopCaptureSource::OnCapturedFrame(const webrtc::VideoFrame& frame) {
    webrtc::MutexLock lock(&sink_mutex);
    if (sink) {
        sink->OnFrame(frame);  // 将帧传递给 WebRTC 内部处理
    }
}

// CaptureCallback 实现保持不变
void DesktopCaptureSource::CaptureCallback::OnFrameCaptureStart() {}

int64_t DesktopCaptureSource::CaptureCallback::GetCurrentNtpTimeMs() {
    // 当前系统时间（ms）
    int64_t now_ms = rtc::TimeMillis();

    // 转换为 NTP 时间戳（我们估算为当前 ms + 1900 到 1970 的差距）
    const int64_t kUnixEpochInNtpMs = 2208988800000LL;  // 1900 to 1970 in ms
    return now_ms + kUnixEpochInNtpMs;
}

void DesktopCaptureSource::CaptureCallback::OnCaptureResult(
    webrtc::DesktopCapturer::Result result,
    std::unique_ptr<webrtc::DesktopFrame> frame) 
{
    if (result != webrtc::DesktopCapturer::Result::SUCCESS || !frame) {
        // std::cout << "Capture failed."<<std::endl;
        return;
    }
            
    const int width = frame->size().width();
    const int height = frame->size().height();
    const uint8_t* src_argb = frame->data();
    const int src_stride = frame->stride();
            
    // 分配 I420 缓冲区
    rtc::scoped_refptr<webrtc::I420Buffer> buffer = webrtc::I420Buffer::Create(width, height);
            
    // ARGB -> I420
    libyuv::ARGBToI420(
        src_argb, src_stride,
        buffer->MutableDataY(), buffer->StrideY(),
        buffer->MutableDataU(), buffer->StrideU(),
        buffer->MutableDataV(), buffer->StrideV(),
        width, height);
    int64_t now_us = rtc::TimeMicros();
    int64_t now_ntp_ms = GetCurrentNtpTimeMs();
    // 创建 VideoFrame
    webrtc::VideoFrame frame_i420 = webrtc::VideoFrame::Builder()
        .set_video_frame_buffer(buffer)
        .set_rotation(webrtc::kVideoRotation_0)
        .set_timestamp_us(now_us)  // 时间戳基于系统时间
        .set_ntp_time_ms(now_ntp_ms) // 设置 NTP 时间
        .build();
    source->OnCapturedFrame(frame_i420);
}