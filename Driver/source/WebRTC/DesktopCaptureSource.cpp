#include "DesktopCaptureSource.h"

#include "api/scoped_refptr.h"
#include "api/video/i420_buffer.h"
#include "api/video/video_frame_buffer.h"
#include "api/video/video_rotation.h"
#include "rtc_base/checks.h"
#include "third_party/libyuv/include/libyuv.h"
#include "rtc_base/time_utils.h"
#include <iostream>
DesktopCaptureSource::DesktopCaptureSource(std::unique_ptr<webrtc::DesktopCapturer> capturer):
  capturer(std::move(capturer)),
  callback_(std::make_unique<CaptureCallback>(this))
{
  current_status = SourceState::kInitializing;
  fps = 30;
}

DesktopCaptureSource::DesktopCaptureSource(int required_alignment)
    : video_adapter_(required_alignment) {}

DesktopCaptureSource::~DesktopCaptureSource() = default;

void DesktopCaptureSource::Start()
{
  if(running)
  {
    std::cout<<"Capture is already running"<<std::endl;
    return;
  }
  running = true;
  capturer->Start(callback_.get());
  owned_thread = rtc::Thread::Create();
  owned_thread->Start();
  capture_thread = owned_thread.get();
  capture_thread->Start();

  capture_thread->PostTask([this](){
    const int interval_ms = 1000 / fps;
    while (running) {
      capturer->CaptureFrame();
      rtc::Thread::Current()->SleepMs(interval_ms);
    }
  });
  current_status = SourceState::kLive;
  
}

void DesktopCaptureSource::Stop()
{
  running = false;
  if(owned_thread)
  {
    owned_thread->Stop();
    owned_thread.reset();
  }
  capture_thread = nullptr;
  current_status = SourceState::kEnded;
}
bool DesktopCaptureSource::GetStats(Stats* stats) {
  webrtc::MutexLock lock(&stats_mutex_);

  if (!stats_) {
    return false;
  }

  *stats = *stats_;
  return true;
}

void DesktopCaptureSource::OnFrame(const webrtc::VideoFrame& frame) {
  std::cout<<"capture"<<std::endl;

  rtc::scoped_refptr<webrtc::VideoFrameBuffer> buffer(
      frame.video_frame_buffer());
  /* Note that this is a "best effort" approach to
     wants.rotation_applied; apply_rotation_ can change from false to
     true between the check of apply_rotation() and the call to
     broadcaster_.OnFrame(), in which case we generate a frame with
     pending rotation despite some sink with wants.rotation_applied ==
     true was just added. The VideoBroadcaster enforces
     synchronization for us in this case, by not passing the frame on
     to sinks which don't want it. */
  if (apply_rotation() && frame.rotation() != webrtc::kVideoRotation_0 &&
      buffer->type() == webrtc::VideoFrameBuffer::Type::kI420) {
    /* Apply pending rotation. */
    webrtc::VideoFrame rotated_frame(frame);
    rotated_frame.set_video_frame_buffer(
        webrtc::I420Buffer::Rotate(*buffer->GetI420(), frame.rotation()));
    rotated_frame.set_rotation(webrtc::kVideoRotation_0);
    broadcaster_.OnFrame(rotated_frame);
  } else {
    broadcaster_.OnFrame(frame);
  }
}

void DesktopCaptureSource::OnFrameDropped() {
  broadcaster_.OnDiscardedFrame();
}

void DesktopCaptureSource::AddOrUpdateSink(
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink,
    const rtc::VideoSinkWants& wants) {
  broadcaster_.AddOrUpdateSink(sink, wants);
  OnSinkWantsChanged(broadcaster_.wants());
}

void DesktopCaptureSource::RemoveSink(
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) {
  broadcaster_.RemoveSink(sink);
  OnSinkWantsChanged(broadcaster_.wants());
}

bool DesktopCaptureSource::apply_rotation() {
  return broadcaster_.wants().rotation_applied;
}

void DesktopCaptureSource::OnSinkWantsChanged(
    const rtc::VideoSinkWants& wants) {
  video_adapter_.OnSinkWants(wants);
}

bool DesktopCaptureSource::AdaptFrame(int width,
                                         int height,
                                         int64_t time_us,
                                         int* out_width,
                                         int* out_height,
                                         int* crop_width,
                                         int* crop_height,
                                         int* crop_x,
                                         int* crop_y) {
  {
    webrtc::MutexLock lock(&stats_mutex_);
    stats_ = Stats{width, height};
  }

  if (!broadcaster_.frame_wanted()) {
    return false;
  }

  if (!video_adapter_.AdaptFrameResolution(
          width, height, time_us * rtc::kNumNanosecsPerMicrosec, crop_width,
          crop_height, out_width, out_height)) {
    broadcaster_.OnDiscardedFrame();
    // VideoAdapter dropped the frame.
    return false;
  }

  *crop_x = (width - *crop_width) / 2;
  *crop_y = (height - *crop_height) / 2;
  return true;
}

void DesktopCaptureSource::ProcessConstraints(
    const webrtc::VideoTrackSourceConstraints& constraints) {
  broadcaster_.ProcessConstraints(constraints);
}

int64_t DesktopCaptureSource::GetCurrentNtpTimeMs() {
    return rtc::TimeMillis() + 2208988800 * 1000;
}

void DesktopCaptureSource::CaptureCallback::OnCaptureResult(
    webrtc::DesktopCapturer::Result result,
    std::unique_ptr<webrtc::DesktopFrame> frame) {
        if (!frame) {
            return;
        }
                
        const int width = frame->size().width();
        const int height = frame->size().height();
        const uint8_t* src_argb = frame->data();
        const int src_stride = frame->stride();
                
        // 分配 I420 缓冲区
        rtc::scoped_refptr<webrtc::I420Buffer> buffer = webrtc::I420Buffer::Create(width, height);
                
        // ARGB -> I420 转换
        libyuv::ARGBToI420(
            src_argb, src_stride,
            buffer->MutableDataY(), buffer->StrideY(),
            buffer->MutableDataU(), buffer->StrideU(),
            buffer->MutableDataV(), buffer->StrideV(),
            width, height);
                
        int64_t now_us = rtc::TimeMicros();
        int64_t now_ntp_ms = GetCurrentNtpTimeMs();
                
        // 创建并发送 VideoFrame
        webrtc::VideoFrame video_frame = webrtc::VideoFrame::Builder()
            .set_video_frame_buffer(buffer)
            .set_rotation(webrtc::kVideoRotation_0)
            .set_timestamp_us(now_us)
            .set_ntp_time_ms(now_ntp_ms)
            .build();
    source_->OnFrame(std::move(video_frame));
}