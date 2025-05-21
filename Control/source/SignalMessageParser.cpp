/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "SignalMessageParser.h"
#include <iostream>

//使用nlohamnnJson的驱动
SignalMessageParser::SignalMessageParser(Operator& base_operator):
json_factory(std::make_unique<NlohmannJson>()),
network_operator(base_operator)
{
    initTypeFuncMap();
}

SignalMessageParser::~SignalMessageParser()
{

}

void SignalMessageParser::initTypeFuncMap()
{
    type_func_map["register_result"] = [this](std::unique_ptr<Parser> parser) {
        this->onRegisterResult(std::move(parser));
    };
    type_func_map["target_status"] = [this](std::unique_ptr<Parser> parser) {
        this->onTargetStatusResult(std::move(parser));
    };
    type_func_map["connect_request"] = [this](std::unique_ptr<Parser> parser) {
        this->onConnectRequest(std::move(parser));
    };
    type_func_map["connect_request_result"] = [this](std::unique_ptr<Parser> parser) {
        this->onConnectRequestResult(std::move(parser));
    };
    type_func_map["ready"] = [this](std::unique_ptr<Parser> parser) {
        this->onReady(std::move(parser));
    };
    type_func_map["sdp_offer"] = [this](std::unique_ptr<Parser> parser) {
        this->onSdpOffer(std::move(parser));
    };
    type_func_map["sdp_answer"] = [this](std::unique_ptr<Parser> parser) {
        this->onSdpAnswer(std::move(parser));
    };
    type_func_map["ice_candidate"] = [this](std::unique_ptr<Parser> parser) {
        this->onIceCondidate(std::move(parser));
    };
    type_func_map["ice_gather_done"] = [this](std::unique_ptr<Parser> parser) {
        this->onIceGatherDone(std::move(parser));
    };
}


void SignalMessageParser::parserMsg(std::string&& msg)
{
    auto parser = json_factory->getParser();
    parser->loadJson(msg);
    if(parser->contain("type"))
    {
        std::string type = parser->getKey("type");
        if(type_func_map.find(type) != type_func_map.end())
            type_func_map[type](parser->getObj("content"));
        else
            std::cout<<"Illegal Type"<<std::endl;
    }

}

void SignalMessageParser::onRegisterResult(std::unique_ptr<Parser> parser)
{
    if(parser->getKey("status") == "success")
    {
        network_operator.dispatch_bool(EventBus::EventType::Network_SignalRegisterResult, true);
    }
    else
    {
        network_operator.dispatch_bool(EventBus::EventType::Network_SignalRegisterResult, false);
    }
}

void SignalMessageParser::onTargetStatusResult(std::unique_ptr<Parser> parser)
{
    //目标不在线
    if(parser->getKey("status") == "False")
    {
        network_operator.dispatch_bool(EventBus::EventType::Network_TargetStatus,false);//会被ui层接收
    }
    //目标在线
    else
    {
        network_operator.dispatch_bool(EventBus::EventType::Network_TargetStatus,true);
    }
}

void SignalMessageParser::onConnectRequest(std::unique_ptr<Parser> parser)
{
    std::string target_id = parser->getKey("target_id");
    if(!target_id.empty())
    {
        UserInfoManager::getInstance().setEstablishingTargetId(target_id);
        network_operator.dispatch_string_string(EventBus::EventType::Network_HasConnectRequest,target_id, parser->getKey("key"));
    }
    else
    {
        std::cout<<"json has error"<<std::endl;
    }
}

//receive peer connect request result
void SignalMessageParser::onConnectRequestResult(std::unique_ptr<Parser> parser)
{
    std::string result = parser->getKey("result");
    //对方同意连接
    if(result == "True")
    {
        network_operator.dispatch_bool(EventBus::EventType::Network_RecvConnectRequestResult,true);
    }
    else
    {
        network_operator.dispatch_bool(EventBus::EventType::Network_RecvConnectRequestResult,false);
    }
}

//receive peer sdp offer
void SignalMessageParser::onSdpOffer(std::unique_ptr<Parser> parser)
{
    UserInfoManager::getInstance().setEstablishingTargetId(parser->getKey("target_id"));
    auto sdp_offer = parser->getKey("sdp");
    network_operator.dispatch_string(EventBus::EventType::WebRTC_RecvSdpOffer,std::move(sdp_offer));
}

void SignalMessageParser::onSdpAnswer(std::unique_ptr<Parser> parser)
{
    auto sdp_answer = parser->getKey("sdp");
    network_operator.dispatch_string(EventBus::EventType::WebRTC_RecvSdpAnswer,std::move(sdp_answer));
}

void SignalMessageParser::onIceCondidate(std::unique_ptr<Parser> parser)
{
    auto ice_content = parser->getObj("ice_content");
    network_operator.dispatch_string_string_string(EventBus::EventType::WebRTC_RecvIceCandidate,std::move(ice_content->getKey("ice")),
                                                    std::move(ice_content->getKey("sdp_mid")),std::move(ice_content->getKey("sdp_mline_index")));
}

void SignalMessageParser::onIceGatherDone(std::unique_ptr<Parser> parser)
{
    network_operator.dispatch_void(EventBus::EventType::WebRTC_RecvIceGatherDone);
}

void SignalMessageParser::onReady(std::unique_ptr<Parser> parser)
{
    network_operator.dispatch_void(EventBus::EventType::WebRTC_RemoteReady);
}