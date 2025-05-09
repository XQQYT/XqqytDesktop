// system_audio_device_module.h
#pragma once

#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_device/include/audio_device_defines.h"
#include "rtc_base/thread.h"
#include "rtc_base/ref_counted_object.h"
#include "modules/audio_processing/include/audio_processing.h"

#include <pulse//pulseaudio.h>
#include <pulse/error.h>
#include <thread>
#include <atomic>

class PulseAudioCapture : public webrtc::AudioDeviceModule, public rtc::RefCountInterface{
public:
    PulseAudioCapture(webrtc::AudioDeviceModule::AudioLayer audio_layer,
        webrtc::TaskQueueFactory* task_queue_factory);

    ~PulseAudioCapture() override;
    // Creates a default ADM for usage in production code.
    static rtc::scoped_refptr<AudioDeviceModule> Create(
        AudioLayer audio_layer,
        webrtc::TaskQueueFactory* task_queue_factory)
        {
            return rtc::scoped_refptr<webrtc::AudioDeviceModule>(
                new rtc::RefCountedObject<PulseAudioCapture>(audio_layer, task_queue_factory)
            );
        }

    // Retrieve the currently utilized audio layer
    int32_t ActiveAudioLayer(AudioLayer* audioLayer) const override{return 0;}

    // Full-duplex transportation of PCM audio
    int32_t RegisterAudioCallback(webrtc::AudioTransport* audioCallback) override;

    // Main initialization and termination
    int32_t Init() override;
    int32_t Terminate() override;
    bool Initialized() const override{return initialized_;};

    // Device enumeration
    int16_t PlayoutDevices() override{return 0;};
    int16_t RecordingDevices() override{return 0;};
    int32_t PlayoutDeviceName(uint16_t index,
                                    char name[webrtc::kAdmMaxDeviceNameSize],
                                    char guid[webrtc::kAdmMaxGuidSize]) override{return 0;};
    int32_t RecordingDeviceName(uint16_t index,
                                        char name[webrtc::kAdmMaxDeviceNameSize],
                                        char guid[webrtc::kAdmMaxGuidSize]) override{return 0;};

    // Device selection
    int32_t SetPlayoutDevice(uint16_t index) override{return 0;};
    int32_t SetPlayoutDevice(WindowsDeviceType device) override{return 0;};
    int32_t SetRecordingDevice(uint16_t index) override{return 0;};
    int32_t SetRecordingDevice(WindowsDeviceType device) override{return 0;};

    // Audio transport initialization
    int32_t PlayoutIsAvailable(bool* available) override{return 0;};
    int32_t InitPlayout() override{return 0;};
    bool PlayoutIsInitialized() const override{return false;};
    int32_t RecordingIsAvailable(bool* available) override;
    int32_t InitRecording() override;
    bool RecordingIsInitialized() const override;

    // Audio transport control
    int32_t StartPlayout() override{return 0;};
    int32_t StopPlayout() override{return 0;};
    bool Playing() const override{return false;};
    int32_t StartRecording() override;
    int32_t StopRecording() override;
    bool Recording() const override;

    // Audio mixer initialization
    int32_t InitSpeaker() override{return 0;};
    bool SpeakerIsInitialized() const override{return false;};
    int32_t InitMicrophone() override{return 0;};
    bool MicrophoneIsInitialized() const override{return false;};

    // Speaker volume controls
    int32_t SpeakerVolumeIsAvailable(bool* available) override{return 0;};
    int32_t SetSpeakerVolume(uint32_t volume) override{return 0;};
    int32_t SpeakerVolume(uint32_t* volume) const override{return 0;};
    int32_t MaxSpeakerVolume(uint32_t* maxVolume) const override{return 0;};
    int32_t MinSpeakerVolume(uint32_t* minVolume) const override{return 0;};

    // Microphone volume controls
    int32_t MicrophoneVolumeIsAvailable(bool* available) override{return 0;};
    int32_t SetMicrophoneVolume(uint32_t volume) override{return 0;};
    int32_t MicrophoneVolume(uint32_t* volume) const override{return 0;};
    int32_t MaxMicrophoneVolume(uint32_t* maxVolume) const override{return 0;};
    int32_t MinMicrophoneVolume(uint32_t* minVolume) const override{return 0;};

    // Speaker mute control
    int32_t SpeakerMuteIsAvailable(bool* available) override{return 0;};
    int32_t SetSpeakerMute(bool enable) override{return 0;};
    int32_t SpeakerMute(bool* enabled) const override{return 0;};

    // Microphone mute control
    int32_t MicrophoneMuteIsAvailable(bool* available) override{return 0;};
    int32_t SetMicrophoneMute(bool enable) override{return 0;};
    int32_t MicrophoneMute(bool* enabled) const override{return 0;};

    // Stereo support
    int32_t StereoPlayoutIsAvailable(bool* available) const override{return 0;};
    int32_t SetStereoPlayout(bool enable) override{return 0;};
    int32_t StereoPlayout(bool* enabled) const override{return 0;};
    int32_t StereoRecordingIsAvailable(bool* available) const override{return 0;};
    int32_t SetStereoRecording(bool enable) override{return 0;};
    int32_t StereoRecording(bool* enabled) const override{return 0;};

    // Playout delay
    int32_t PlayoutDelay(uint16_t* delayMS) const override{return 0;};

    // Only supported on Android.
    bool BuiltInAECIsAvailable() const override{return false;};
    bool BuiltInAGCIsAvailable() const override{return false;};
    bool BuiltInNSIsAvailable() const override{return false;};

    // Enables the built-in audio effects. Only supported on Android.
    int32_t EnableBuiltInAEC(bool enable) override{return 0;};
    int32_t EnableBuiltInAGC(bool enable) override{return 0;};
    int32_t EnableBuiltInNS(bool enable) override{return 0;};

    // Play underrun count. Only supported on Android.
    // TODO(alexnarest): Make it abstract after upstream projects support it.
    int32_t GetPlayoutUnderrunCount() const { return -1; }

    // Used to generate RTC stats. If not implemented, RTCAudioPlayoutStats will
    // not be present in the stats.
    absl::optional<Stats> GetStats() const { return absl::nullopt; }


    static void ContextStateCallback(pa_context* context, void* userdata);
    static void StreamStateCallback(pa_stream* stream, void* userdata);
    static void StreamReadCallback(pa_stream* stream, size_t nbytes, void* userdata);
private:

    void CaptureLoop();

    std::atomic<bool> recording_{false};
    std::atomic<bool> initialized_{false};
    webrtc::AudioTransport* audio_callback_ = nullptr;

    webrtc::AudioDeviceModule::AudioLayer audio_layer_;
    webrtc::TaskQueueFactory* task_queue_factory_;

    pa_threaded_mainloop* mainloop_;
    pa_context* context_;
    pa_stream* stream_;

    static rtc::scoped_refptr<webrtc::AudioProcessing> apm_;
};
