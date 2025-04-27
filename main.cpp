#include "MainWidget.h"
#include "EventBus.h"
#include <QApplication>
#include "UserInfo.h"
//注册必需事件
void initEventBusRegisterEvent()
{
    EventBus::getInstance().registerEvent("/ui/connectwidget_init_done");
    EventBus::getInstance().registerEvent("/network/connect_to_target");
    EventBus::getInstance().registerEvent("/network/registration_rejected");\
    EventBus::getInstance().registerEvent("/network/registration_successed");
    EventBus::getInstance().registerEvent("/network/target_is_offline");
    EventBus::getInstance().registerEvent("/network/target_is_online");
    EventBus::getInstance().registerEvent("/network/failed_to_connect_server");
    EventBus::getInstance().registerEvent("/network/has_connect_request");
    EventBus::getInstance().registerEvent("/network/send_connect_request_result");
    EventBus::getInstance().registerEvent("/network/recv_connect_request_result");

    EventBus::getInstance().registerEvent("/webrtc/init_webrtc_done");
    EventBus::getInstance().registerEvent("/webrtc/remote_ready");
    EventBus::getInstance().registerEvent("/webrtc/create_sdp_offer");
    EventBus::getInstance().registerEvent("/webrtc/create_sdp_answer");
    EventBus::getInstance().registerEvent("/webrtc/set_remote_sdp_offer_done");
    EventBus::getInstance().registerEvent("/webrtc/recv_sdp_offer");
    EventBus::getInstance().registerEvent("/webrtc/recv_sdp_answer");
    EventBus::getInstance().registerEvent("/webrtc/send_ice_candidate");
    EventBus::getInstance().registerEvent("/webrtc/send_ice_gather_done");
    EventBus::getInstance().registerEvent("/webrtc/recv_ice_candidate");
    EventBus::getInstance().registerEvent("/webrtc/recv_ice_gather_done");
    EventBus::getInstance().registerEvent("/webrtc/connection_status");

    EventBus::getInstance().registerEvent("/render/set_render_instance");

    EventBus::getInstance().registerEvent("/mouse_event/has_event");
    EventBus::getInstance().registerEvent("/keyboard_event/has_event");

    EventBus::getInstance().registerEvent("/control/close_control");
    EventBus::getInstance().registerEvent("/control/recv_close_control");
}
//使模块订阅好事件
void initModuleSubscribe()
{
    EventBus::getInstance().initModuleSubscribe();
}

int main(int argc, char *argv[])
{
    if(argc != 2)
        return 0;
    QApplication a(argc, argv);
    initEventBusRegisterEvent();
    initModuleSubscribe();
    UserInfoManager::getInstance().setCurrentUserId(argv[1]);
    MainWidget w;
    w.show();
    return a.exec();
}
