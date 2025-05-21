/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "NetworkController.h"
#include "SettingInfo.h"

static const std::string module_name = "Network";

NetworkController::NetworkController():
    websocket_interface(WebSocket::create()),
    tcp_interface(std::make_unique<TcpDriver>()),
    openssl_interface(std::make_shared<OpensslDriver>())
{
    //启用加密
    tcp_interface->setSecurityInstance(openssl_interface);
    auto meta_config = SettingInfoManager::getInstance().getModuleConfig("Meta");
    websocket_interface->initSocket((*meta_config)["signal_server_ip"],(*meta_config)["signal_server_port"]);
    tcp_interface->initSocket("127.0.0.1","8889");
    json_factory = std::make_unique<NlohmannJson>();
    msg_parser = std::make_unique<SignalMessageParser>(*this);
    user_server_msg_parser = std::make_unique<UserServerMsgParser>(*this),
    recv_thread = nullptr;
    is_recv_thread_running = false;
    is_first_connect = true;
    loadSetting();
}

NetworkController::~NetworkController()
{
    stopRecvMsg();
    tcp_interface->closeSocket();
}

void NetworkController::loadSetting()
{
    SettingInfoManager::getInstance().getModuleConfig("Network");
    std::cout<<"catch network config"<<std::endl;
}

void NetworkController::connectToServer()
{
    if(is_first_connect)
    {
        std::string user_id = UserInfoManager::getInstance().getCurrentUserId();
        if(!user_id.empty())
        {
            websocket_interface->connectToServer([this,code = std::move(user_id)](bool ret){
                if(ret){
                    UserInfoManager::getInstance().setSignalConnectStatus(true);
                    startRecvMsg();
                    //发送注册消息
                    sendMsg(*json_factory->ws_register(std::move(code)));
                    std::cout<<"success to connect signal server"<<std::endl;
                }
                else{
                    UserInfoManager::getInstance().setSignalConnectStatus(false);
                    EventBus::getInstance().publish("/network/failed_to_connect_server");
                    std::cout<<"failed to connect signal server"<<std::endl;
                }
            });
        }
        tcp_interface->connectToServer([this](bool ret){
            if (ret) {
                UserInfoManager::getInstance().setUserConnectStatus(true);
                EventBus::getInstance().publish("/network/connect_to_user_server_result", true);
                dynamic_cast<TcpDriver*>(tcp_interface.get())->recvMsg([this](std::vector<uint8_t> vec, bool is_binary){
                    if (user_server_msg_parser) {
                        user_server_msg_parser->ParseMsg(std::move(vec), is_binary);
                    }
                });
            }
            else
            {   
                UserInfoManager::getInstance().setUserConnectStatus(false);
                EventBus::getInstance().publish("/network/connect_to_user_server_result", false);
            }
        });
        is_first_connect = false;
    }
}

void NetworkController::onReConnectToSignalServer(std::string code)
{
    websocket_interface->connectToServer([this,user_id = std::move(code)](bool ret){
        if(ret){
            startRecvMsg();
            //发送注册消息
            sendMsg(*json_factory->ws_register(std::move(user_id)));
            std::cout<<"success to re-connect signal server"<<std::endl;
        }
        else{
            EventBus::getInstance().publish("/network/failed_to_connect_server");
            std::cout<<"failed to re-connect server"<<std::endl;
        }
    });
}

void NetworkController::startRecvMsg()
{
    std::function<void(std::string&&)> recv_callback = [this](std::string&& recv_msg){
        msg_parser->parserMsg(std::move(recv_msg));
    };
    websocket_interface->recvMsg(recv_callback);
}

void NetworkController::stopRecvMsg()
{
    if(recv_thread)
    {
        is_recv_thread_running = false;
        recv_thread->join();
        delete recv_thread;
    }

}

void NetworkController::sendMsg(std::string msg)
{
    websocket_interface->sendMsg(std::move(msg));
}

