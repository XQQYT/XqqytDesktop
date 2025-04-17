#include "MainWidget.h"
#include "EventBus.h"
#include <QApplication>

//注册必需事件
void initEventBusRegisterEvent()
{
    EventBus::getInstance().registerEvent("/ui/mainwidget_init_done");
    EventBus::getInstance().registerEvent("/network/connect_to_target");
    EventBus::getInstance().registerEvent("/network/registration_rejected");
    EventBus::getInstance().registerEvent("/network/target_is_offline");
    EventBus::getInstance().registerEvent("/network/target_is_online");
    EventBus::getInstance().registerEvent("/network/failed_to_connect_server");
    EventBus::getInstance().registerEvent("/network/has_connect_request");
    EventBus::getInstance().registerEvent("/network/connect_request_result");
    
    EventBus::getInstance().registerEvent("/webrtc/create_sdp");

}
//使模块订阅好事件
void initModuleSubscribe()
{
    EventBus::getInstance().initModuleSubscribe();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initEventBusRegisterEvent();
    initModuleSubscribe();
    MainWidget w;
    w.show();
    return a.exec();
}
