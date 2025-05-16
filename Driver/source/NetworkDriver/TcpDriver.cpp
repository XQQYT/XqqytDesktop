#include "TcpDriver.h"
#include <iostream>
#include <iomanip>

TcpDriver::TcpDriver():
    msg_builder(std::make_unique<UserServerMsgBuilder>(security_instance))
{
    addr = {};
}

void TcpDriver::initSocket(const std::string& address,const std::string& port)
{
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::stoi(port));
    inet_pton(AF_INET, address.c_str(), &addr.sin_addr);
}

void TcpDriver::connectToServer(std::function<void(bool)> callback)
{
    int ret = connect(tcp_socket, (sockaddr*)&addr, sizeof(addr));
    if(security_instance && !ret)
    {
        aes_key = security_instance->getAesKey(tcp_socket);
    }
    if(callback)
    {
        callback(!ret);
    }
}

void TcpDriver::sendMsg(std::string msg)
{
    std::unique_ptr<MsgBuilderInterface::UserMsg> ready_to_send_msg = std::move(msg_builder->buildMsg(msg, aes_key));

    size_t final_msg_length = ready_to_send_msg->msg->size();
    size_t sended_length = 0;

    while(sended_length < final_msg_length)
    {
        ssize_t ret = write(tcp_socket, ready_to_send_msg->msg->data() + sended_length, final_msg_length - sended_length);
        if (ret <= 0) {
            if (errno == EINTR) continue;
            perror("write failed");
            break;
        }
        sended_length += ret;
    }
}

void TcpDriver::recvMsg(std::function<void(std::string&&)> callback)
{

}

void TcpDriver::closeSocket()
{

}

void TcpDriver::setSecurityInstance(std::shared_ptr<SecurityInterface> instance)
{
    security_instance = instance;
    msg_builder->setSecurityInstance(instance);
}