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
#include "PeerConnectionObserver.h"
#include "DataChannelObserver.h"
#include "Operator.h"
#include "SdpObserver.h"

class WebRTC : public WebRTCInterface
{
public:
    WebRTC(Operator& base_operator);
    void initWebRTC();
    void createSDP(SDPType type);
    void setRemoteSDP(std::string remote_sdp);
    void setLocalSDP(webrtc::SessionDescriptionInterface* desc);
public:
    void display_string(std::string event_name,std::string str);
    void display_void(std::string event_name);
    Role currentRole;
    std::unique_ptr<rtc::Thread> signaling_thread;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection;
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

    Operator& webrtc_operator;
};

#endif