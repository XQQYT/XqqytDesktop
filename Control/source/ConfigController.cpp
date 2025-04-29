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
    std::cout << "on get all config " << std::endl;
    for (const auto& [outer_key, inner_map] : *all_config) {
        std::cout << "Outer key: " << outer_key << std::endl;
        for (const auto& [inner_key, value] : inner_map) {
            std::cout << "  " << inner_key << ": " << value << std::endl;
        }
    }
    EventBus::getInstance().publish("/config/all_config_result",*all_config);
}