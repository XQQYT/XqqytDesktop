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
        // std::string current_user_id = std::move(UserInfoManager::getInstance().getCurrentUserId());
        // std::string current_target_id = std::move(UserInfoManager::getInstance().getCurrentTargetId());
        // network_operator.sendToServer(*json_factory->ws_get_target_status(std::move(current_user_id),std::move(current_target_id)));
        std::cout<<"success to connect server"<<std::endl;
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
                            UserInfoManager::getInstance().getCurrentTargetId()));
        // network_operator.dispatch_void("/network/target_is_online");
    }
}
