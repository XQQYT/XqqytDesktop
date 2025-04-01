#include <memory>
#include <functional>
#include <string>

class NetworkInterface{
public:
    NetworkInterface();
    NetworkInterface(const NetworkInterface& obj);
    NetworkInterface(const NetworkInterface&& obj);
    NetworkInterface& NetworkInterface::operator=(NetworkInterface&& other);
    virtual ~NetworkInterface();
    virtual void initSocket(const std::string& address,const std::string& port);
    virtual void connectToServer();
    virtual void sendMsg(const std::string& msg);
    virtual void recvMsg(std::function<void(std::string)> callback);
    virtual void closeSocket();
protected:
    std::string address;
    std::string port;
};