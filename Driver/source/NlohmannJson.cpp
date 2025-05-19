/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

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

std::vector<std::unique_ptr<Parser>> NlohmannJsonParser::getArray(std::string&& key)
{
    std::vector<std::unique_ptr<Parser>> result;

    if (msg_json.contains(key) && msg_json[key].is_array())
    {
        for (const auto& item : msg_json[key])
        {
            if (item.is_object())
            {
                result.push_back(std::make_unique<NlohmannJsonParser>(item));
            }
        }
    }

    return result;
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
    json result_msg = {
        {"type", "register"},
        {"content", {
            {"id", std::move(id)}
        }}
    };
    return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_message(std::string user_id,std::string target_id,std::string msg)
{
    json result_msg = {
        {"type", "message"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)},
            {"message", std::move(msg)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_get_target_status(std::string user_id,std::string target_id)
{
    json result_msg = {
        {"type", "get_target_status"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_ready(std::string user_id,std::string target_id)
{
    json result_msg = {
        {"type", "ready"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_sdp_offer(std::string user_id,std::string target_id,std::string sdp)
{
    json result_msg = {
        {"type", "sdp_offer"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)},
            {"sdp", std::move(sdp)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_sdp_answer(std::string user_id,std::string target_id,std::string sdp)
{
    json result_msg = {
        {"type", "sdp_answer"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)},
            {"sdp", std::move(sdp)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_connect_request(std::string user_id,std::string target_id, std::string key)
{
    json result_msg = {
        {"type", "connect_request"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)},
            {"key",std::move(key)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_connect_request_result(std::string user_id,std::string target_id,bool result)
{
    json result_msg = {
        {"type", "connect_request_result"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)},
            {"result", result ? "True" : "False"}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_ice_condidate(std::string user_id,std::string target_id,std::string ice_str,std::string sdp_mid,std::string sdp_mline_index)
{
    json result_msg = {
        {"type", "ice_candidate"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)},
            {"ice_content", {
                {"ice", std::move(ice_str)},
                {"sdp_mid", std::move(sdp_mid)},
                {"sdp_mline_index", std::move(sdp_mline_index)}
            }}
        }}
    };
    return std::make_shared<std::string>(result_msg.dump());
}
std::shared_ptr<std::string> NlohmannJson::ws_ice_gather_done(std::string user_id,std::string target_id)
{
    json result_msg = {
        {"type", "ice_gather_done"},
        {"content", {
            {"user_id", std::move(user_id)},
            {"target_id", std::move(target_id)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::ws_logout(std::string user_id)
{
    json result_msg = {
        {"type", "logout"},
        {"content", {
            {"user_id", std::move(user_id)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::user_register_device_code(std::string device_name)
{
    json result_msg = {
        {"type", "register_device"},
        {"content", {
            {"device_name", std::move(device_name)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}


std::shared_ptr<std::string> NlohmannJson::user_login(std::string user_name, std::string password, std::string code)
{
    json result_msg = {
        {"type", "login"},
        {"content", {
            {"user_name", std::move(user_name)},
            {"password", std::move(password)},
            {"device_code", std::move(code)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::user_register(std::string user_name, std::string password)
{
    json result_msg = {
        {"type", "register"},
        {"content", {
            {"user_name", std::move(user_name)},
            {"password", std::move(password)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::shared_ptr<std::string> NlohmannJson::user_get_device_list(std::string user_name)
{
    json result_msg = {
        {"type", "get_user_device_list"},
        {"content", {
            {"user_name", std::move(user_name)}
        }}
    };
        return std::make_shared<std::string>(result_msg.dump());
}

std::unique_ptr<Parser> NlohmannJson::getParser()
{
    return std::make_unique<NlohmannJsonParser>();
}


