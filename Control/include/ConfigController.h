#ifndef CONFIGCONTROLLER_H
#define CONFIGCONTROLLER_H

#include "Config.h"
#include "EventBus.h"

class ConfigController
{
public:
    ConfigController();
    void initSubscribe();
private:
    void onGetAllConfig();
private:
    std::unique_ptr<ConfigInterface> config_driver;
    std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> all_config;
};


#endif