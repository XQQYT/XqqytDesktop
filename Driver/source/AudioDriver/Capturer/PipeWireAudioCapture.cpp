#include "PipeWireAudioCapture.h"
#include <spa/param/audio/format-utils.h>
#include <spa/utils/result.h>

int32_t PipeWireAudioCapture::Init() {
    if (initialized_) {
        return 0;
    }

    pw_init(nullptr, nullptr);
    
    loop_ = pw_loop_new(nullptr);
    if (!loop_) {
        fprintf(stderr, "Failed to create PipeWire loop\n");
        return -1;
    }

    context_ = pw_context_new(loop_, nullptr, 0);
    if (!context_) {
        fprintf(stderr, "Failed to create PipeWire context\n");
        pw_loop_destroy(loop_);
        loop_ = nullptr;
        return -1;
    }

    initialized_ = true;
    return 0;
}

int32_t PipeWireAudioCapture::Terminate() {
    if (!initialized_) {
        return 0;
    }

    StopRecording();

    if (stream_) {
        pw_stream_destroy(stream_);
        stream_ = nullptr;
    }

    if (core_) {
        pw_core_disconnect(core_);
        core_ = nullptr;
    }

    if (context_) {
        pw_context_destroy(context_);
        context_ = nullptr;
    }

    if (loop_) {
        pw_loop_destroy(loop_);
        loop_ = nullptr;
    }

    initialized_ = false;
    return 0;
}

bool PipeWireAudioCapture::Initialized() const {
    return initialized_;
}

int32_t PipeWireAudioCapture::RegisterAudioCallback(webrtc::AudioTransport* audioCallback) {
    audio_callback_ = audioCallback;
    return 0;
}

int32_t PipeWireAudioCapture::InitRecording() {
    if (!initialized_) {
        return -1;
    }

    if (stream_) {
        return 0; // Already initialized
    }

    core_ = pw_context_connect(context_, nullptr, 0);
    if (!core_) {
        fprintf(stderr, "Failed to connect PipeWire context\n");
        return -1;
    }

    const char* target_object = "alsa_output.pci-0000_00_1f.3.analog-stereo.monitor";
    const pw_stream_flags stream_flags = static_cast<pw_stream_flags>(
        PW_STREAM_FLAG_AUTOCONNECT | PW_STREAM_FLAG_MAP_BUFFERS
    );
    

    pw_properties* props = pw_properties_new(
        PW_KEY_MEDIA_TYPE, "Audio",
        PW_KEY_MEDIA_CATEGORY, "Capture",
        PW_KEY_MEDIA_ROLE, "Communication",
        PW_KEY_APP_NAME, "PipeWireAudioCapture",
        PW_KEY_NODE_NAME, "webrtc-capture",
        PW_KEY_NODE_TARGET, target_object,
        nullptr
    );

    stream_ = pw_stream_new(core_, "webrtc-capture", props);
    if (!stream_) {
        fprintf(stderr, "Failed to create PipeWire stream\n");
        return -1;
    }

    const spa_pod* params[1];
    uint8_t buffer[1024];
    spa_pod_builder builder = SPA_POD_BUILDER_INIT(buffer, sizeof(buffer));

    // Configure audio format (48kHz, 16-bit, mono)
    struct spa_audio_info_raw audio_info = {
        .format = SPA_AUDIO_FORMAT_S16,
        .flags = 0,
        .rate = 48000,
        .channels = 1,
        .position = { SPA_AUDIO_CHANNEL_MONO }
    };

    params[0] = spa_format_audio_raw_build(&builder, SPA_PARAM_EnumFormat, &audio_info);

    pw_stream_add_listener(stream_, &stream_listener_, &stream_events_, this);
    pw_stream_connect(stream_, PW_DIRECTION_INPUT, PW_ID_ANY, stream_flags, params, 1);

    return 0;
}

int32_t PipeWireAudioCapture::StartRecording() {
    if (recording_ || !stream_) {
        return 0;
    }

    recording_ = true;
    capture_thread_.reset(new std::thread(&PipeWireAudioCapture::CaptureLoop, this));
    return 0;
}

bool PipeWireAudioCapture::RecordingIsInitialized() const {
    return stream_ != nullptr;
}

bool PipeWireAudioCapture::Recording() const {
    return recording_;
}

int32_t PipeWireAudioCapture::RecordingIsAvailable(bool* available) {
    *available = true;
    return 0;
}

void PipeWireAudioCapture::CaptureLoop() {
    const int kSampleRate = 48000;
    const int kChannels = 1;
    const int kBytesPerSample = 2;
    const int kSamplesPer10ms = (kSampleRate / 100);
    const int kBufferSize = kSamplesPer10ms * kBytesPerSample * kChannels;

    while (recording_) {
        pw_loop_iterate(loop_, -1); // Process events with no timeout

        struct pw_buffer* buffer = pw_stream_dequeue_buffer(stream_);
        if (!buffer) {
            continue;
        }

        struct spa_data* data = buffer->buffer->datas;
        if (data[0].chunk->size == 0) {
            pw_stream_queue_buffer(stream_, buffer);
            continue;
        }

        if (audio_callback_) {
            uint32_t newMicLevel = 0;
            audio_callback_->RecordedDataIsAvailable(
                data[0].data,
                kSamplesPer10ms,
                kBytesPerSample,
                kChannels,
                kSampleRate,
                0,      // totalDelayMS
                0,      // clockDrift
                0,      // currentMicLevel
                false,  // keyPressed
                newMicLevel
            );
        }

        pw_stream_queue_buffer(stream_, buffer);
    }
}

// PipeWire stream events callbacks
static void on_stream_state_changed(void* userdata, enum pw_stream_state old, 
                                   enum pw_stream_state state, const char* error) {
    PipeWireAudioCapture* self = static_cast<PipeWireAudioCapture*>(userdata);
    // Handle state changes if needed
}

static void on_stream_param_changed(void* userdata, uint32_t id, 
                                   const struct spa_pod* param) {
    PipeWireAudioCapture* self = static_cast<PipeWireAudioCapture*>(userdata);
    // Handle parameter changes if needed
}

const struct pw_stream_events PipeWireAudioCapture::stream_events_ = {
    PW_VERSION_STREAM_EVENTS,
    .state_changed = on_stream_state_changed,
    .param_changed = on_stream_param_changed,
};