#include "TcpDriver.h"
#include <iostream>
#include <memory.h>
#include "GlobalEnum.h"

TcpDriver::TcpDriver():
    msg_builder(std::make_unique<UserServerMsgBuilder>(security_instance)),
    tls_info({nullptr,nullptr})
{
    addr = {};
}

TcpDriver::~TcpDriver()
{
    if(tls_info.key)
        delete[] tls_info.key;
    if(tls_info.session_id)
        delete[] tls_info.session_id;
    closeSocket();
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

    struct timeval timeout;
    timeout.tv_sec = 1;   // 1 秒超时
    timeout.tv_usec = 0;
    setsockopt(tcp_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    
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

void TcpDriver::sendFile(MsgBuilderInterface::MessageType type,std::string username, std::string path)
{
    std::unique_ptr<MsgBuilderInterface::UserMsg> ready_to_send_msg = std::move(msg_builder->buildFile(type,
             std::move(username), std::move(path),tls_info.key));

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

NetworkInterface::ParsedPayload parseMsgPayload(const uint8_t* full_msg ,const uint32_t length) {
    NetworkInterface::ParsedPayload result;

    size_t offset = 0;

    memcpy(&result.is_binary, full_msg, 1);
    offset += 1;

    // 3. 解析 IV（16字节）
    result.iv.assign(full_msg + offset, full_msg + offset + 16);
    offset += 16;

    // 4. 解析密文
    size_t cipher_len = length - 16 - 32 - 1;
    result.encrypted_data.assign(full_msg + offset, full_msg + offset + cipher_len);
    offset += cipher_len;

    // 5. 解析 SHA256（32字节）
    result.sha256.assign(full_msg + offset, full_msg + offset + 32);

    return result;
}

void TcpDriver::recvMsg(std::function<void(std::vector<uint8_t>,bool)> callback)
{
    runing = true;
    receive_thread = new std::thread([this,&callback](){
        while(runing)
        {
            uint8_t peek_buffer[4];
            int peeked = recv(tcp_socket, peek_buffer, sizeof(peek_buffer), MSG_PEEK);
            if(peek_buffer[0] == 0xAB && peek_buffer[1] == 0xCD)
            {
                constexpr int HEADER_SIZE = 7;
                uint8_t buffer[HEADER_SIZE] = {0};
                uint32_t header_received = 0;
                while (header_received < HEADER_SIZE) {
                    int n = recv(tcp_socket, buffer + header_received, HEADER_SIZE - header_received, 0);
                    if (n <= 0) throw std::runtime_error("Header recv error");
                    header_received += n;
                }

                uint32_t payload_length = 0;
                memcpy(&payload_length, buffer + 3, sizeof(payload_length));
                payload_length = ntohl(payload_length);

                uint8_t receive_msg[payload_length];
                uint32_t readed_length = 0;

                while (readed_length < payload_length) {
                    int read_byte = recv(tcp_socket, receive_msg + readed_length, payload_length - readed_length, 0);
                    if (read_byte == 0) {
                        throw std::runtime_error("peer closed");
                    }
                    if (read_byte < 0) {
                        throw std::runtime_error("recv error");
                    }
                    readed_length += read_byte;
                    std::cout<<readed_length<<" / "<<payload_length<<std::endl;
                }

                auto parsed = parseMsgPayload(receive_msg,payload_length);
            
                std::vector<uint8_t> result_vec;
                if(security_instance->verifyAndDecrypt(parsed.encrypted_data,tls_info.key,parsed.iv,result_vec, parsed.sha256))
                {
                    result_vec.resize(result_vec.size() - 4);
                    callback(std::move(result_vec),parsed.is_binary);
                }
            }
            else
            {
                char dump_buffer[4];
                recv(tcp_socket, dump_buffer, sizeof(dump_buffer), 0);
            }
        }
    });
}

void TcpDriver::closeSocket()
{
    close(tcp_socket);
    runing = false;
    if(receive_thread->joinable())
        receive_thread->join();
    delete receive_thread;
}

void TcpDriver::setSecurityInstance(std::shared_ptr<SecurityInterface> instance)
{
    security_instance = instance;
    msg_builder->setSecurityInstance(instance);
}