#include <pulse/pulseaudio.h>
#include <iostream>
#include <thread>
#include <atomic>
#include <cstring>
#include "PulseAudioCapture.h"

rtc::scoped_refptr<webrtc::AudioProcessing> PulseAudioCapture::apm_ = nullptr;

PulseAudioCapture::PulseAudioCapture(webrtc::AudioDeviceModule::AudioLayer audio_layer,
    webrtc::TaskQueueFactory* task_queue_factory)
    : mainloop_(nullptr), context_(nullptr), stream_(nullptr),
      initialized_(false), recording_(false), audio_callback_(nullptr),
      audio_layer_(audio_layer), task_queue_factory_(task_queue_factory) {
        initialized_ = false;
        recording_ = false;
      }

PulseAudioCapture::~PulseAudioCapture() {
    Terminate();
}

int32_t PulseAudioCapture::Init() {
    if (initialized_) return 0;

    mainloop_ = pa_threaded_mainloop_new();
    if (!mainloop_) return -1;

    context_ = pa_context_new(pa_threaded_mainloop_get_api(mainloop_), "PulseAudioCapture");
    if (!context_) return -1;

    pa_context_set_state_callback(context_, &PulseAudioCapture::ContextStateCallback, this);

    if (pa_context_connect(context_, nullptr, PA_CONTEXT_NOFLAGS, nullptr) < 0) {
        std::cerr << "pa_context_connect() failed" << std::endl;
        return -1;
    }

    pa_threaded_mainloop_start(mainloop_);
    pa_threaded_mainloop_lock(mainloop_);
    while (true) {
        auto state = pa_context_get_state(context_);
        if (state == PA_CONTEXT_READY) break;
        if (!PA_CONTEXT_IS_GOOD(state)) {
            pa_threaded_mainloop_unlock(mainloop_);
            return -1;
        }
        pa_threaded_mainloop_wait(mainloop_);
    }
    pa_threaded_mainloop_unlock(mainloop_);
    initialized_ = true;
    return 0;
}

int32_t PulseAudioCapture::Terminate() {
    if (!initialized_) return 0;
    StopRecording();

    pa_threaded_mainloop_lock(mainloop_);
    if (stream_) {
        pa_stream_disconnect(stream_);
        pa_stream_unref(stream_);
        stream_ = nullptr;
    }
    if (context_) {
        pa_context_disconnect(context_);
        pa_context_unref(context_);
        context_ = nullptr;
    }
    pa_threaded_mainloop_unlock(mainloop_);

    pa_threaded_mainloop_stop(mainloop_);
    pa_threaded_mainloop_free(mainloop_);
    mainloop_ = nullptr;
    initialized_ = false;
    return 0;
}

int32_t PulseAudioCapture::RegisterAudioCallback(webrtc::AudioTransport* audioCallback) {
    audio_callback_ = audioCallback;
    return 0;
}

int32_t PulseAudioCapture::InitRecording() {
    if (!initialized_ || stream_) return 0;

    apm_ = webrtc::AudioProcessingBuilder().Create();
    webrtc::AudioProcessing::Config config;
    config.echo_canceller.enabled = true;
    config.noise_suppression.enabled = true;
    config.noise_suppression.level = webrtc::AudioProcessing::Config::NoiseSuppression::kHigh;
    apm_->ApplyConfig(config);

    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 48000;
    ss.channels = 1;

    pa_buffer_attr attr;
    attr.maxlength = 960*4;        // 40ms缓冲区
    attr.tlength = 960;            // 10ms目标长度
    attr.prebuf = 0;
    attr.minreq = 960;             // 10ms最小请求
    attr.fragsize = 960;           // 10ms片段大小

    const char* device = "alsa_output.pci-0000_00_1f.3.analog-stereo.2.monitor";

    pa_threaded_mainloop_lock(mainloop_);
    stream_ = pa_stream_new(context_, "CaptureStream", &ss, nullptr);
    if (!stream_) {
        pa_threaded_mainloop_unlock(mainloop_);
        return -1;
    }

    pa_stream_set_read_callback(stream_, &PulseAudioCapture::StreamReadCallback, this);
    pa_stream_set_state_callback(stream_, &PulseAudioCapture::StreamStateCallback, this);

    if (pa_stream_connect_record(stream_, device, &attr, PA_STREAM_ADJUST_LATENCY) < 0) {
        std::cerr << "Failed to connect record stream." << std::endl;
        pa_threaded_mainloop_unlock(mainloop_);
        return -1;
    }

    while (true) {
        auto state = pa_stream_get_state(stream_);
        if (state == PA_STREAM_READY) break;
        if (!PA_STREAM_IS_GOOD(state)) {
            pa_threaded_mainloop_unlock(mainloop_);
            return -1;
        }
        pa_threaded_mainloop_wait(mainloop_);
    }

    pa_threaded_mainloop_unlock(mainloop_);
    return 0;
}

int32_t PulseAudioCapture::StartRecording() {
    if (recording_ || !stream_) return 0;
    recording_ = true;
    return 0;
}

int32_t PulseAudioCapture::StopRecording() {
    if (!recording_) return 0;
    recording_ = false;
    return 0;
}

bool PulseAudioCapture::Recording() const {
    return recording_;
}

bool PulseAudioCapture::RecordingIsInitialized() const {
    return stream_ != nullptr;
}

int32_t PulseAudioCapture::RecordingIsAvailable(bool* available) {
    *available = true;
    return 0;
}

// --- Callbacks ---

void PulseAudioCapture::ContextStateCallback(pa_context* context, void* userdata) {
    auto* self = static_cast<PulseAudioCapture*>(userdata);
    pa_context_state_t state = pa_context_get_state(context);
    if (state == PA_CONTEXT_READY || !PA_CONTEXT_IS_GOOD(state)) {
        pa_threaded_mainloop_signal(self->mainloop_, 0);
    }
}

void PulseAudioCapture::StreamStateCallback(pa_stream* stream, void* userdata) {
    auto* self = static_cast<PulseAudioCapture*>(userdata);
    pa_threaded_mainloop_signal(self->mainloop_, 0);
}

void PulseAudioCapture::StreamReadCallback(pa_stream* stream, size_t nbytes, void* userdata) {
    auto* self = static_cast<PulseAudioCapture*>(userdata);
    if (!self->recording_ || !self->audio_callback_) return;

    const void* data;
    if (pa_stream_peek(stream, &data, &nbytes) < 0 || !data || nbytes == 0)
        return;
    webrtc::StreamConfig stream_config(48000, 1);
    apm_->ProcessStream(
        static_cast<int16_t*>(const_cast<void*>(data)),
        stream_config,
        stream_config,
        static_cast<int16_t*>(const_cast<void*>(data))
    );
    const int kBytesPerSample = 2;
    const int kChannels = 1;
    const int samples = nbytes / (kBytesPerSample * kChannels);

    uint32_t newMicLevel = 0;
    self->audio_callback_->RecordedDataIsAvailable(
        data, samples, kBytesPerSample, kChannels,
        48000, 0, 0, 0, false, newMicLevel
    );

    pa_stream_drop(stream);
}
