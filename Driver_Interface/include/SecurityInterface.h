#ifndef _SECURITYINTERFACE_H
#define _SECURITYINTERFACE_H

#include <vector>
#include <stdint.h>

class SecurityInterface
{
    
public:
    virtual ~SecurityInterface(){}
    virtual uint8_t* getAesKey(int socket) = 0;
    virtual uint8_t* aesEncrypt(std::vector<uint8_t>& data,const uint8_t* key) = 0;
    virtual uint8_t* sha256(uint8_t* str, size_t length) = 0;
};


#endif //_SECURITYINTERFACE_H