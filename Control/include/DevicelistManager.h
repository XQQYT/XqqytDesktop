#ifndef _DEVICELISTMANAGER_H
#define _DEVICELISTMANAGER_H

#include "GlobalEnum.h"
#include <vector>

class DevicelistManager
{
public:
    struct DeviceInfo
    {
        DeviceInfo(std::string device_name_str,std::string code_str,std::string ip_str,std::string comment_str):
            device_name(std::move(device_name_str)),
            code(std::move(code_str)),
            ip(std::move(ip_str)),
            comment(std::move(comment_str)){}
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
private:
    std::vector<DeviceInfo> device_list;
};


#endif //_DEVICELISTMANAGER_H