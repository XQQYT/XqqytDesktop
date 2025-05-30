/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _MESSAGEPARSER_H
#define _MESSAGEPARSER_H

#include "NlohmannJson.h"
#include <unordered_map>
#include <functional>
#include "Operator.h"
#include "UserInfo.h"
class SignalMessageParser{
public:
    SignalMessageParser(Operator& base_operator);
    ~SignalMessageParser();
    void parserMsg(std::string&& msg);
private:
    void initTypeFuncMap();
    void onRegisterResult(std::unique_ptr<Parser> parser);
    void onTargetStatusResult(std::unique_ptr<Parser> parser);
    void onConnectRequest(std::unique_ptr<Parser> parser);
    void onConnectRequestResult(std::unique_ptr<Parser> parser);
    void onReady(std::unique_ptr<Parser> parser);
    void onSdpOffer(std::unique_ptr<Parser> parser);
    void onSdpAnswer(std::unique_ptr<Parser> parser);
    void onIceCondidate(std::unique_ptr<Parser> parser);
    void onIceGatherDone(std::unique_ptr<Parser> parser);
private:
    std::unique_ptr<JsonFactory> json_factory;
    std::unordered_map<std::string,std::function<void(std::unique_ptr<Parser>)>> type_func_map;
    Operator& network_operator;
};

#endif
