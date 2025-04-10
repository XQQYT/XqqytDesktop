#ifndef _USERINFO_H
#define _USERINFO_H

#include <string>

class UserInfoManager {
public:
    static UserInfoManager& getInstance() {
        static UserInfoManager instance;
        return instance;
    }

    UserInfoManager(const UserInfoManager&) = delete;
    void operator=(const UserInfoManager&) = delete;

    void setCurrentUserId(const std::string& id) { currentUserId_ = id; }
    const std::string& getCurrentUserId() const { return currentUserId_; }

    void setCurrentTargetId(const std::string& id) { currendTargetId = id; }
    const std::string& getCurrentTargetId() const { return currendTargetId; }
private:
    UserInfoManager() = default;
    std::string currentUserId_;
    std::string currendTargetId;
};

#endif