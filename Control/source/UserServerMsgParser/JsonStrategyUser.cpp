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
            controll_instance.dispatch_bool("/network/login_result", statusToBool(status));
        }
        else if(subtype == "register")
        {
            controll_instance.dispatch_bool("/network/register_result", statusToBool(status));
        }
        else if(subtype == "update_device_comment_result")
        {
            controll_instance.dispatch_bool("/network/update_device_comment_result",statusToBool(status));
        }
        else if(subtype == "delete_device_result")
        {
            controll_instance.dispatch_bool("/network/delete_device_result",statusToBool(status));
        }
    }
    
}

void DeviceCodeStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    if(parser->contain("device_code"))
        controll_instance.dispatch_string("/network/receive_device_code", std::move(parser->getKey("device_code")));
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
        controll_instance.dispatch_void("/network/update_device_list");
    }

}
