#include "WebrtcController.h"

WebrtcController::WebrtcController()
{
    webrtc_instance = std::make_unique<WebRTC>(*this);
}

void WebrtcController::initWebrtcSubscribe()
{
    EventBus::getInstance().subscribe("/network/registration_successed",std::bind(
        &WebrtcController::onInitWebrtc,
        this
    ));
    EventBus::getInstance().subscribe("/network/recv_connect_request_result",std::bind(
        &WebrtcController::createSDP,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/recv_sdp_offer",std::bind(
        &WebrtcController::recvSDPOffer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/recv_sdp_answer",std::bind(
        &WebrtcController::recvSDPAnswer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/set_remote_sdp_offer_done",std::bind(
        &WebrtcController::onSetRemoteSDPOfferDone,
        this
    ));
}

void WebrtcController::onInitWebrtc()
{
    webrtc_instance->initWebRTC();
}

//The peer accept the connection request
void WebrtcController::createSDP(bool status)
{
    if(status)
        webrtc_instance->createSDP(WebRTCInterface::SDPType::OFFER);
}

void WebrtcController::onSetRemoteSDPOfferDone()
{
    webrtc_instance->createSDP(WebRTC::SDPType::ANSWER);
}


void WebrtcController::dispatch_string(std::string event_name,std::string str)
{
    std::cout<<"publish "<<event_name<<std::endl;
    EventBus::getInstance().publish(std::move(event_name),std::move(str));
}

void WebrtcController::dispatch_void(std::string event_name)
{
    std::cout<<"publish "<<event_name<<std::endl;
    EventBus::getInstance().publish(std::move(event_name));
}


void WebrtcController::recvSDPOffer(std::string sdp)
{
    std::cout<<"webrtc recvSDPOffer"<<std::endl;
    webrtc_instance->setRemoteSDP(std::move(sdp),WebRTC::SDPType::OFFER);
}

void WebrtcController::recvSDPAnswer(std::string sdp)
{
    webrtc_instance->setRemoteSDP(std::move(sdp),WebRTC::SDPType::ANSWER);
}

