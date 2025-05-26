#ifndef _BINARYSTRATEGY_H
#define _BINARYSTRATEGY_H

#include "StrategyInterface.h"
#include <fstream>

enum class MessageType : uint16_t {
    VERSION_PACKAGE = 0xBEBE     
};

enum class SubMessageType : uint16_t{
    HEADER = 0xAAAA,
    PAYLOAD = 0xABAB,
    END = 0xACAC
};

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

class VersionPackageStrategy : public BinaryStrategy
{
public:
    void execute(std::vector<uint8_t> content, Operator& controll_instance) override;
    ~VersionPackageStrategy(){}
private:
    static std::ofstream* in;
    static uint32_t total_size;
    static uint32_t received_size;
    static uint64_t send_event;
};


#endif  //_BINARYSTRATEGY_H