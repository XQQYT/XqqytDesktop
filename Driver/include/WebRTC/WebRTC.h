#ifndef _WEBRTC_H
#define _WEBRTC_H

#include "WebRTCInterface.h"
#include "api/create_peerconnection_factory.h"
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
    void createSDP();
    void setRemoteSDP(std::string remote_sdp);
public:
    void display_string(std::string event_name,std::string str);
private:
    bool is_first;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection;
    rtc::scoped_refptr<webrtc::DataChannelInterface> data_channel;
    webrtc::PeerConnectionInterface::RTCConfiguration configuration;

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_connection_factory;

    std::unique_ptr<rtc::Thread> network_thread;
    std::unique_ptr<rtc::Thread> worker_thread;
    std::unique_ptr<rtc::Thread> signaling_thread;

    PCO pco;
    DCO dco;
    rtc::scoped_refptr<SDPO> sdpo;
    rtc::scoped_refptr<SRDO> srdo;

    Operator& webrtc_operator;
};

#endif