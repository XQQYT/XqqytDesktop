#ifndef _WEBRTC_H
#define _WEBRTC_H

#include "WebRTCInterface.h"
#include "api/create_peerconnection_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/video_codecs/builtin_video_encoder_factory.h"
#include "api/video_codecs/builtin_video_decoder_factory.h"
#include <iostream>
#include <thread>
#include <vector>
#include "PeerConnectionObserver.h"
#include "DataChannelObserver.h"
#include "Operator.h"
#include "SdpObserver.h"

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
    void initWebRTC();
    void createSDP(SDPType type);
    void setRemoteSDP(std::string remote_sdp, SDPType type);
    void setLocalSDP(webrtc::SessionDescriptionInterface* desc);
    void addIceCandidateIntoBuffer(std::string ice_str,std::string sdp_mid,int sdp_mline_index);
    void startAddIceCandidateIntoPeer();
    void checkConnectionStatus();
public:
    void display_string(std::string event_name,std::string str);
    void display_string_string_string(std::string event_name,std::string str1,std::string str2,std::string str3);
    void display_void(std::string event_name);
    void dispatch_bool(std::string event_name,bool status);
    Role currentRole;
    SetSDPType set_sdp_type;
    bool hasSetRemoteSdp;
    WebRTCInterface::ConnectionStatus ice_status;
    WebRTCInterface::ConnectionStatus peerconnection_status;
    std::unique_ptr<rtc::Thread> signaling_thread;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection;
private:
    void AddIceCandidate(std::string ice_str,std::string sdp_mid,int sdp_mline_index);
private:
    rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel;
    webrtc::PeerConnectionInterface::RTCConfiguration configuration;

    rtc::scoped_refptr<webrtc::AudioTrackInterface> audio_track;
    rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track;

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory;

    std::unique_ptr<rtc::Thread> network_thread;
    std::unique_ptr<rtc::Thread> worker_thread;

    std::unique_ptr<PCO> pco;
    DCO dco;
    rtc::scoped_refptr<SDPO> sdpo;
    rtc::scoped_refptr<SSDO> ssdo;

    std::vector<Ice> ice_candidate_list;

    Operator& webrtc_operator;
};

#endif