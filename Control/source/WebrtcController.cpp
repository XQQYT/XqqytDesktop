#include "WebrtcController.h"

WebrtcController::WebrtcController()
{
    webrtc_instance = std::make_unique<WebRTC>(*this);
}

void WebrtcController::initWebrtcSubscribe()
{
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
}

void WebrtcController::createSDP(bool status)
{
    if(status)
        webrtc_instance->createSDP();
}

void WebrtcController::dispatch_string(std::string event_name,std::string str)
{
    std::cout<<"publish "<<event_name<<std::endl;
    EventBus::getInstance().publish(std::move(event_name),std::move(str));
}

void WebrtcController::recvSDPOffer(std::string sdp)
{
    std::cout<<"webrtc recvSDPOffer"<<std::endl;
    webrtc_instance->setRemoteSDP(std::move(sdp));
}
