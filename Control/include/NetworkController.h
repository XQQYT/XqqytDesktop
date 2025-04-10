#ifndef _NETWORKCONTROLLER_H
#define _NETWORKCONTROLLER_H

#include "WebSocket.h"
#include <thread>
#include "EventBus.h"
#include "NlohmannJson.h"
#include "MessageParser.h"
#include "UserInfo.h"
#include "NetworkOperator.h"

const std::string server_address = "127.0.0.1";
const std::string server_port = "8888";

class NetworkController : public NetworkOperator{
public:
    void sendToServer(std::string msg);
public:
    NetworkController();
    ~NetworkController();
    NetworkController(const NetworkController&) = delete;
    void connectToServer(std::string target_id);
    void startRecvMsg();
    void stopRecvMsg();
    void sendMsg(std::string msg);
    void initNetworkSubscribe();
private:
    void onConnectToServer(std::string id, std::string target_id);
private:
    std::shared_ptr<NetworkInterface> network_interface;
    std::thread *recv_thread;
    bool is_recv_thread_running;
    std::unique_ptr<JsonFactory> json_factory;
    std::unique_ptr<MessageParser> msg_parser;
};

#endif