#include "MainWidget.h"
#include "EventBus.h"
#include <QApplication>
#include "UserInfo.h"
//注册必需事件
void initEventBusRegisterEvent()
{
    EventBus::getInstance().registerEvent("/ui/mainwidget_init_done");
    EventBus::getInstance().registerEvent("/network/connect_to_target");
    EventBus::getInstance().registerEvent("/network/registration_rejected");\
    EventBus::getInstance().registerEvent("/network/registration_successed");
    EventBus::getInstance().registerEvent("/network/target_is_offline");
    EventBus::getInstance().registerEvent("/network/target_is_online");
    EventBus::getInstance().registerEvent("/network/failed_to_connect_server");
    EventBus::getInstance().registerEvent("/network/has_connect_request");
    EventBus::getInstance().registerEvent("/network/send_connect_request_result");
    EventBus::getInstance().registerEvent("/network/recv_connect_request_result");

    EventBus::getInstance().registerEvent("/webrtc/create_sdp_offer");
    EventBus::getInstance().registerEvent("/webrtc/create_sdp_answer");
    EventBus::getInstance().registerEvent("/webrtc/set_remote_sdp_offer_done");
    
    EventBus::getInstance().registerEvent("/webrtc/recv_sdp_offer");

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
    UserInfoManager::getInstance().setCurrentUserId(argv[1]);
    MainWidget w;
    w.show();
    return a.exec();
}
