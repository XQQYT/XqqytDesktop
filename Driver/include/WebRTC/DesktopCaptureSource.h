#ifndef _DESKTOPCAPTURESOURCE_H
#define _DESKTOPCAPTURESOURCE_H

#define NDEBUG

#include <stdint.h>

#include "absl/types/optional.h"
#include "api/media_stream_interface.h"
#include "api/notifier.h"
#include "api/video/video_frame.h"
#include "api/video/video_sink_interface.h"
#include "api/video/video_source_interface.h"
#include "media/base/video_adapter.h"
#include "media/base/video_broadcaster.h"
#include "rtc_base/synchronization/mutex.h"
#include "rtc_base/system/rtc_export.h"
#include "rtc_base/thread_annotations.h"
#include "rtc_base/thread.h"
#include "modules/desktop_capture/desktop_capturer.h"
#include "modules/desktop_capture/desktop_capture_options.h"
#include "rtc_base/synchronization/sequence_checker_internal.h"
#include <memory>
#include  <atomic>

class DesktopCaptureSource : public webrtc::Notifier<webrtc::VideoTrackSourceInterface>  {

public:
    DesktopCaptureSource(std::unique_ptr<webrtc::DesktopCapturer> capturer);
    ~DesktopCaptureSource() override;
    inline void setCaptureRate(int rate){fps = rate;}
    void Start();
    void Stop();
    protected:
    bool is_screencast() const{return true;}
    absl::optional<bool> needs_denoising() const {return false;}
    SourceState state() const {return current_status;}
    bool remote() const {return false;}
    // Allows derived classes to initialize `video_adapter_` with a custom
    // alignment.
    explicit DesktopCaptureSource(int required_alignment);
    // Checks the apply_rotation() flag. If the frame needs rotation, and it is a
    // plain memory frame, it is rotated. Subclasses producing native frames must
    // handle apply_rotation() themselves.
    void OnFrame(const webrtc::VideoFrame& frame);
    // Indication from source that a frame was dropped.
    void OnFrameDropped();

    // Reports the appropriate frame size after adaptation. Returns true
    // if a frame is wanted. Returns false if there are no interested
    // sinks, or if the VideoAdapter decides to drop the frame.
    bool AdaptFrame(int width,
                    int height,
                    int64_t time_us,
                    int* out_width,
                    int* out_height,
                    int* crop_width,
                    int* crop_height,
                    int* crop_x,
                    int* crop_y);

    // Returns the current value of the apply_rotation flag, derived
    // from the VideoSinkWants of registered sinks. The value is derived
    // from sinks' wants, in AddOrUpdateSink and RemoveSink. Beware that
    // when using this method from a different thread, the value may
    // become stale before it is used.
    bool apply_rotation();

    cricket::VideoAdapter* video_adapter() { return &video_adapter_; }

private:
    class CaptureCallback;


    static int64_t GetCurrentNtpTimeMs();
    // Implements rtc::VideoSourceInterface.
    void AddOrUpdateSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink,
                        const rtc::VideoSinkWants& wants) override;
    void RemoveSink(rtc::VideoSinkInterface<webrtc::VideoFrame>* sink) override;

    // Part of VideoTrackSourceInterface.
    bool GetStats(Stats* stats) override;

    void OnSinkWantsChanged(const rtc::VideoSinkWants& wants);

    // Encoded sinks not implemented for AdaptedVideoTrackSource.
    bool SupportsEncodedOutput() const override { return false; }
    void GenerateKeyFrame() override {}
    void AddEncodedSink(
        rtc::VideoSinkInterface<webrtc::RecordableEncodedFrame>* sink) override {}
    void RemoveEncodedSink(
        rtc::VideoSinkInterface<webrtc::RecordableEncodedFrame>* sink) override {}
    void ProcessConstraints(
        const webrtc::VideoTrackSourceConstraints& constraints) override;

    cricket::VideoAdapter video_adapter_;

    webrtc::Mutex stats_mutex_;

    absl::optional<Stats> stats_ RTC_GUARDED_BY(stats_mutex_);

    rtc::VideoBroadcaster broadcaster_;

    std::unique_ptr<webrtc::DesktopCapturer> capturer;
    
    std::unique_ptr<CaptureCallback> callback_;

    std::atomic<bool> running{false};

    std::unique_ptr<rtc::Thread> owned_thread;

    rtc::Thread* capture_thread;

    std::atomic<int> fps;

    SourceState current_status;
};

class DesktopCaptureSource::CaptureCallback : public webrtc::DesktopCapturer::Callback {
public:
    explicit CaptureCallback(DesktopCaptureSource* source) : source_(source) {}
    
    void OnFrameCaptureStart() override {}
    
    void OnCaptureResult(webrtc::DesktopCapturer::Result result,
                       std::unique_ptr<webrtc::DesktopFrame> frame) override;

private:
    DesktopCaptureSource* source_;
};

#endif