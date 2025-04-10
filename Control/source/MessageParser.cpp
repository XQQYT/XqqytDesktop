#include "MessageParser.h"
#include <iostream>

//使用nlohamnnJson的驱动
MessageParser::MessageParser(NetworkOperator& base_operator):
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
}


void MessageParser::parserMsg(std::string&& msg)
{
    auto parser = json_factory->getParser();
    parser->loadJson(msg);
    if(parser->contain("type"))
    {
        std::string type = parser->getKey("type");
        std::cout<<type<<std::endl;
        type_func_map[type](parser->getObj("content"));
    }

}

void MessageParser::onRegisterResult(std::unique_ptr<Parser> parser)
{
    std::cout<<"recv register result"<<parser->toString()<<std::endl;
    network_operator.sendToServer("hello");
}
