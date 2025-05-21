#ifndef _TCPDRIVER_H
#define _TCPDRIVER_H

#include "Network.h"
#include "UserServerMsgBuilder.h"
#include <unistd.h>
#include <arpa/inet.h>
#include <thread>
#include <atomic>

class TcpDriver : public NetworkInterface
{
public:
    TcpDriver();
    ~TcpDriver();
    void initSocket(const std::string& address,const std::string& port) override;
    void connectToServer(std::function<void(bool)> callback = nullptr) override;
    void sendMsg(std::string msg) override;
    void recvMsg(std::function<void(std::vector<uint8_t>,bool)> callback);
    void closeSocket() override;
    void setSecurityInstance(std::shared_ptr<SecurityInterface> instance) override;
    void sendFile(MsgBuilderInterface::MessageType type,std::string username, std::string path) override;
private:
    int tcp_socket;
    std::unique_ptr<MsgBuilderInterface> msg_builder;
    sockaddr_in addr;
    SecurityInterface::TlsInfo tls_info;
    std::thread* receive_thread;
    std::atomic<bool> runing{false};
    bool connect_status;
};

#endif //_TCPDRIVER_H