#include "BinaryStrategyUser.h"
#include "UserInfo.h"
#include <arpa/inet.h>
#include <iostream>

std::ofstream* VersionPackageStrategy::in = nullptr;
uint32_t VersionPackageStrategy::total_size = 0;
uint32_t VersionPackageStrategy::received_size = 0;
uint64_t VersionPackageStrategy::send_event = 0;

void AvatarStrategy::execute(std::vector<uint8_t> content, Operator& controll_instance)
{
    std::string username(reinterpret_cast<const char*>(content.data() + 2), 15);
    username = username.substr(0, username.find('\0'));

    if(username == UserInfoManager::getInstance().getUserName())
    {
        std::ofstream out(std::string("User/Avatar/").append(username), std::ios::binary);
        if (out.is_open()) {
            out.write(reinterpret_cast<char*>(content.data() + 17), content.size() - 17);
            out.close();
        } else {
            std::cerr << "无法写入" << std::endl;
        }
        controll_instance.dispatch_void(EventBus::EventType::Network_UserAvatarUpdate);
    }
}


void VersionPackageStrategy::execute(std::vector<uint8_t> content, Operator& controll_instance)
{
    uint16_t main_type;
    memcpy(&main_type, content.data(), sizeof(main_type));
    uint16_t main_type_be = ntohs(main_type);

    uint16_t subtype;
    memcpy(&subtype, content.data() + 2, sizeof(subtype));
    uint16_t subtype_be = ntohs(subtype);

    // payload 提取
    std::size_t payload_offset = 4;
    std::size_t payload_size = content.size() - payload_offset;
    const uint8_t* data_ptr = content.data() + payload_offset;

    if (subtype == static_cast<uint16_t>(SubMessageType::HEADER)) {
        std::cout << "开始接收，创建文件" << std::endl;
        if (in) { in->close(); delete in; in = nullptr; }
        in = new std::ofstream("tmp/app.tar.gz", std::ios::binary | std::ios::trunc);
        if (!in->is_open()) {
            std::cerr << "无法打开目标文件" << std::endl;
            delete in; in = nullptr;
            return;
        }
        uint32_t file_size;
        memcpy(&file_size,content.data()+4,4);
        total_size = ntohl(file_size);
    }
    else if (subtype == static_cast<uint16_t>(SubMessageType::PAYLOAD)) {
        if (!in) {
            std::cerr << "未初始化文件流" <<std::endl;
            return;
        }
        in->write(reinterpret_cast<const char*>(data_ptr), payload_size);
        received_size += payload_size;
        send_event++;
        if(send_event % 20 == 0)
            controll_instance.dispatch_uint32_uint32(EventBus::EventType::Network_VersionPackageProgress,received_size, total_size);
    }
    else if (subtype == static_cast<uint16_t>(SubMessageType::END)) {
        std::cout << "接收完毕，关闭文件" << std::endl;
        if (in) {
            in->close(); delete in; in = nullptr;
        }
        controll_instance.dispatch_uint32_uint32(EventBus::EventType::Network_VersionPackageProgress,received_size, total_size);
        send_event = 0;
        total_size = 0;
        received_size = 0;
    }
    else {
        std::cerr << "未知子类型: " << subtype << std::endl;
    }
}


