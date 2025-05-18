#include "JsonStrategyUser.h"
#include <iostream>

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
        if(subtype == "register")
        {
            controll_instance.dispatch_bool("/network/register_result", statusToBool(status));
        }
    }
    
}

void DeviceCodeStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    if(parser->contain("device_code"))
        controll_instance.dispatch_string("/network/receive_device_code", std::move(parser->getKey("device_code")));
}
