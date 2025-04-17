#ifndef _NETWORK_H
#define _NETWORK_H

#include <memory>
#include <functional>
#include <string>

class NetworkInterface{
public:
    NetworkInterface(){};
    NetworkInterface(const NetworkInterface& obj) = delete;
    NetworkInterface(NetworkInterface&& obj) = delete;
    NetworkInterface& operator=(NetworkInterface& other) = delete;
    NetworkInterface& operator=(NetworkInterface&& other) = delete;
    virtual ~NetworkInterface(){};
    virtual void initSocket(const std::string& address,const std::string& port) = 0;
    virtual void connectToServer(std::function<void(bool)> callback = nullptr) = 0;
    virtual void sendMsg(std::string msg) = 0;
    virtual void recvMsg(std::function<void(std::string&&)> callback) = 0;
    virtual void closeSocket() = 0;
protected:
    std::string address;
    std::string port;
};

#endif