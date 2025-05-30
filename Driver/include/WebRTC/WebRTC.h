/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _WEBRTC_H
#define _WEBRTC_H

#include "WebRTCInterface.h"
#include <iostream>
#include <thread>
#include <vector>
#include "PeerConnectionObserver.h"
#include "ControlDataChannelObserver.h"
#include "FileDataChannelObserver.h"
#include "Operator.h"
#include "SdpObserver.h"
#include "DesktopCaptureSource.h"
#include "VideoRender.h"
#include "PulseAudioPlayer.h"
#include "Clipboard.h"
#include "FileSender.h"
#include "FileReceiver.h"

class WebRTC : public WebRTCInterface
{
public:
    struct Ice{
        Ice(std::string ice, std::string mid, int index)
        : ice_str(std::move(ice)), sdp_mid(std::move(mid)), sdp_mline_index(index) {}
        std::string ice_str;
        std::string sdp_mid;
        int sdp_mline_index;
    };
public:
    WebRTC(Operator& base_operator);
    ~WebRTC();
    void initWebRTC(bool is_offer) override;
    void createSDP(SDPType type) override;
    void setRemoteSDP(std::string remote_sdp, SDPType type) override;
    void setLocalSDP(webrtc::SessionDescriptionInterface* desc);
    void addIceCandidateIntoBuffer(std::string ice_str,std::string sdp_mid,int sdp_mline_index) override;
    void startAddIceCandidateIntoPeer();
    void checkConnectionStatus();
    void startCaptureDesktop() override;
    void stopCaptureDesktop() override;
    void setRenderInstance(RenderInterface* instance) override;
    void sendMouseEventPacket(const MouseEventPacket packet) override;
    void sendClipboardContent(std::string content);
    void sendKeyboardEventPacket(const KeyEventPacket packet) override;
    void closeWebRTC() override;
    bool getWebRtcReady() override;
    void setCaptureRate(int rate) override;
    void writeIntoClipboard(std::string str) override;
    void setSyncMsgCallback(std::function<void(std::string)> callback) override;
    void sendFileSync(std::string msg) override;
    void sendToPeer(uint8_t* msg, size_t length);
    void sendToPeer(std::string msg);
    void sendFile(uint16_t id,const std::string path) override;
    void setFileHolder(std::shared_ptr<std::ofstream> out) override;
    void setReceiveFileProgressCb(std::function<void(uint16_t,uint32_t,uint32_t)> cb) override;
public:
    void display_string(EventBus::EventType event_name,std::string str);
    void display_string_string_string(EventBus::EventType event_name,std::string str1,std::string str2,std::string str3);
    void display_void(EventBus::EventType event_name);
    void dispatch_bool(EventBus::EventType event_name,bool status);
    Role currentRole;
    SetSDPType set_sdp_type;
    bool hasSetRemoteSdp;
    WebRTCInterface::ConnectionStatus ice_status;
    WebRTCInterface::ConnectionStatus peerconnection_status;
    std::unique_ptr<rtc::Thread> signaling_thread;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection;
    rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> desktop_source;
    std::unique_ptr<VideoRender> video_render;
    rtc::scoped_refptr<webrtc::DataChannelInterface> control_data_channel;
    rtc::scoped_refptr<webrtc::DataChannelInterface> file_data_channel;

    std::unique_ptr<ControlDCO> control_dco;
    std::unique_ptr<FileDCO> file_dco;

    std::unique_ptr<PulseAudioPlayer> audio_player;
    std::unique_ptr<ClipboardInterface> clipboard_driver;
    std::function<void(std::string)> sync_file_callback;
    std::unique_ptr<FileSender> file_sender;
    std::unique_ptr<FileReceiver> file_receiver;
private:
    void AddIceCandidate(std::string ice_str,std::string sdp_mid,int sdp_mline_index);
    void sendCloseWebRTC();
private:
    webrtc::PeerConnectionInterface::RTCConfiguration configuration;
    rtc::scoped_refptr<webrtc::AudioDeviceModule> adm;

    rtc::scoped_refptr<webrtc::AudioTrackInterface> desktop_audio_track;
    rtc::scoped_refptr<webrtc::VideoTrackInterface> desktop_video_track;

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory;

    std::unique_ptr<rtc::Thread> network_thread;
    std::unique_ptr<rtc::Thread> worker_thread;

    std::unique_ptr<PCO> pco;
    rtc::scoped_refptr<SDPO> sdpo;
    rtc::scoped_refptr<SSDO> ssdo;

    std::vector<Ice> ice_candidate_list;

    Operator& webrtc_operator;
    bool webrtc_ready;

    int webrtc_capture_rate;

};

#endif