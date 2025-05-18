#include "JsonStrategyUser.h"
#include <iostream>

void ResponseStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    std::cout<<"subtype "<<parser->getKey("subtype")<<" , response status  "<<parser->getKey("status");
}

void DeviceCodeStrategy::execute(std::unique_ptr<Parser> parser, Operator& controll_instance)
{
    controll_instance.dispatch_string("/network/receive_device_code", std::move(parser->getKey("device_code")));
}
