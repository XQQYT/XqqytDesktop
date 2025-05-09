/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#pragma once

#include <pulse/simple.h>
#include <pulse/error.h>
#include "api/media_stream_interface.h"

class PulseAudioPlayer : public webrtc::AudioTrackSinkInterface {
public:
    PulseAudioPlayer();
    ~PulseAudioPlayer();

    void OnData(const void* audio_data,
                int bits_per_sample,
                int sample_rate,
                size_t number_of_channels,
                size_t number_of_frames) override;

private:
    pa_simple* stream_ = nullptr;
};
