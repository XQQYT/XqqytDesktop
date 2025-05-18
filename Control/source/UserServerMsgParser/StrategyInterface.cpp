#include "StrategyInterface.h"
#include "BinaryStrategyUser.h"
#include "JsonStrategyUser.h"
#include <iostream>
std::unique_ptr<Strategy> Strategy::createStrategy(UserServerMsgType type)
{

}

std::unique_ptr<Strategy> Strategy::createStrategy(std::string type)
{
    if(type == "respond")
    {
        return std::make_unique<ResponseStrategy>();
    }
    else
    {
        return nullptr;
    }
}