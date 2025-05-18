#ifndef _BINARYSTRATEGY_H
#define _BINARYSTRATEGY_H

#include "StrategyInterface.h"

class BinaryStrategy : public Strategy
{
public:
    virtual void execute(std::vector<uint8_t> content) = 0 ;
    void execute(std::unique_ptr<Parser> parser) {};
    ~BinaryStrategy(){}
};


#endif  //_BINARYSTRATEGY_H