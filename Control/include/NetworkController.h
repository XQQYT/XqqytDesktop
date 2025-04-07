#ifndef _NETWORKCONTROLLER_H
#define _NETWORKCONTROLLER_H

#include "WebSocket.h"
#include <thread>

const std::string server_address = "127.0.0.1";
const std::string server_port = "8888";

class NetworkController{
public:
    NetworkController();
    ~NetworkController();
    NetworkController(const NetworkController&) = delete;
    void connectToHost(const std::string&& target_id);
    void onRecvMsg(std::string&& recv_msg);
    void startRecvMsg();
    void stopRecvMsg();
private:
    std::shared_ptr<NetworkInterface> network_interface;
    std::thread *recv_thread;
    bool is_recv_thread_running;
};

#endif