#include "EventBus.h"
#include "NetworkController.h"
#include "WebrtcController.h"
EventBus::EventBus(){
    network_controller = std::make_unique<NetworkController>();
    webrtc_controller = std::make_unique<WebrtcController>();
    std::cout<<"init"<<std::endl;
    thread_pool = std::make_unique<ThreadPool<>>(2, 4, 1024, ThreadPoolType::NORMAL);
};

EventBus::~EventBus(){
};

void EventBus::initModuleSubscribe()
{
    network_controller->initNetworkSubscribe();
    webrtc_controller->initWebrtcSubscribe();
}