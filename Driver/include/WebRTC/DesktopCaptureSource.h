#ifndef _DESKTOPCAPTURESOURCE_H
#define _DESKTOPCAPTURESOURCE_H

#include "api/media_stream_interface.h"
#include "api/video/video_source_interface.h"
#include "media/base/adapted_video_track_source.h"
#include "modules/desktop_capture/desktop_capturer.h"
#include "rtc_base/thread.h"
#include "api/video/i420_buffer.h"
#include "third_party/libyuv/include/libyuv.h"
#include <memory>

class DesktopCaptureSource : public webrtc::VideoTrackSourceInterface {
public:
    explicit DesktopCaptureSource(std::unique_ptr<webrtc::DesktopCapturer> capturer);
    ~DesktopCaptureSource() override;

    // VideoSourceInterface 必须实现的接口
    // void AddOrUpdateSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink,
    //                     const rtc::VideoSinkWants& wants) override;
    // void RemoveSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) override;
    bool is_screencast() const override{return true;}
    absl::optional<bool> needs_denoising() const override{return false;};
    bool GetStats(Stats* stats) override{return false;};
    bool SupportsEncodedOutput() const override{return false;};
    void GenerateKeyFrame() override{};
    void AddEncodedSink(rtc::VideoSinkInterface<webrtc::RecordableEncodedFrame>* sink) override{};
    void RemoveEncodedSink(rtc::VideoSinkInterface<webrtc::RecordableEncodedFrame>* sink) override{};

    // 自定义方法
    void Start();
    void Stop();
    void OnCapturedFrame(const webrtc::VideoFrame& frame);

private:
    class CaptureCallback;

    std::unique_ptr<webrtc::DesktopCapturer> capturer;
    std::unique_ptr<CaptureCallback> callback;
    rtc::Thread* capture_thread;
    std::unique_ptr<rtc::Thread> owned_capture_thread;
    
    // 用于管理视频接收器
    rtc::VideoSinkInterface<webrtc::VideoFrame>* sink = nullptr;
    webrtc::Mutex sink_mutex;
    std::atomic<bool> capturing{false};
};

class DesktopCaptureSource::CaptureCallback : public webrtc::DesktopCapturer::Callback {
public:
    explicit CaptureCallback(DesktopCaptureSource* source) : source(source) {}
    void OnFrameCaptureStart() override;
    void OnCaptureResult(webrtc::DesktopCapturer::Result result,
                       std::unique_ptr<webrtc::DesktopFrame> frame) override;
private:
    static int64_t GetCurrentNtpTimeMs();

    DesktopCaptureSource* source;
};

#endif