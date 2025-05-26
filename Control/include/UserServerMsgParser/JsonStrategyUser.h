#ifndef _JSONSTRATEGY_H
#define _JSONSTRATEGY_H

#include "StrategyInterface.h"

class JsonStrategy : public Strategy
{
public:
    void execute(std::vector<uint8_t> content, Operator& controll_instance) override{};
    virtual void execute(std::unique_ptr<Parser> parser, Operator& controll_instance) = 0;
    ~JsonStrategy(){}
};

class ResponseStrategy : public JsonStrategy
{
public:
    void execute(std::unique_ptr<Parser> parser, Operator& controll_instance) override;
    ~ResponseStrategy(){}
};

class DeviceCodeStrategy : public JsonStrategy
{
public:
    void execute(std::unique_ptr<Parser> parser, Operator& controll_instance) override;
    ~DeviceCodeStrategy(){}
};

class DeviceListStrategy : public JsonStrategy
{
public:
    void execute(std::unique_ptr<Parser> parser, Operator& controll_instance) override;
    ~DeviceListStrategy(){}
};

class LastestVersionStrategy : public JsonStrategy
{
public:
    void execute(std::unique_ptr<Parser> parser, Operator& controll_instance) override;
    ~LastestVersionStrategy(){}
};

#endif  //_JSONSTRATEGY_H