#include "EventBus.h"
#include "NetworkController.h"
#include "WebrtcController.h"
EventBus::EventBus(){
    network_controller = std::make_unique<NetworkController>();
    webrtc_controller = std::make_unique<WebrtcController>();
    std::cout<<"init"<<std::endl;
};

EventBus::~EventBus(){
};

void EventBus::initModuleSubscribe()
{
    network_controller->initNetworkSubscribe();
    webrtc_controller->initWebrtcSubscribe();
}