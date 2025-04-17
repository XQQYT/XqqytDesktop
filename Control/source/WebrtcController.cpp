#include "WebrtcController.h"

WebrtcController::WebrtcController()
{
    webrtc_instance = std::make_unique<WebRTC>(*this);
}

void WebrtcController::initWebrtcSubscribe()
{
    // EventBus::getInstance().subscribe("/network/target_is_online",std::bind(
    //     &WebrtcController::createSDP,
    //     this
    // ));
}

void WebrtcController::createSDP()
{
    webrtc_instance->createSDP();
}

void WebrtcController::dispatch_string(std::string event_name,std::string str)
{
    std::cout<<"publish "<<event_name<<"  "<<str<<std::endl;
    EventBus::getInstance().publish(std::move(event_name),std::move(str));
}