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
    EventBus::getInstance().subscribe("/webrtc/recv_ice_candidate",std::bind(
        &WebrtcController::onRecvIceCandidate,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe("/webrtc/recv_ice_gather_done",std::bind(
        &WebrtcController::onRecvIceCandidateDone,
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

void WebrtcController::dispatch_string_string_string(std::string event_name, std::string str1, std::string str2, std::string str3)
{
    std::cout<<"publish "<<event_name<<std::endl;
    EventBus::getInstance().publish(std::move(event_name),std::move(str1),std::move(str2),std::move(str3));
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

void WebrtcController::onRecvIceCandidate(std::string ice_str,std::string sdp_mid,std::string sdp_mline_index)
{
    webrtc_instance->addIceCandidateIntoBuffer(std::move(ice_str),std::move(sdp_mid),std::stoi(sdp_mline_index));
}

void WebrtcController::onRecvIceCandidateDone()
{
    std::cout<<"recv Ice Candidata Done"<<std::endl;
}
