#ifndef _DEVICELISTMANAGER_H
#define _DEVICELISTMANAGER_H

#include "GlobalEnum.h"
#include <vector>
#include <iostream>
class DevicelistManager
{
public:
    struct DeviceInfo
    {
        DeviceInfo() = default;
        DeviceInfo(std::string device_name_str,std::string code_str,std::string ip_str,std::string comment_str):
            device_name(std::move(device_name_str)),
            code(std::move(code_str)),
            ip(std::move(ip_str)),
            comment(std::move(comment_str)){}
        static DeviceInfo fromMap(const std::map<std::string, std::string>& m)
        {
            DeviceInfo d;
            auto get = [&](const std::string& key) {
                auto it = m.find(key);
                return it != m.end() ? it->second : "";
            };
            d.device_name = get("device_name");
            d.ip = get("ip");
            d.code = get("code");
            d.comment = get("comment");
            return d;
        }
        
        static std::map<std::string, std::string> toMap(const DeviceInfo& d)
        {
            return {
                {"device_name", d.device_name},
                {"ip", d.ip},
                {"code", d.code},
                {"comment", d.comment}
            };
        }
        std::string device_name;
        std::string ip;
        std::string code;
        std::string comment;
    };
public:
    static DevicelistManager& getInstance()
    {
        static DevicelistManager instance;
        return instance;
    }
    void loadDeviceList(std::vector<DeviceInfo> devices)
    {
        device_list = devices;
    }
    const std::vector<DeviceInfo>& getDeviceInfo()
    {
        return device_list;
    }
    void updateCommentByCode(const std::string& code, const std::string& new_comment)
    {
        for (auto& device : device_list)
        {
            if (device.code == code)
            {
                device.comment = new_comment;
                return;
            }
        }
    }
private:
    std::vector<DeviceInfo> device_list;
};


#endif //_DEVICELISTMANAGER_H