#include "NetworkController.h"

NetworkController::NetworkController()
{
    //使用websocket驱动
    network_interface = WebSocket::create();
    json_factory = std::make_shared<NlohmannJson>();
    recv_thread = nullptr;
    is_recv_thread_running = false;
}

NetworkController::~NetworkController()
{
    stopRecvMsg();
}

void NetworkController::connectToHost(std::string target_id)
{
    network_interface->initSocket(server_address,server_port);
    network_interface->connectToServer([this,target_id = std::move(target_id)](bool ret){
        if(ret){
            startRecvMsg();
            //发送注册消息
            sendMsg(*json_factory->ws_register(std::move(target_id)));
            std::cout<<"success to connect server"<<std::endl;
        }
        else{
            std::cout<<"failed to connect server"<<std::endl;
        }
    });
}

void NetworkController::onRecvMsg(std::string&& recv_msg)
{
    std::cout<<recv_msg<<std::endl;
}

void NetworkController::startRecvMsg()
{
    std::function<void(std::string&&)> recv_callback = [this](std::string&& recv_msg){
        onRecvMsg(std::move(recv_msg));
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
    EventBus::getInstance().subscribe("/network/connect_to_server",std::bind(
        &NetworkController::onConnectToServer,
        this,
        std::placeholders::_1
    ));
}


void NetworkController::onConnectToServer(std::string id)
{
    std::cout<<id<<std::endl;
    connectToHost(std::move(id));
}