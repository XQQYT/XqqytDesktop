#ifndef _STRATEGY_H
#define _STRATEGY_H

#include <vector>
#include <stdint.h>
#include <string>
#include <memory>
#include "NlohmannJson.h"
#include "Operator.h"

enum class UserServerMsgType : uint32_t{

};

class Strategy {
public:
    virtual void execute(std::vector<uint8_t> content, Operator& controll_instance) = 0;
    virtual void execute(std::unique_ptr<Parser> parser, Operator& controll_instance) = 0;
    virtual ~Strategy(){}
    static std::unique_ptr<Strategy> createStrategy(UserServerMsgType type);
    static std::unique_ptr<Strategy> createStrategy(std::string type);
};

#endif //_STRATEGY_H