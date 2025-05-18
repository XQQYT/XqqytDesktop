#include "UserServerMsgParser.h"
#include "StrategyInterface.h"
#include <iostream>

UserServerMsgParser::UserServerMsgParser(Operator& instance):
    controll_instance(instance),
    json_interface(std::make_unique<NlohmannJson>())
{

}

UserServerMsgParser::~UserServerMsgParser()
{

}

void UserServerMsgParser::ParseMsg(std::vector<uint8_t> msg, bool is_binary)
{
    if(is_binary)
    {
        uint32_t type;
        memcpy(&type, msg.data(), 2);
        auto strategy = Strategy::createStrategy(static_cast<UserServerMsgType>(type));
        if(strategy)
        {
            strategy->execute(std::move(msg), controll_instance);
        }
    }
    else
    {
        std::string msg_string(msg.begin(), msg.end());
        auto parser = json_interface->getParser();
        parser->loadJson(msg_string);
        if(parser->contain("type"))
        {
            std::cout<<"Type -> "<<parser->getKey("type")<<std::endl;
            auto strategy = Strategy::createStrategy(std::move(parser->getKey("type")));
            if(strategy)
            {
                strategy->execute(parser->getObj("content"), controll_instance);
            }
        }
        else
        {
            std::cout<<"没有type"<<std::endl;
        }
    }
}