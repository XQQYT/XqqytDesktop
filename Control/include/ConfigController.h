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
private:
    std::unique_ptr<ConfigInterface> config_driver;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> updated_config;
    std::shared_mutex mtx;
};


#endif