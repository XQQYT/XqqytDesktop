#ifndef _NETWORK_H
#define _NETWORK_H

#include <memory>
#include <functional>
#include <string>

class NetworkInterface{
public:
    NetworkInterface(){};
    NetworkInterface(const NetworkInterface& obj) = default;
    NetworkInterface(NetworkInterface&& obj) = default;
    NetworkInterface& operator=(NetworkInterface& other) = default;
    NetworkInterface& operator=(NetworkInterface&& other) = default;
    virtual ~NetworkInterface();
    virtual void initSocket(const std::string& address,const std::string& port);
    virtual void connectToServer(std::function<void(bool)> callback = nullptr);
    virtual void sendMsg(std::string msg);
    virtual void recvMsg(std::function<void(std::string&&)> callback);
    virtual void closeSocket();
protected:
    std::string address;
    std::string port;
};

#endif