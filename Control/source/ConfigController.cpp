#include "ConfigController.h"
#include "ConfigDriver.h"
#include <iostream>

ConfigController::ConfigController()
{
    config_driver = std::make_unique<ConfigDriver>("settings.json");
    all_config = std::move(config_driver->getAllConfig());
}

void ConfigController::initSubscribe()
{
    EventBus::getInstance().subscribe("/config/get_all_config",std::bind(
        &ConfigController::onGetAllConfig,
        this
    ));
}

void ConfigController::onGetAllConfig()
{
    EventBus::getInstance().publish("/config/all_config_result",*all_config);
}