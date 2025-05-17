#include "UserServerMsgBuilder.h"
#include <memory.h>
#include <arpa/inet.h>
#include <iostream>
#include <iomanip>
#include <fstream>

UserServerMsgBuilder::UserServerMsgBuilder(std::shared_ptr<SecurityInterface> instance)
    :version(0x01)
{
    security_instance = instance;
}


void printHexAndAscii(const std::vector<uint8_t>& data) {
    const size_t bytes_per_line = 16;
    for (size_t i = 0; i < data.size(); i += bytes_per_line) {
        // 地址偏移
        std::cout << std::setw(4) << std::setfill('0') << std::hex << i << ": ";

        // 十六进制部分
        for (size_t j = 0; j < bytes_per_line; ++j) {
            if (i + j < data.size()) {
                std::cout << std::setw(2) << std::setfill('0') << std::hex
                          << static_cast<int>(data[i + j]) << " ";
            } else {
                std::cout << "   ";
            }
        }

        std::cout << " | ";

        // ASCII部分
        for (size_t j = 0; j < bytes_per_line; ++j) {
            if (i + j < data.size()) {
                char c = static_cast<char>(data[i + j]);
                std::cout << (std::isprint(static_cast<unsigned char>(c)) ? c : '.');
            }
        }

        std::cout << std::endl;
    }

    // 恢复标准格式（可选）
    std::cout << std::dec << std::setfill(' ') << std::endl;
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
    std::vector<uint8_t> msg(sizeof(Header) + 1 + 16 + vec.size() + 32);

    uint32_t payload_length = htonl(1 + 16 + 32 + vec.size());
    memcpy(&header.length, &payload_length, sizeof(payload_length));

    size_t offset = 0;
    memcpy(msg.data() + offset, &header, sizeof(Header)); offset += sizeof(Header);
    *(msg.data()+offset) = 0x00; offset += 1;
    memcpy(msg.data() + offset, iv, 16); offset += 16;
    memcpy(msg.data() + offset, vec.data(), vec.size()); offset += vec.size();
    memcpy(msg.data() + offset, sha256, 32);

    auto user_msg = std::make_unique<MsgBuilderInterface::UserMsg>();
    user_msg->iv = iv;
    user_msg->sha256 = sha256;
    user_msg->msg = std::make_unique<std::vector<uint8_t>>(std::move(msg));

    printHexAndAscii(*user_msg->msg);
    return user_msg;
}

std::unique_ptr<std::vector<uint8_t>> readFileToBytes(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) throw std::runtime_error("Failed to open file");

    file.seekg(0, std::ios::end);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
        throw std::runtime_error("Failed to read file");
    }

    return std::make_unique<std::vector<uint8_t>>(std::move(buffer));
}

std::streamsize getFileSize(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate); // 打开文件，光标定位到末尾
    if (!file) {
        throw std::runtime_error("Failed to open file");
    }
    return file.tellg(); // 返回当前位置，也就是文件大小
}

std::unique_ptr<MsgBuilderInterface::UserMsg> UserServerMsgBuilder::buildFile(MsgBuilderInterface::MessageType type,std::string username, std::string path, uint8_t* key)
{
    constexpr size_t USERNAME_SIZE = 15;
    if (username.size() > USERNAME_SIZE) {
        username.resize(USERNAME_SIZE);
    }

    Header header;

    uint16_t net_magic = htons(magic);
    uint32_t length_place_holder = 0x0;

    memcpy(&header.magic, &net_magic, sizeof(net_magic));
    memcpy(&header.version, &version, sizeof(version));
    memcpy(&header.length, &length_place_holder, sizeof(length_place_holder));

    uint8_t* iv = nullptr;
    uint8_t* sha256 = nullptr;

    std::unique_ptr<std::vector<uint8_t>> full_content = std::make_unique<std::vector<uint8_t>>(getFileSize(path) + 2 + USERNAME_SIZE);
    uint16_t head_offset = 0;
    uint16_t type_net = htons(static_cast<uint16_t>(type));
    memcpy(full_content->data() + head_offset, &type_net, 2);
    head_offset += 2;
    memcpy(full_content->data() + head_offset, username.data(), username.size());
    if (username.size() < USERNAME_SIZE) {
        memset(full_content->data() + head_offset + username.size(), 0, USERNAME_SIZE - username.size());
    }
    head_offset += USERNAME_SIZE;
    
    auto file_all_content = readFileToBytes(path);

    memcpy(full_content->data() + head_offset, file_all_content->data(), file_all_content->size());

    if (security_instance) {
        iv = security_instance->aesEncrypt(*full_content, key);
        std::vector<uint8_t> vi_encrypt(iv,iv+16);
        vi_encrypt.insert(vi_encrypt.end(),full_content->begin(),full_content->end());
        sha256 = security_instance->sha256(vi_encrypt.data(), vi_encrypt.size());
    } else {
        iv = new uint8_t[16]();
        sha256 = new uint8_t[32]();
    }

    // 构造最终消息
    std::vector<uint8_t> msg(sizeof(Header) + 1 + 16 + full_content->size() + 32);

    uint32_t payload_length = htonl(1 + 16 + 32 + full_content->size());
    memcpy(&header.length, &payload_length, sizeof(payload_length));

    size_t offset = 0;
    memcpy(msg.data() + offset, &header, sizeof(Header)); offset += sizeof(Header);
    *(msg.data()+offset) = 0x01; offset += 1;
    memcpy(msg.data() + offset, iv, 16); offset += 16;
    memcpy(msg.data() + offset, full_content->data(), full_content->size()); offset += full_content->size();
    memcpy(msg.data() + offset, sha256, 32);

    auto user_msg = std::make_unique<MsgBuilderInterface::UserMsg>();
    user_msg->iv = iv;
    user_msg->sha256 = sha256;
    user_msg->msg = std::make_unique<std::vector<uint8_t>>(std::move(msg));

    printHexAndAscii(*user_msg->msg);
    return user_msg;
}