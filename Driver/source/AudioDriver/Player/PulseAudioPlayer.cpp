/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "PulseAudioPlayer.h"
#include <cstdio>

PulseAudioPlayer::PulseAudioPlayer() {
    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 48000;
    ss.channels = 1;

    pa_buffer_attr buffer_attr;
    buffer_attr.maxlength = (uint32_t)-1;
    buffer_attr.tlength = 48000 * 2 * 1 / 100;  // 10ms (480 samples * 2 bytes)
    buffer_attr.prebuf = 0;
    buffer_attr.minreq = (uint32_t)-1;
    buffer_attr.fragsize = (uint32_t)-1;

    int error;
    stream_ = pa_simple_new(nullptr, "WebRTCPlayback", PA_STREAM_PLAYBACK,
                            nullptr, "playback", &ss, nullptr, &buffer_attr, &error);
    if (!stream_) {
        fprintf(stderr, "pa_simple_new() failed for playback: %s\n", pa_strerror(error));
    }
}

void PulseAudioPlayer::OnData(const void* audio_data, int bits_per_sample,
                               int sample_rate, size_t number_of_channels,
                               size_t number_of_frames) {
    if (!stream_) return;

    size_t bytes_per_sample = bits_per_sample / 8;
    size_t buffer_size = number_of_frames * number_of_channels * bytes_per_sample;

    int error;
    if (pa_simple_write(stream_, audio_data, buffer_size, &error) < 0) {
        fprintf(stderr, "pa_simple_write() failed: %s\n", pa_strerror(error));
    }
}

PulseAudioPlayer::~PulseAudioPlayer() {
    if (stream_) {
        pa_simple_drain(stream_, nullptr);
        pa_simple_free(stream_);
    }
}
