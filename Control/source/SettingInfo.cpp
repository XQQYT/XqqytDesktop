#include "SettingInfo.h"
#include <iostream>

void SettingInfoManager::initSettingInfo(std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> setting)
{
    setting_info = std::move(setting);
}

bool SettingInfoManager::checkModlue(std::string& module)
{
    return setting_info->find(module) != setting_info->end();
}

std::unique_ptr<std::unordered_map<std::string,std::string>> SettingInfoManager::getModuleConfig(std::string module)
{
    if(!checkModlue(module))
        return nullptr;
    auto result = (*setting_info)[module];
    return std::make_unique<std::unordered_map<std::string,std::string>>(result);
}

void SettingInfoManager::updataModuleConfig(std::string module, std::string key, std::string value)
{
    if(!checkModlue(module))
        return;
    (*setting_info)[module][key] = std::move(value);
}

std::string SettingInfoManager::getValue(std::string module, std::string key)
{
    if(!checkModlue(module))
        return "";
    return (*setting_info)[module][key];
}

std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* SettingInfoManager::getAllConfig()
{
    return setting_info.get();
}