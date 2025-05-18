#ifndef _BINARYSTRATEGY_H
#define _BINARYSTRATEGY_H

#include "StrategyInterface.h"

class BinaryStrategy : public Strategy
{
public:
    virtual void execute(std::vector<uint8_t> content, Operator& controll_instance) = 0 ;
    void execute(std::unique_ptr<Parser> parser ,Operator& controll_instance) {};
    ~BinaryStrategy(){}
};

class AvatarStrategy : public BinaryStrategy
{
public:
    void execute(std::vector<uint8_t> content, Operator& controll_instance) override;
    ~AvatarStrategy(){}
};


#endif  //_BINARYSTRATEGY_H