#include "NetworkController.h"

NetworkController::NetworkController()
{
    //使用websocket驱动
    network_interface = WebSocket::create();
    network_interface->initSocket(server_address,server_port);
    json_factory = std::make_unique<NlohmannJson>();
    msg_parser = std::make_unique<MessageParser>(*this);
    recv_thread = nullptr;
    is_recv_thread_running = false;
    is_first_connect = true;
}

NetworkController::~NetworkController()
{
    stopRecvMsg();
}

void NetworkController::connectToServer()
{
    if(is_first_connect)
    {
        network_interface->connectToServer([this,user_id = std::move(UserInfoManager::getInstance().getCurrentUserId())](bool ret){
        if(ret){
            startRecvMsg();
            //发送注册消息
            sendMsg(*json_factory->ws_register(std::move(user_id)));
            std::cout<<"success to connect server"<<std::endl;
            is_first_connect = false;
        }
        else{
            EventBus::getInstance().publish("/network/failed_to_connect_server");
            std::cout<<"failed to connect server"<<std::endl;
        }
        });
        
    }
}

void NetworkController::startRecvMsg()
{
    std::function<void(std::string&&)> recv_callback = [this](std::string&& recv_msg){
        msg_parser->parserMsg(std::move(recv_msg));
    };
    network_interface->recvMsg(recv_callback);
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
    network_interface->sendMsg(std::move(msg));
}

void NetworkController::initNetworkSubscribe()
{
    EventBus::getInstance().subscribe("/network/connect_to_target",std::bind(
        &NetworkController::connectToTarget,
        this,
        std::placeholders::_1
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
    
}


void NetworkController::connectToTarget(std::string target_id)
{
    UserInfoManager::getInstance().setCurrentTargetId(target_id);
    UserInfoManager::getInstance().setEstablishingTargetId(target_id);
    sendToServer(*json_factory->ws_get_target_status(std::move(UserInfoManager::getInstance().getCurrentUserId()),
        std::move(UserInfoManager::getInstance().getCurrentTargetId())));
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
