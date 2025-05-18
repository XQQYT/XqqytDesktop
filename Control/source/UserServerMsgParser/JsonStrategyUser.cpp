#include "JsonStrategyUser.h"
#include <iostream>

void ResponseStrategy::execute(std::unique_ptr<Parser> parser)
{
    std::cout<<"subtype "<<parser->getKey("subtype")<<" , response status  "<<parser->getKey("status");
}
