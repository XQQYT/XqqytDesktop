#include "SettingInfo.h"
#include <iostream>
#include <unistd.h>
#include <limits.h>
#include <libgen.h>
#include <cstring>
#include <string>

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


std::string SettingInfoManager::getExecutableDir() {
    char result[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
    if (count <= 0) return {};

    result[count] = '\0';
    char path[PATH_MAX];
    std::strcpy(path, result);
    return std::string(dirname(path));
}

std::unique_ptr<std::string> SettingInfoManager::getCurrentThemeDir()
{
    std::string theme_dir = get_current_dir_name() + std::string("/Theme/") + (*setting_info)["General"]["theme"];
    return std::make_unique<std::string>(theme_dir);
}