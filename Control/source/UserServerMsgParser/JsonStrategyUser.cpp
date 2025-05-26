#include "JsonStrategyUser.h"
#include <iostream>
#include "DevicelistManager.h"

bool statusToBool(std::string& status)
{
    if(status == "success")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void ResponseStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    if(parser->contain("status") && parser->contain("subtype"))
    {
        std::string subtype = parser->getKey("subtype");
        std::string status = parser->getKey("status");
        if(subtype == "login")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_LoginResult, statusToBool(status));
        }
        else if(subtype == "register")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_UserRegisterResult, statusToBool(status));
        }
        else if(subtype == "update_device_comment_result")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_UpdateDeviceCommentResult,statusToBool(status));
        }
        else if(subtype == "delete_device_result")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_DeleteDeviceResult,statusToBool(status));
        }
        else if(subtype == "upload_avatar")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_UploadAvatarResult, statusToBool(status));
        }
        else if(subtype == "update_user_name")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_UpdateUsernameResult, statusToBool(status));
        }
        else if(subtype == "update_user_password")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_UpdateUserPasswordResult, statusToBool(status));
        }
        else if(subtype == "register_device")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_RegisterDeviceResult, statusToBool(status));
        }
        else if(subtype == "get_device_list")
        {
            controll_instance.dispatch_bool(EventBus::EventType::Network_GetDeviceListResult, statusToBool(status));
        }
    }
    
}

void DeviceCodeStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    if(parser->contain("device_code"))
        controll_instance.dispatch_string(EventBus::EventType::Network_ReceiveDeviceCode, std::move(parser->getKey("device_code")));
}

void DeviceListStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    std::vector<DevicelistManager::DeviceInfo> devices_vec;
    if(parser->contain("device_list"))
    {
        auto devices = parser->getArray("device_list");
        for (auto& dev : devices) {
            std::string name = dev->getKey("device_name");
            std::string code = dev->getKey("code");
            std::string ip = dev->getKey("ip");
            std::string comment = dev->getKey("comment");
            devices_vec.emplace_back(name,code,ip,comment);
        }
        DevicelistManager::getInstance().loadDeviceList(std::move(devices_vec));
        controll_instance.dispatch_void(EventBus::EventType::Network_UpdateDeviceList);
    }

}

void LastestVersionStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    if(parser->contain("version") && parser->contain("description") && parser->contain("date"))
    {
        std::string version = parser->getKey("version");
        std::string description = parser->getKey("description");
        std::string date = parser->getKey("date");
        controll_instance.dispatch_string_string_string(EventBus::EventType::Network_LastestVersionResult,std::move(version),
            std::move(description),std::move(date));
    }

}

