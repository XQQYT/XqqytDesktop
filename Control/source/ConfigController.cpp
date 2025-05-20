/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "ConfigController.h"
#include "ConfigDriver.h"
#include "UserInfo.h"
#include "DevicelistManager.h"
#include <iostream>
#include <filesystem>

ConfigController::ConfigController()
{
    settings_config_driver = std::make_unique<ConfigDriver>("settings.json");
    devices_config_driver = std::make_unique<ConfigDriver>("devices.json");
    SettingInfoManager::getInstance().initSettingInfo(std::move(settings_config_driver->getAllConfig()));

    auto raw_device_list = devices_config_driver->getDeviceList();
    std::vector<DevicelistManager::DeviceInfo> device_list;
    for (const auto& m : raw_device_list)
    {
        device_list.push_back(DevicelistManager::DeviceInfo::fromMap(m));
    }
    DevicelistManager::getInstance().loadDeviceList(std::move(device_list));

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
    EventBus::getInstance().subscribe("/network/receive_device_code",std::bind(
        &ConfigController::onRecvDeviceCode,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/login_result",std::bind(
        &ConfigController::onLoginResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/update_device_list",std::bind(
        &ConfigController::onDeviceListUpdated,
        this
    ));
    EventBus::getInstance().subscribe("/network/update_device_comment",std::bind(
        &ConfigController::onUpdateDeviceComment,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    EventBus::getInstance().subscribe("/network/delete_device_in_config",std::bind(
        &ConfigController::onDeleteDevice,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/config/copy_file",std::bind(
        &ConfigController::onCopyFile,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
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
}

void ConfigController::onWrite()
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    settings_config_driver->updataConfig(*(SettingInfoManager::getInstance().getAllConfig()));

    for (const auto& [module, key_value_map] : updated_config) {
        for (const auto& [key, value] : key_value_map) {
            EventBus::getInstance().publish("/config/module_config_updated", std::move(module), std::move(key), std::move(value));
        }
    }
    updated_config.clear();
}

void ConfigController::onRecvDeviceCode(std::string code)
{
    UserInfoManager::getInstance().setCurrentUserId(code);
    onUpdateModule("User","user_id", std::move(code));
    onWrite();
}


void ConfigController::onLoginResult(bool status)
{
    if(status)
    {
        onUpdateModule("User","user_name", std::move(UserInfoManager::getInstance().getUserName()));
        onWrite();
    }

}

void ConfigController::onDeviceListUpdated()
{
    auto devices = DevicelistManager::getInstance().getDeviceInfo();
    std::vector<std::map<std::string, std::string>> list;

    for(const auto& i : devices)
    {
        list.push_back(DevicelistManager::DeviceInfo::toMap(i));
    }
    devices_config_driver->updateDeviceList(list);
}

void ConfigController::onUpdateDeviceComment(std::string code, std::string new_comment)
{
    DevicelistManager::getInstance().updateCommentByCode(code, new_comment);
    onDeviceListUpdated();
}

void ConfigController::onDeleteDevice(std::string code)
{
    std::cout<<"delete "<<code<<std::endl;
    DevicelistManager::getInstance().deleteDevice(code);
    onDeviceListUpdated();
}

void ConfigController::onCopyFile(std::string source_path, std::string des_path, std::function<void()> callback)
{
    std::cout<<"copy "<<source_path<<" -> "<<des_path<<std::endl;
    std::filesystem::copy_file(
        source_path, des_path,
        std::filesystem::copy_options::overwrite_existing
    );
    if(callback)
        callback();
}