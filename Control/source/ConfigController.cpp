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
    std::cout<<"updata "<<module<<" "<<key<<" "<<value<<std::endl;
    SettingInfoManager::getInstance().updataModuleConfig(module, key, value);
    updated_module.insert(module);
    EventBus::getInstance().publish("/config/update_module_config_done",std::move(module),std::move(key),std::move(value));
    std::cout <<"publish done"<<std::endl;
}

void ConfigController::onWrite()
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    config_driver->updataConfig(*(SettingInfoManager::getInstance().getAllConfig()));
    for(auto& module: updated_module)
    {
        EventBus::getInstance().publish("/config/module_config_updated",module,std::move(*(SettingInfoManager::getInstance().getModuleConfig(module))));
    }
    updated_module.clear();
}
