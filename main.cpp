/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "MainWidget.h"
#include "EventBus.h"
#include <QApplication>
//注册必需事件
void initEventBusRegisterEvent()
{
    EventBus::getInstance().registerEvent("/ui/connectwidget_init_done");
    EventBus::getInstance().registerEvent("/network/get_target_status");
    EventBus::getInstance().registerEvent("/network/registration_result");
    EventBus::getInstance().registerEvent("/network/target_status");
    EventBus::getInstance().registerEvent("/network/connect_to_target");
    EventBus::getInstance().registerEvent("/network/failed_to_connect_server");
    EventBus::getInstance().registerEvent("/network/has_connect_request");
    EventBus::getInstance().registerEvent("/network/send_connect_request_result");
    EventBus::getInstance().registerEvent("/network/recv_connect_request_result");
    EventBus::getInstance().registerEvent("/network/send_logout");
    EventBus::getInstance().registerEvent("/network/send_to_user_server");
    EventBus::getInstance().registerEvent("/network/connect_to_user_server_result");
    EventBus::getInstance().registerEvent("/network/receive_device_code");
    EventBus::getInstance().registerEvent("/network/re_connect_to_signal_server");
    EventBus::getInstance().registerEvent("/network/login_result");
    EventBus::getInstance().registerEvent("/network/register_result");
    EventBus::getInstance().registerEvent("/network/user_avatar_update");
    EventBus::getInstance().registerEvent("/network/update_device_list");

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
    EventBus::getInstance().registerEvent("/clipboard/write_into_clipboard");


    EventBus::getInstance().registerEvent("/control/close_control");
    EventBus::getInstance().registerEvent("/control/recv_close_control");

    EventBus::getInstance().registerEvent("/config/update_module_config");
    EventBus::getInstance().registerEvent("/config/update_module_config_done");
    EventBus::getInstance().registerEvent("/config/write_into_file");
    EventBus::getInstance().registerEvent("/config/module_config_updated");
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
