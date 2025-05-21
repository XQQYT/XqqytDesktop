/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _USERINFO_H
#define _USERINFO_H

#include <string>

class UserInfoManager {
public:
    enum class Role
    {
        UN_DEFINED,
        Controller,
        BeControlled
    };
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
    
    void setCurrentRole(const Role& role) { current_role = role; }
    const Role& getCurrentRole() const { return current_role; }

    void setCurrentUserKey(const std::string& key) { user_key = key; }
    const std::string& getCurrentUserKey() const { return user_key; }

    void setUserName(const std::string& name) { user_name = name; }
    const std::string& getUserName() const { return user_name; }

    void setChangingUserName(const std::string& name) { changing_user_name = name; }
    const std::string& getChangingUserName() const { return changing_user_name; }

    void setUserConnectStatus(const bool status) { user_connect_status = status; }
    const bool& getUserConnectStatus() const { return user_connect_status; }

    void setSignalConnectStatus(const bool status) { signal_connect_status = status; }
    const bool getSignalConnectStatus() const { return signal_connect_status; }

private:
    UserInfoManager(){
        current_role = Role::UN_DEFINED;
    };
    std::string currentUserId_; //your id
    std::string currendTargetId;   //target id which you want to connect

    std::string establishing_target_id;   //target id which try to connect to you
    Role current_role;
    std::string user_key;

    std::string user_name;
    std::string changing_user_name;

    bool user_connect_status;
    bool signal_connect_status;
};

#endif