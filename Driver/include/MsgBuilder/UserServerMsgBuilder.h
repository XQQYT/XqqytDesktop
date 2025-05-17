#ifndef _USERSERVERMSG_H
#define _USERSERVERMSG_H

#include "MsgBuilderInterface.h"
#include "SecurityInterface.h"
#include <vector>
#include <memory>
#include <stdint.h>

static const uint16_t magic = 0xABCD;
static const uint8_t version = 0x01; 

struct __attribute__((packed)) Header
{
    uint16_t magic;
    uint8_t version;
    uint32_t length;
};

class UserServerMsgBuilder : public MsgBuilderInterface
{
public:
    UserServerMsgBuilder(std::shared_ptr<SecurityInterface> instance = nullptr);
    ~UserServerMsgBuilder(){}
    std::unique_ptr<MsgBuilderInterface::UserMsg> buildMsg(std::string payload, const uint8_t* key) override;
    std::unique_ptr<MsgBuilderInterface::UserMsg> buildFile(MsgBuilderInterface::MessageType type,std::string username, std::string path, uint8_t* key) override;

private:
    uint8_t version;
};

#endif //_USERSERVERMSG_H