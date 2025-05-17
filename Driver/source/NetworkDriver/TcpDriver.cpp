#include "TcpDriver.h"
#include <iostream>
#include <memory.h>

TcpDriver::TcpDriver():
    msg_builder(std::make_unique<UserServerMsgBuilder>(security_instance))
{
    addr = {};
}

TcpDriver::~TcpDriver()
{
    delete[] tls_info.key;
    delete[] tls_info.session_id;
}

void TcpDriver::initSocket(const std::string& address,const std::string& port)
{
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(std::stoi(port));
    inet_pton(AF_INET, address.c_str(), &addr.sin_addr);
    this->address = std::move(address);
    this->port = std::move(port);
}

void TcpDriver::connectToServer(std::function<void(bool)> callback)
{
    int ret = connect(tcp_socket, (sockaddr*)&addr, sizeof(addr));
    if(security_instance && !ret)
    {
        //发送建立TLS请求
        uint8_t head[2];
        head[0] = 0xEA;
        head[1] = 0xEA;
        write(tcp_socket, head, 2);
        tls_info = security_instance->getAesKey(tcp_socket);

        //TLS连接完成，发起普通tcp连接
        tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

        ret = connect(tcp_socket, (sockaddr*)&addr, sizeof(addr));

        //发送session id，向服务器注册
        uint8_t session_msg[34];
        session_msg[0] = 0xFA;
        session_msg[1] = 0xFA;

        memcpy(session_msg + 2,tls_info.session_id,32);
        size_t final_msg_length = 34;
        size_t sended_length = 0;
    
        while(sended_length < final_msg_length)
        {
            ssize_t ret = write(tcp_socket, session_msg + sended_length, final_msg_length - sended_length);
            if (ret <= 0) {
                if (errno == EINTR) continue;
                perror("write failed");
                break;
            }
            sended_length += ret;
        }
    }
    if(callback)
    {
        callback(!ret);
    }
}

void TcpDriver::sendMsg(std::string msg)
{
    std::unique_ptr<MsgBuilderInterface::UserMsg> ready_to_send_msg = std::move(msg_builder->buildMsg(msg, tls_info.key));

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
        std::cout<<sended_length<<" / "<<final_msg_length<<std::endl;
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