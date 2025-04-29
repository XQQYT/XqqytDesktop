#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include "Config.h"
#include "EventBus.h"
#include <mutex>
#include <set>

class ConfigController
{
public:
    ConfigController();
    void initConfigSubscribe();
private:
    void onGetAllConfig();
    void onUpdateModule(std::string module, std::string key, std::string value);
    void onGetModuleConfig(std::string module);
    void onWrite(); 
private:
    std::unique_ptr<ConfigInterface> config_driver;
    std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> all_config;
    std::set<std::string> updated_module;
    std::shared_mutex mtx;
};


#endif