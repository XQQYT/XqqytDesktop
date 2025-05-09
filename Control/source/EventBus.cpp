/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "EventBus.h"
#include "NetworkController.h"
#include "WebrtcController.h"
#include "ConfigController.h"

EventBus::EventBus(){
    config_controller = std::make_unique<ConfigController>();
    network_controller = std::make_unique<NetworkController>();
    webrtc_controller = std::make_unique<WebrtcController>();
    thread_pool = std::make_unique<ThreadPool<>>(2, 4, 1024, ThreadPoolType::NORMAL);
};

EventBus::~EventBus(){
};

void EventBus::initModuleSubscribe()
{
    //config controller must be the first to init subscribe, due to networkd and webrtc depend on it
    config_controller->initConfigSubscribe();
    network_controller->initNetworkSubscribe();
    webrtc_controller->initWebrtcSubscribe();
}