#ifndef _OPENSSLDIRVER_H
#define _OPENSSLDRIVER_H

#include "SecurityInterface.h"
#include <openssl/ssl.h>
#include <openssl/err.h>

class OpensslDriver : public SecurityInterface
{
public:
    OpensslDriver();
    ~OpensslDriver(){}
    uint8_t* getAesKey(int socket) override;
    uint8_t* aesEncrypt(std::vector<uint8_t>& data,const uint8_t* key) override;
    uint8_t* sha256(uint8_t* str, size_t length) override;
private:
    SSL_CTX* ctx;
};

#endif //_OPENSSLDRIVER_H