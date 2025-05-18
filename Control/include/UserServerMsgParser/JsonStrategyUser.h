#ifndef _JSONSTRATEGY_H
#define _JSONSTRATEGY_H

#include "StrategyInterface.h"

class JsonStrategy : public Strategy
{
public:
    void execute(std::vector<uint8_t> content) override{};
    virtual void execute(std::unique_ptr<Parser> parser) = 0;
    ~JsonStrategy(){}
};

class ResponseStrategy : public JsonStrategy
{
public:
    void execute(std::unique_ptr<Parser> parser) override;
    ~ResponseStrategy(){}
};

#endif  //_JSONSTRATEGY_H