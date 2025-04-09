#include "EventBus.h"
#include "NetworkController.h"

EventBus::EventBus(){
    network_controller = new NetworkController;
    std::cout<<"init"<<std::endl;
};

EventBus::~EventBus(){
    delete network_controller;
};

void EventBus::initModuleSubscribe()
{
    network_controller->initNetworkSubscribe();
}