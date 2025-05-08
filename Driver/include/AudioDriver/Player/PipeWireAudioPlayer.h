#pragma once

#include <pipewire/pipewire.h>
#include <mutex>
#include <queue>
#include "api/media_stream_interface.h"

class PipeWireAudioPlayer : public webrtc::AudioTrackSinkInterface {
public:
    PipeWireAudioPlayer();
    ~PipeWireAudioPlayer();

    void OnData(const void* audio_data,
                int bits_per_sample,
                int sample_rate,
                size_t number_of_channels,
                size_t number_of_frames) override;

private:
    struct pw_stream* stream_ = nullptr;
    struct pw_main_loop* loop_ = nullptr;
    static void on_process(void* userdata);
    std::mutex buffer_mutex_;
    std::queue<std::vector<uint8_t>> audio_queue_;
};