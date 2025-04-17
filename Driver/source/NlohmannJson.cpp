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

std::shared_ptr<std::string> NlohmannJson::ws_register(std::string id)
{
    json result_msg = {{"type", "register"},{"content",{{"id",std::move(id)}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_message(std::string user_id,std::string target_id,std::string msg)
{
    json result_msg = {{"type", "message"},{"content",{{"user_id",std::move(user_id)},{"target_id",std::move(target_id)},{"message",std::move(msg)}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_get_target_status(std::string user_id,std::string target_id)
{
    json result_msg = {{"type","get_target_status"},{"content",{{"user_id",std::move(user_id)},{"target_id",std::move(target_id)}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_sdp_offer(std::string user_id,std::string target_id,std::string sdp)
{
    json result_msg = {{"type","sdp_offer"},{"content",{{"user_id",std::move(user_id)},{"target_id",std::move(target_id)},{"sdp",std::move(sdp)}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_connect_request(std::string user_id,std::string target_id)
{
    json result_msg = {{"type","connect_request"},{"content",{{"user_id",std::move(user_id)},{"target_id",std::move(target_id)}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_connect_request_result(std::string user_id,std::string target_id,bool result)
{
    json result_msg = {{"type","connect_request_result"},{"content",{{"user_id",std::move(user_id)},{"target_id",std::move(target_id)},{"result",result ? "True":"False"}}}};
    return std::make_shared<std::string>(result_msg.dump());
}

std::unique_ptr<Parser> NlohmannJson::getParser()
{
    return std::make_unique<NlohmannJsonParser>();
}


