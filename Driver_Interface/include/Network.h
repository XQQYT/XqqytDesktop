/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _NETWORK_H
#define _NETWORK_H

#include <memory>
#include <functional>
#include <string>
#include "SecurityInterface.h"
#include "MsgBuilderInterface.h"

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
    virtual void sendFile(MsgBuilderInterface::MessageType type,std::string username, std::string path) {};
    virtual void recvMsg(std::function<void(std::string&&)> callback) = 0;
    virtual void closeSocket() = 0;
    virtual void setSecurityInstance(std::shared_ptr<SecurityInterface> instance){security_instance = instance;}
protected:
    std::string address;
    std::string port;
    std::shared_ptr<SecurityInterface> security_instance;
};

#endif