void NetworkController::initNetworkSubscribe()
{
    EventBus::getInstance().subscribe("/config/module_config_updated",std::bind(
        &NetworkController::onModuleConfigUpdated,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe("/network/get_target_status",std::bind(
        &NetworkController::onGetTargetStatus,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/connect_to_target",std::bind(
        &NetworkController::onConnectToTarget,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    EventBus::getInstance().subscribe("/ui/connectwidget_init_done",std::bind(
        &NetworkController::connectToServer,
        this
    ));
    EventBus::getInstance().subscribe("/network/send_connect_request_result",std::bind(
        &NetworkController::onConnectRequestResult,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    EventBus::getInstance().subscribe("/webrtc/init_webrtc_done",std::bind(
        &NetworkController::onWebRTCInitDone,
        this
    ));
    EventBus::getInstance().subscribe("/webrtc/create_sdp_offer",std::bind(
        &NetworkController::onCreateSDPOffer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/create_sdp_answer",std::bind(
        &NetworkController::onCreateSDPAnswer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/send_ice_candidate",std::bind(
        &NetworkController::onHaveICECondidate,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe("/webrtc/send_ice_gather_done",std::bind(
        &NetworkController::onGatherICEDone,
        this
    ));
    EventBus::getInstance().subscribe("/network/send_logout",std::bind(
        &NetworkController::onSendLogout,
        this
    ));
    EventBus::getInstance().subscribe("/network/send_to_user_server",std::bind(
        &NetworkController::onSendToUserServer,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    EventBus::getInstance().subscribe("/network/receive_device_code",std::bind(
        &NetworkController::onReConnectToSignalServer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/login_result",std::bind(
        &NetworkController::onLoginResult,
        this,
        std::placeholders::_1
    ));
}


void NetworkController::onModuleConfigUpdated(std::string module,std::string key,std::string value)
{
    std::cout<<"network config receive changed"<<std::endl;
}

void NetworkController::onGetTargetStatus(std::string target_id)
{
    UserInfoManager::getInstance().setCurrentTargetId(target_id);
    UserInfoManager::getInstance().setEstablishingTargetId(target_id);
    sendToServer(*json_factory->ws_get_target_status(std::move(UserInfoManager::getInstance().getCurrentUserId()),
        std::move(UserInfoManager::getInstance().getCurrentTargetId())));
}

void NetworkController::onConnectToTarget(std::string target_id, std::string key)
{
    sendToServer(*json_factory->ws_connect_request(UserInfoManager::getInstance().getCurrentUserId(),
                    UserInfoManager::getInstance().getCurrentTargetId(),key));
}

void NetworkController::sendToServer(std::string msg)
{
    sendMsg(std::move(msg));
}

void NetworkController::dispatch_void(const std::string event_name)
{
    EventBus::getInstance().publish(std::move(event_name));
    std::cout<<"send "<<event_name<<std::endl;
}

void NetworkController::dispatch_string(std::string event_name,std::string str)
{
    EventBus::getInstance().publish(std::move(event_name),std::move(str));
}

void NetworkController::dispatch_string_string(std::string event_name,std::string str1,std::string str2)
{
    EventBus::getInstance().publish(std::move(event_name),std::move(str1),std::move(str2));
}

void NetworkController::dispatch_string_string_string(std::string event_name, std::string str1, std::string str2, std::string str3)
{
    EventBus::getInstance().publish(std::move(event_name),std::move(str1),std::move(str2),std::move(str3));
}

void NetworkController::dispatch_bool(std::string event_name,bool status)
{
    EventBus::getInstance().publish(std::move(event_name),status);
}

void NetworkController::onCreateSDPOffer(std::string sdp_str)
{
    std::string userid = UserInfoManager::getInstance().getCurrentUserId();
    std::string targetid = UserInfoManager::getInstance().getCurrentTargetId();
    sendToServer(*json_factory->ws_sdp_offer(std::move(UserInfoManager::getInstance().getCurrentUserId()),
        std::move(UserInfoManager::getInstance().getCurrentTargetId()),
        std::move(sdp_str)));
}

void NetworkController::onCreateSDPAnswer(std::string sdp_str)
{
    std::string userid = UserInfoManager::getInstance().getCurrentUserId();
    std::string targetid = UserInfoManager::getInstance().getCurrentTargetId();
    sendToServer(*json_factory->ws_sdp_answer(std::move(UserInfoManager::getInstance().getCurrentUserId()),
        std::move(UserInfoManager::getInstance().getEstablishingTargetId()),
        std::move(sdp_str)));
}

//send connect result to peer
void NetworkController::onConnectRequestResult(std::string target_id,bool result)
{
    sendToServer(*json_factory->ws_connect_request_result(std::move(UserInfoManager::getInstance().getCurrentUserId()),
        std::move(target_id),
        result));
}

void NetworkController::onHaveICECondidate(std::string ice_str,std::string sdp_mid,std::string sdp_mline_index)
{
    sendToServer(*json_factory->ws_ice_condidate(std::move(UserInfoManager::getInstance().getCurrentUserId()),
    std::move(UserInfoManager::getInstance().getEstablishingTargetId()),std::move(ice_str),std::move(sdp_mid),std::move(sdp_mline_index)));
}

void NetworkController::onGatherICEDone()
{
    sendToServer(*json_factory->ws_ice_gather_done(std::move(UserInfoManager::getInstance().getCurrentUserId()),
    std::move(UserInfoManager::getInstance().getEstablishingTargetId())));
}

void NetworkController::onWebRTCInitDone()
{
    sendToServer(*json_factory->ws_ready(std::move(UserInfoManager::getInstance().getCurrentUserId()),
    std::move(UserInfoManager::getInstance().getEstablishingTargetId())));
}

void NetworkController::onSendLogout()
{
    sendToServer(*json_factory->ws_logout(std::move(UserInfoManager::getInstance().getCurrentUserId())));
}

void NetworkController::onLoginResult(bool status)
{
    std::cout<<"NetworkController::onLoginResult"<<std::endl;

    if(status)
    {
        tcp_interface->sendMsg(*json_factory->user_get_device_list(UserInfoManager::getInstance().getUserName()));
    }
    std::cout<<"NetworkController::onLoginResult"<<std::endl;

}

void NetworkController::onSendToUserServer(UserMsgType msg_type, std::vector<std::string> args)
{
    switch(msg_type)
    {
        case UserMsgType::RegisterDeviceCode:
            tcp_interface->sendMsg(*json_factory->user_register_device_code(std::move(args[0])));
            break;
        case UserMsgType::LOGIN:
            tcp_interface->sendMsg(*json_factory->user_login(std::move(args[0]),std::move(args[1]), std::move(args[2])));
            break;
        case UserMsgType::REGISTER:
            tcp_interface->sendMsg(*json_factory->user_register(args[0],std::move(args[1])));
            tcp_interface->sendFile(MsgBuilderInterface::MessageType::USER_AVATAR,std::move(args[0]), std::move(args[2]));
            break;
        case UserMsgType::UPDATEAVATAR:
            tcp_interface->sendFile(MsgBuilderInterface::MessageType::USER_AVATAR,std::move(args[0]), std::move(args[1]));
            break;
        case UserMsgType::UPDATEUSERNAME:
            tcp_interface->sendMsg(*json_factory->user_update_user_name(UserInfoManager::getInstance().getUserName(),std::move(args[0])));
            break;
        case UserMsgType::UPDATEPASSWORD:
            tcp_interface->sendMsg(*json_factory->user_update_user_password(UserInfoManager::getInstance().getUserName(),std::move(args[0]), std::move(args[1])));
            break;
        case UserMsgType::UPDATEDEVICECOMMENT:
            tcp_interface->sendMsg(*json_factory->user_update_device_comment(UserInfoManager::getInstance().getUserName(),std::move(args[0]),std::move(args[1])));
            break;
        case UserMsgType::DELETEDEVICE:
            tcp_interface->sendMsg(*json_factory->user_delete_device(UserInfoManager::getInstance().getUserName(),std::move(args[0])));
            break;
        default:
            std::cout<<"unknow msg type "<<static_cast<int>(msg_type)<<std::endl;
    }
}

void NetworkController::onDeleteDevice(std::string device_code)
{
    tcp_interface->sendMsg(*json_factory->user_delete_device(UserInfoManager::getInstance().getUserName(),std::move(device_code)));
}