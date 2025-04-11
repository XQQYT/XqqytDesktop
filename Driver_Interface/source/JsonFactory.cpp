#include "JsonFactory.h"
#include <iostream>

void Parser::loadJson(std::string& msg)
{
    std::cout<<"base "<<msg<<std::endl;
}

std::string Parser::getKey(std::string&& key)
{
    return "";
}

std::unique_ptr<Parser> Parser::getObj(std::string&& key)
{
    return nullptr;
}

JsonFactory::JsonFactory(){}

JsonFactory::~JsonFactory(){}

std::shared_ptr<std::string> JsonFactory::ws_register(const std::string&& id)
{
    return nullptr;
}

std::shared_ptr<std::string> JsonFactory::ws_message(const std::string&& user_id,const std::string&& target_id,const std::string&& msg)
{
    return nullptr;
}

std::shared_ptr<std::string> JsonFactory::ws_get_target_status(const std::string&& user_id,const std::string&& target_id)
{
    return nullptr;
}

std::unique_ptr<Parser> JsonFactory::getParser()
{
    return nullptr;
}

bool Parser::contain(std::string&& key)
{
    return false;
}

std::string Parser::toString()
{
    return "";
}
