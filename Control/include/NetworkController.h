/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _NETWORKCONTROLLER_H
#define _NETWORKCONTROLLER_H

#include "WebSocket.h"
#include <thread>
#include "EventBus.h"
#include "NlohmannJson.h"
#include "TcpDriver.h"
#include "OpensslDriver.h"
#include "SignalMessageParser.h"
#include "UserServerMsgParser.h"
#include "UserInfo.h"
#include "Operator.h"
#include "GlobalEnum.h"

class NetworkController : public Operator{
//NetworkOperator
public:
    void sendToServer(std::string msg) override;
    void dispatch_void(std::string event_name) override;
    void dispatch_string(std::string event_name,std::string str) override;
    void dispatch_string_string(std::string event_name,std::string str1,std::string str2) override;
    void dispatch_string_string_string(std::string event_name, std::string str1, std::string str2, std::string str3) override;
    void dispatch_bool(std::string event_name,bool status) override;
//NetworkController
public:
    NetworkController();
    ~NetworkController();
    NetworkController(const NetworkController&) = delete;
    void connectToServer();
    void startRecvMsg();
    void stopRecvMsg();
    void sendMsg(std::string msg);
    void loadSetting();
    void initNetworkSubscribe();
    void onConnectRequestResult(std::string target_id,bool result);
    void onCreateSDPOffer(std::string sdp_str);
    void onCreateSDPAnswer(std::string sdp_str);
    void onHaveICECondidate(std::string ice_str,std::string sdp_mid,std::string sdp_mline_index);
    void onGatherICEDone();
    void onWebRTCInitDone();
    void onModuleConfigUpdated(std::string module,std::string key,std::string value);
    void onSendLogout();
    void onSendToUserServer(UserMsgType msg_type, std::vector<std::string> args);
private:
    void onGetTargetStatus(std::string target_id);
    void onConnectToTarget(std::string target_id, std::string key);
    // void onHaveUserServerMsg()
private:
    std::shared_ptr<NetworkInterface> websocket_interface;
    std::unique_ptr<NetworkInterface> tcp_interface;
    std::shared_ptr<SecurityInterface> openssl_interface;
    std::thread *recv_thread;
    bool is_recv_thread_running;
    std::unique_ptr<JsonFactory> json_factory;
    std::unique_ptr<SignalMessageParser> msg_parser;
    std::unique_ptr<UserServerMsgParser> user_server_msg_parser;
    bool is_first_connect;
};

#endif