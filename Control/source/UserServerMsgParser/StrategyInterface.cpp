#include "StrategyInterface.h"
#include "BinaryStrategyUser.h"
#include "JsonStrategyUser.h"
#include <iostream>
std::unique_ptr<Strategy> Strategy::createStrategy(UserServerMsgType type)
{
    switch (type)
    {
    case UserServerMsgType::USER_AVATAR:
        return std::make_unique<AvatarStrategy>();
        break;
    case UserServerMsgType::VERSION_PACKAGE:
        return std::make_unique<VersionPackageStrategy>();
        break;
    default:
        return nullptr;
        break;
    }
}

std::unique_ptr<Strategy> Strategy::createStrategy(std::string type)
{
    if(type == "respond")
    {
        return std::make_unique<ResponseStrategy>();
    }
    else if(type == "device_code")
    {
        return std::make_unique<DeviceCodeStrategy>();
    }
    else if(type == "device_list")
    {
        return std::make_unique<DeviceListStrategy>();
    }
    else if(type == "lastest_version")
    {
        return std::make_unique<LastestVersionStrategy>();
    }
    else
    {
        return nullptr;
    }
}