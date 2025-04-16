#ifndef _WEBRTC_H
#define _WEBRTC_H


#include "WebRTCInterface.h"
#include "api/create_peerconnection_factory.h"
#include <iostream>
#include <thread>
#include "PeerConnectionObserver.h"
#include "DataChannelObserver.h"
#include "SdpObserver.h"
class WebRTC : public WebRTCInterface
{
public:
    WebRTC();
    void initWebRTC();
    void createSDP();
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
};

#endif