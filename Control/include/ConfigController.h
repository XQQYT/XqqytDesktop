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
private:
    std::unique_ptr<ConfigInterface> config_driver;
    std::set<std::string> updated_module;
    std::shared_mutex mtx;
};


#endif