#include "WebrtcController.h"

WebrtcController::WebrtcController()
{
    webrtc_instance = std::make_unique<WebRTC>();
}

void WebrtcController::initWebrtcSubscribe()
{
    EventBus::getInstance().subscribe("/network/target_is_online",std::bind(
        &WebrtcController::createSDP,
        this
    ));
}

void WebrtcController::createSDP()
{
    webrtc_instance->createSDP();
}