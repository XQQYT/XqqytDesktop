#include "UserServerMsgBuilder.h"
#include <memory.h>
#include <arpa/inet.h>
#include <iostream>

UserServerMsgBuilder::UserServerMsgBuilder(std::shared_ptr<SecurityInterface> instance)
    :version(0x01)
{
    security_instance = instance;
}

std::unique_ptr<MsgBuilderInterface::UserMsg> UserServerMsgBuilder::buildMsg(std::string real_msg, const uint8_t* key)
{
    Header header;

    uint16_t net_magic = htons(magic);
    uint32_t length_place_holder = 0x0;

    memcpy(&header.magic, &net_magic, sizeof(net_magic));
    memcpy(&header.version, &version, sizeof(version));
    memcpy(&header.length, &length_place_holder, sizeof(length_place_holder));

    uint8_t* iv = nullptr;
    uint8_t* sha256 = nullptr;

    std::vector<uint8_t> vec(reinterpret_cast<const uint8_t*>(real_msg.data()),
                             reinterpret_cast<const uint8_t*>(real_msg.data() + real_msg.size()));

    if (security_instance) {
        iv = security_instance->aesEncrypt(vec, key);
        std::vector<uint8_t> vi_encrypt(iv,iv+16);
        vi_encrypt.insert(vi_encrypt.end(),vec.begin(),vec.end());
        sha256 = security_instance->sha256(vi_encrypt.data(), vi_encrypt.size());
    } else {
        iv = new uint8_t[16]();
        sha256 = new uint8_t[32]();
    }

    // 构造最终消息
    std::vector<uint8_t> msg(sizeof(Header) + 16 + vec.size() + 32);

    uint32_t payload_length = htonl(16 + 32 + vec.size());
    memcpy(&header.length, &payload_length, sizeof(payload_length));

    size_t offset = 0;
    memcpy(msg.data() + offset, &header, sizeof(Header)); offset += sizeof(Header);
    memcpy(msg.data() + offset, iv, 16); offset += 16;
    memcpy(msg.data() + offset, vec.data(), vec.size()); offset += vec.size();
    memcpy(msg.data() + offset, sha256, 32);

    auto user_msg = std::make_unique<MsgBuilderInterface::UserMsg>();
    user_msg->iv = iv;
    user_msg->sha256 = sha256;
    user_msg->msg = std::make_unique<std::vector<uint8_t>>(std::move(msg));

    return user_msg;
}