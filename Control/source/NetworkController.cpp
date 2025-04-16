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

void NetworkController::connectToServer(std::string user_id)
{
    if(is_first_connect)
    {
        network_interface->connectToServer([this,user_id = std::move(user_id)](bool ret){
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
        std::placeholders::_1,
        std::placeholders::_2
    ));
    EventBus::getInstance().subscribe("/ui/mainwidget_init_done",std::bind(
        &NetworkController::connectToServer,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/webrtc/create_sdp",std::bind(
        &NetworkController::onCreateSDP,
        this,
        std::placeholders::_1
    ));
}


void NetworkController::connectToTarget(std::string user_id, std::string target_id)
{
    UserInfoManager::getInstance().setCurrentUserId(user_id);
    UserInfoManager::getInstance().setCurrentTargetId(target_id);
    sendToServer(*json_factory->ws_get_target_status(std::move(UserInfoManager::getInstance().getCurrentUserId()),
        std::move(UserInfoManager::getInstance().getCurrentTargetId())));
}

void NetworkController::sendToServer(std::string msg)
{
    sendMsg(std::move(msg));
}

void NetworkController::dispatch_void(const std::string event_name)
{
    EventBus::getInstance().publish(event_name);
    std::cout<<"send "<<event_name<<std::endl;
}

void NetworkController::onCreateSDP(std::string sdp_str)
{
    std::string userid = UserInfoManager::getInstance().getCurrentUserId();
    std::string targetid = UserInfoManager::getInstance().getCurrentTargetId();
    sendToServer(*json_factory->ws_sdp_offer(std::move(UserInfoManager::getInstance().getCurrentUserId()),
        std::move(UserInfoManager::getInstance().getCurrentTargetId()),
        std::move(sdp_str)));
}
