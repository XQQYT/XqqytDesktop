#include "ConfigController.h"
#include "ConfigDriver.h"
#include <iostream>

ConfigController::ConfigController()
{
    config_driver = std::make_unique<ConfigDriver>("settings.json");
    all_config = std::move(config_driver->getAllConfig());
    std::cout<<"config init done"<<std::endl;
}

void ConfigController::initConfigSubscribe()
{
    EventBus::getInstance().subscribe("/config/get_all_config",std::bind(
        &ConfigController::onGetAllConfig,
        this
    ));
    EventBus::getInstance().subscribe("/config/updata_module_config",std::bind(
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
    EventBus::getInstance().subscribe("/config/get_module_config",std::bind(
        &ConfigController::onGetModuleConfig,
        this,
        std::placeholders::_1
    ));
}

void ConfigController::onGetAllConfig()
{
    EventBus::getInstance().publish("/config/all_config_result",*all_config);
}

void ConfigController::onUpdateModule(std::string module, std::string key, std::string value)
{
    std::cout<<"updata "<<module<<" "<<key<<" "<<value<<std::endl;
    (*all_config)[module][key] = std::move(value);
    updated_module.insert(std::move(module));
}

void ConfigController::onWrite()
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    config_driver->updataConfig(*all_config);
    for(auto& module: updated_module)
    {
        EventBus::getInstance().publish("/config/module_config_updated",module,(*all_config)[module]);
    }
    updated_module.clear();
}

void ConfigController::onGetModuleConfig(std::string module)
{
    EventBus::getInstance().publish("/config/module_config_result",module,(*all_config)[module]);
}