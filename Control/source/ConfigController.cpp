/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "ConfigController.h"
#include "ConfigDriver.h"
#include "UserInfo.h"
#include <iostream>

ConfigController::ConfigController()
{
    config_driver = std::make_unique<ConfigDriver>("settings.json");
    SettingInfoManager::getInstance().initSettingInfo(std::move(config_driver->getAllConfig()));
    UserInfoManager::getInstance().setCurrentUserId((SettingInfoManager::getInstance().getValue("User","user_id")));
    std::cout<<"config init done"<<std::endl;
}

void ConfigController::initConfigSubscribe()
{
    EventBus::getInstance().subscribe("/config/update_module_config",std::bind(
        &ConfigController::onUpdateModule,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe("/config/write_into_file",std::bind(
        &ConfigController::onWrite,
        this
    ));
}


void ConfigController::onUpdateModule(std::string module, std::string key, std::string value)
{
    std::cout << "update " << module << " " << key << " " << value << std::endl;
    SettingInfoManager::getInstance().updataModuleConfig(module, key, value);
    {
        std::unique_lock<std::shared_mutex> lock(mtx);
        updated_config[module][key] = value;
    }
    EventBus::getInstance().publish("/config/update_module_config_done", module, key, value);
    std::cout << "publish done" << std::endl;
}

void ConfigController::onWrite()
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    config_driver->updataConfig(*(SettingInfoManager::getInstance().getAllConfig()));

    for (const auto& [module, key_value_map] : updated_config) {
        for (const auto& [key, value] : key_value_map) {
            EventBus::getInstance().publish("/config/module_config_updated", std::move(module), std::move(key), std::move(value));
        }
    }
    updated_config.clear();
}
