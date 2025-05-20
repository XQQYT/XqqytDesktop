/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include "Config.h"
#include "EventBus.h"
#include "SettingInfo.h"
#include <mutex>
#include <set>

class ConfigController
{
public:
    ConfigController();
    void initConfigSubscribe();
private:
    void onUpdateModule(std::string module, std::string key, std::string value);
    void onWrite(); 
    void onRecvDeviceCode(std::string code);
    void onLoginResult(bool status);
    void onDeviceListUpdated();
    void onUpdateDeviceComment(std::string code, std::string new_comment);
    void onDeleteDevice(std::string code);
    void onCopyFile(std::string source_path, std::string des_path, std::function<void()> callback);
private:
    std::unique_ptr<ConfigInterface> settings_config_driver;
    std::unique_ptr<ConfigInterface> devices_config_driver;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> updated_config;
    std::shared_mutex mtx;
};


#endif