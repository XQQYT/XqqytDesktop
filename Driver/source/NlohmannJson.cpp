#include "NlohmannJson.h"
#include <iostream>
NlohmannJsonParser::NlohmannJsonParser():has_loaded(false)
{
    
}

NlohmannJsonParser::NlohmannJsonParser(const json& msg):
has_loaded(false),
msg_json(msg)
{
    
}

void NlohmannJsonParser::loadJson(std::string& msg)
{
    msg_json = json::parse(msg);
    has_loaded = true;
}

std::string NlohmannJsonParser::getKey(std::string&& key)
{
    if(msg_json[key].is_string())
    {
        return msg_json[key];
    }
    return "";
}

std::unique_ptr<Parser> NlohmannJsonParser::getObj(std::string&& key)
{
    if(msg_json[key].is_object())
    {
        return std::make_unique<NlohmannJsonParser>(msg_json[key]);
    }
    return nullptr;
}

bool NlohmannJsonParser::contain(std::string&& key)
{
    return msg_json.contains(key);
}

std::string NlohmannJsonParser::toString()
{
    return msg_json.dump();
}

NlohmannJson::NlohmannJson()
{

}

NlohmannJson::~NlohmannJson()
{

}

std::shared_ptr<std::string> NlohmannJson::ws_register(const std::string&& id)
{
    json result_msg = {{"type", "register"},{"content",{{"id",id}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_message(const std::string&& user_id,const std::string&& target_id,const std::string&& msg)
{
    json result_msg = {{"type", "message"},{"content",{{"user_id",user_id},{"target_id",target_id},{"message",msg}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_get_target_status(const std::string&& user_id,const std::string&& target_id)
{
    json result_msg = {{"type","get_target_status"},{"content",{{"user_id",user_id},{"target_id",target_id}}}};
    return std::make_shared<std::string>(result_msg.dump());
}


std::unique_ptr<Parser> NlohmannJson::getParser()
{
    return std::make_unique<NlohmannJsonParser>();
}


