#ifndef _MSGBUILDERINTERFACE_H
#define _MSGBUILDERINTERFACE_H

#include <string>
#include <vector>
#include <memory>
#include <string>
#include "SecurityInterface.h"

class MsgBuilderInterface
{
public:
    class UserMsg
    {
    public:
        ~UserMsg()
        {
            delete[] iv;
            delete[] sha256;
        }
    public:
        std::unique_ptr<std::vector<uint8_t>> msg;
        uint8_t* iv;
        uint8_t* sha256;
    };
    enum class MessageType : uint16_t {
        USER_AVATAR = 0xAEAE            
    };

public:
    virtual ~MsgBuilderInterface(){};
    virtual std::unique_ptr<UserMsg> buildMsg(std::string payload, const uint8_t* key) = 0;
    virtual void setSecurityInstance(std::shared_ptr<SecurityInterface> instance){security_instance = instance;}
    virtual std::unique_ptr<MsgBuilderInterface::UserMsg> buildFile(MessageType type,std::string username, std::string path, uint8_t* key) = 0;

protected:
    std::shared_ptr<SecurityInterface> security_instance;
};


#endif //_MSGBUILDERINTERFACE_H