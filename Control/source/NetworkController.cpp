#include "NetworkController.h"

NetworkController::NetworkController()
{
    //使用websocket驱动
    network_interface = WebSocket::create();
    recv_thread = nullptr;
    is_recv_thread_running = false;
}

NetworkController::~NetworkController()
{
    stopRecvMsg();
}

void NetworkController::connectToHost(const std::string&& target_id)
{
    network_interface->initSocket(server_address,server_port);
    network_interface->connectToServer([this](bool ret){
        if(ret){
            startRecvMsg();
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