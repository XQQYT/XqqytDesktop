#ifndef SETTINGINFO_H
#define SETTINGINFO_H

#include <unordered_map>
#include <string>
#include <memory>

class SettingInfoManager
{
public:
    SettingInfoManager(const SettingInfoManager&) = delete;
    SettingInfoManager& operator=(SettingInfoManager&) = delete;
    void initSettingInfo(std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> setting);
    static SettingInfoManager& getInstance()
    {
        static SettingInfoManager instance;
        return instance;
    }
    std::unique_ptr<std::unordered_map<std::string,std::string>> getModuleConfig(std::string module);
    std::string getValue(std::string module, std::string key);
    void updataModuleConfig(std::string module, std::string key, std::string value);
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>>* getAllConfig();
    std::unique_ptr<std::string> getCurrentThemeDir();
private:
    SettingInfoManager() = default;
    std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> setting_info;
    bool checkModlue(std::string& module);
    std::string getExecutableDir();
};

#endif