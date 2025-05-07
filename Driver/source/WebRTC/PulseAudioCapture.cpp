#include "PulseAudioCapture.h"

int32_t PulseAudioCapture::Init() {
    if (initialized_) {
        return 0;  // 已初始化
    }
    
    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;   // 16-bit little-endian PCM
    ss.rate = 48000;               // 采样率，可根据需求调整
    ss.channels = 1;               // 单声道，可改为 2 表示立体声
    
    int error;
    pa_stream_ = pa_simple_new(
        nullptr,               // 使用默认服务器
        "PulseAudioCapture",   // 应用名称
        PA_STREAM_RECORD,      // 录音
        nullptr,               // 使用默认设备
        "record",              // 流的描述
        &ss,                   // 采样格式
        nullptr,               // 使用默认通道映射
        nullptr,               // 使用默认缓冲区属性
        &error                 // 如果失败，错误码写到这里
    );
    
    if (!pa_stream_) {
        fprintf(stderr, "pa_simple_new() failed: %s\n", pa_strerror(error));
        return -1;
    }
    
    initialized_ = true;
    return 0;
}

int32_t PulseAudioCapture::Terminate()
{
    if (!initialized_) {
        return 0;
    }

    if (pa_stream_) {
        pa_simple_free(pa_stream_);
        pa_stream_ = nullptr;
    }

    initialized_ = false;
    return 0;
}
bool PulseAudioCapture::Initialized() const
{
    return initialized_;
}

int32_t PulseAudioCapture::RegisterAudioCallback(webrtc::AudioTransport* audioCallback) 
{
    audio_callback_ = audioCallback;
    return 0;
}

int32_t PulseAudioCapture::InitRecording() {
    if (recording_ || pa_stream_) {
        return 0;  // 已初始化
    }

    pa_sample_spec ss;
    ss.format = PA_SAMPLE_S16LE;
    ss.rate = 48000;     // WebRTC 默认采样率
    ss.channels = 1;     // 单声道

    int error;

    //系统monitor 设备名称
    const char* device = "alsa_output.pci-0000_00_1f.3.analog-stereo.2.monitor";

    pa_stream_ = pa_simple_new(
        nullptr,                // 使用默认服务器
        "PulseAudioCapture",    // 应用名称
        PA_STREAM_RECORD,       // 我们是要录制（系统声音）
        device,                 // 设备名（monitor）
        "record",               // 流名称
        &ss,                    // 采样规格
        nullptr, nullptr,       // 使用默认配置
        &error
    );

    if (!pa_stream_) {
        fprintf(stderr, "pa_simple_new() failed: %s\n", pa_strerror(error));
        return -1;
    }

    return 0;
}

int32_t PulseAudioCapture::StartRecording() {
    if (recording_) {
        return 0;
    }

    recording_ = true;
    capture_thread_.reset(new std::thread(&PulseAudioCapture::CaptureLoop, this));
    return 0;
}

bool PulseAudioCapture::RecordingIsInitialized() const {
    return pa_stream_ != nullptr;
}

bool PulseAudioCapture::Recording() const {
    return recording_;
}

int32_t PulseAudioCapture::RecordingIsAvailable(bool* available) {
    *available = true;
    return 0;
}

void PulseAudioCapture::CaptureLoop() {
    const int kSampleRate = 48000;
    const int kChannels = 1;
    const int kBytesPerSample = 2;
    const int kSamplesPer10ms = (kSampleRate / 100);  // 480 samples for 10ms @48kHz
    const int kBufferSize = kSamplesPer10ms * kBytesPerSample * kChannels;

    uint8_t buffer[kBufferSize];
    int error;

    while (recording_) {
        if (!pa_stream_) {
            break;
        }

        if (pa_simple_read(pa_stream_, buffer, sizeof(buffer), &error) < 0) {
            fprintf(stderr, "pa_simple_read() failed: %s\n", pa_strerror(error));
            continue;
        }

        if (audio_callback_) {
            uint32_t newMicLevel = 0;
            audio_callback_->RecordedDataIsAvailable(
                static_cast<const void*>(buffer),
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
    }
}