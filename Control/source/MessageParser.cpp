/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "MessageParser.h"
#include <iostream>

//使用nlohamnnJson的驱动
MessageParser::MessageParser(Operator& base_operator):
json_factory(std::make_unique<NlohmannJson>()),
network_operator(base_operator)
{
    initTypeFuncMap();
}

MessageParser::~MessageParser()
{

}

void MessageParser::initTypeFuncMap()
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


void MessageParser::parserMsg(std::string&& msg)
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

void MessageParser::onRegisterResult(std::unique_ptr<Parser> parser)
{
    if(parser->getKey("status") == "success")
    {
        network_operator.dispatch_void("/network/registration_successed");
    }
    else
    {
        network_operator.dispatch_void("/network/registration_rejected");
    }
}

void MessageParser::onTargetStatusResult(std::unique_ptr<Parser> parser)
{
    //目标不在线
    if(parser->getKey("status") == "False")
    {
        network_operator.dispatch_void("/network/target_is_offline");//会被ui层接收
    }
    //目标在线
    else
    {
        network_operator.sendToServer(*json_factory->ws_connect_request(UserInfoManager::getInstance().getCurrentUserId(),
                            UserInfoManager::getInstance().getCurrentTargetId(),UserInfoManager::getInstance().getCurrentTargetKey()));
        // network_operator.dispatch_void("/network/target_is_online");
    }
}

void MessageParser::onConnectRequest(std::unique_ptr<Parser> parser)
{
    std::string target_id = parser->getKey("target_id");
    if(!target_id.empty())
    {
        UserInfoManager::getInstance().setEstablishingTargetId(target_id);
        network_operator.dispatch_string("/network/has_connect_request",target_id);
    }
    else
    {
        std::cout<<"json has error"<<std::endl;
    }
}

//receive peer connect request result
void MessageParser::onConnectRequestResult(std::unique_ptr<Parser> parser)
{
    std::string result = parser->getKey("result");
    //对方同意连接
    if(result == "True")
    {
        network_operator.dispatch_bool("/network/recv_connect_request_result",true);
    }
    else
    {
        network_operator.dispatch_bool("/network/recv_connect_request_result",false);
    }
}

//receive peer sdp offer
void MessageParser::onSdpOffer(std::unique_ptr<Parser> parser)
{
    UserInfoManager::getInstance().setEstablishingTargetId(parser->getKey("target_id"));
    auto sdp_offer = parser->getKey("sdp");
    network_operator.dispatch_string("/webrtc/recv_sdp_offer",std::move(sdp_offer));
}

void MessageParser::onSdpAnswer(std::unique_ptr<Parser> parser)
{
    auto sdp_answer = parser->getKey("sdp");
    network_operator.dispatch_string("/webrtc/recv_sdp_answer",std::move(sdp_answer));
}

void MessageParser::onIceCondidate(std::unique_ptr<Parser> parser)
{
    auto ice_content = parser->getObj("ice_content");
    network_operator.dispatch_string_string_string("/webrtc/recv_ice_candidate",std::move(ice_content->getKey("ice")),
                                                    std::move(ice_content->getKey("sdp_mid")),std::move(ice_content->getKey("sdp_mline_index")));
}

void MessageParser::onIceGatherDone(std::unique_ptr<Parser> parser)
{
    network_operator.dispatch_void("/webrtc/recv_ice_gather_done");
}

void MessageParser::onReady(std::unique_ptr<Parser> parser)
{
    network_operator.dispatch_void("/webrtc/remote_ready");
}