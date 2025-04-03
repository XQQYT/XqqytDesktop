#include "Network.h"

NetworkInterface::~NetworkInterface()
{
    
}
void NetworkInterface::initSocket(const std::string& address,const std::string& port)
{

}
void NetworkInterface::connectToServer(std::function<void(bool)> callback)
{

}
void NetworkInterface::sendMsg(const std::string& msg)
{

}
void NetworkInterface::recvMsg(std::function<void(std::string)> callback)
{

}
void NetworkInterface::closeSocket()
{

}