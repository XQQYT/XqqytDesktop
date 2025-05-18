#include "BinaryStrategyUser.h"
#include "UserInfo.h"
#include <fstream>
#include <iostream>

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
        controll_instance.dispatch_void("/network/user_avatar_update");
    }
}
