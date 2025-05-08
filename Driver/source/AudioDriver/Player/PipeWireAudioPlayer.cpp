#include "PipeWireAudioPlayer.h"
#include <spa/pod/builder.h>
#include <spa/param/format.h>
#include <spa/param/audio/format.h>
#include <algorithm> 
#include <cstdio>
#include <thread>
#include <condition_variable>
#include <iostream>

PipeWireAudioPlayer::PipeWireAudioPlayer() {
    pw_init(nullptr, nullptr);
    loop_ = pw_main_loop_new(nullptr);
    if (!loop_) {
        fprintf(stderr, "Failed to create PipeWire main loop\n");
        return;
    }

    struct pw_properties* props = pw_properties_new(
        PW_KEY_MEDIA_TYPE, "Audio",
        PW_KEY_MEDIA_CATEGORY, "Playback",
        PW_KEY_MEDIA_ROLE, "Communication",
        PW_KEY_APP_NAME, "WebRTCPlayback",
        PW_KEY_NODE_LATENCY, "128/48000",     // 约 2.67ms 延迟
        PW_KEY_NODE_RATE, "48000/1",          // 精确设置采样率
        nullptr
    );

    static const struct pw_stream_events stream_events = {
        .version = PW_VERSION_STREAM_EVENTS,
        .process = PipeWireAudioPlayer::on_process
    };

    stream_ = pw_stream_new_simple(
        pw_main_loop_get_loop(loop_),
        "webrtc-playback",
        props,
        &stream_events,
        this
    );

    if (!stream_) {
        fprintf(stderr, "Failed to create PipeWire stream\n");
        return;
    }

    const struct spa_pod* params[1];
    uint8_t buffer[1024];
    struct spa_pod_builder builder = SPA_POD_BUILDER_INIT(buffer, sizeof(buffer));

    // 设置音频格式参数
    params[0] = (spa_pod*) spa_pod_builder_add_object(&builder,
        SPA_TYPE_OBJECT_Format, SPA_PARAM_EnumFormat,
        SPA_FORMAT_mediaType, SPA_POD_Id(SPA_MEDIA_TYPE_audio),
        SPA_FORMAT_mediaSubtype, SPA_POD_Id(SPA_MEDIA_SUBTYPE_raw),
        SPA_FORMAT_AUDIO_format, SPA_POD_Id(SPA_AUDIO_FORMAT_S16),
        SPA_FORMAT_AUDIO_rate, SPA_POD_Int(48000),
        SPA_FORMAT_AUDIO_channels, SPA_POD_Int(1));

    if (pw_stream_connect(stream_,
                          PW_DIRECTION_OUTPUT,
                          PW_ID_ANY,
                          static_cast<pw_stream_flags>(PW_STREAM_FLAG_AUTOCONNECT |
                                                      PW_STREAM_FLAG_MAP_BUFFERS |
                                                      PW_STREAM_FLAG_RT_PROCESS),
                          params, 1) != 0) {
        fprintf(stderr, "Failed to connect PipeWire stream\n");
        return;
    }

    // 启动主循环线程
    std::thread([this]() {
        pw_main_loop_run(loop_);
    }).detach();
}

void PipeWireAudioPlayer::on_process(void* userdata) {
    PipeWireAudioPlayer* self = static_cast<PipeWireAudioPlayer*>(userdata);
    struct pw_buffer* buffer = pw_stream_dequeue_buffer(self->stream_);
    if (!buffer) return;

    struct spa_buffer* spa_buf = buffer->buffer;
    std::vector<uint8_t> data;

    {
        std::lock_guard<std::mutex> lock(self->buffer_mutex_);
        if(self->audio_queue_.size() > 4)
        {
            while(self->audio_queue_.size() > 4)
                self->audio_queue_.pop();
        }
        if (!self->audio_queue_.empty()) {
            data = std::move(self->audio_queue_.front());
            self->audio_queue_.pop();
        }
    }

    if (!data.empty() && spa_buf->datas[0].data) {
        size_t size_to_copy = std::min(data.size(), static_cast<size_t>(spa_buf->datas[0].maxsize));
        memcpy(spa_buf->datas[0].data, data.data(), size_to_copy);
        spa_buf->datas[0].chunk->size = size_to_copy;
        spa_buf->datas[0].chunk->offset = 0;
        spa_buf->datas[0].chunk->stride = 2; // 16-bit mono
    }

    pw_stream_queue_buffer(self->stream_, buffer);
}


void PipeWireAudioPlayer::OnData(const void* audio_data, int bits_per_sample,
    int sample_rate, size_t number_of_channels,
    size_t number_of_frames) {
    static bool is_first = true;
    if(!is_first)
        return;
    auto now = std::chrono::system_clock::now();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()).count();
        is_first=false;
    std::cout << "[Timestamp] " << millis << " ms since epoch" << std::endl;

    if (!stream_) return;

    size_t bytes_per_sample = bits_per_sample / 8;
    size_t buffer_size = number_of_frames * number_of_channels * bytes_per_sample;

    std::lock_guard<std::mutex> lock(buffer_mutex_);
    audio_queue_.emplace(static_cast<const uint8_t*>(audio_data),
                     static_cast<const uint8_t*>(audio_data) + buffer_size);

}

PipeWireAudioPlayer::~PipeWireAudioPlayer() {
    if (loop_) {
        pw_main_loop_quit(loop_);
        pw_main_loop_destroy(loop_);
    }
    if (stream_) {
        pw_stream_destroy(stream_);
    }
    pw_deinit();
}