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

    void setEstablishingTargetId(const std::string& id) { establishing_target_id = id; }
    const std::string& getEstablishingTargetId() const { return establishing_target_id; }
    
private:
    UserInfoManager() = default;
    std::string currentUserId_; //your id
    std::string currendTargetId;   //target id which you want to connect

    std::string establishing_target_id;   //target id which try to connect to you
};

#endif