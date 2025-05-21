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
    EventBus::getInstance().subscribe(EventBus::EventType::Config_UpdateModuleConfig,std::bind(
        &ConfigController::onUpdateModule,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3,
        std::placeholders::_4
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Config_WriteIntoFile,std::bind(
        &ConfigController::onWrite,
        this
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Network_ReceiveDeviceCode,std::bind(
        &ConfigController::onRecvDeviceCode,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Network_LoginResult,std::bind(
        &ConfigController::onLoginResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Network_UpdateDeviceList,std::bind(
        &ConfigController::onDeviceListUpdated,
        this
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Config_UpdateDeviceComment,std::bind(
        &ConfigController::onUpdateDeviceComment,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Network_DeleteDeviceInConfig,std::bind(
        &ConfigController::onDeleteDevice,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Config_CopyFile,std::bind(
        &ConfigController::onCopyFile,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Config_RenameFile,std::bind(
        &ConfigController::onRenameFile,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    
}


void ConfigController::onUpdateModule(std::string module, std::string key, std::string value, bool write_now)
{
    std::cout << "update " << module << " " << key << " " << value << std::endl;
    SettingInfoManager::getInstance().updataModuleConfig(module, key, value);
    {
        std::unique_lock<std::shared_mutex> lock(mtx);
        updated_config[module][key] = value;
    }
    if(write_now)
        onWrite();
    EventBus::getInstance().publish(EventBus::EventType::Config_UpdateModuleConfigDone, module, key, value);
}

void ConfigController::onWrite()
{
    std::shared_lock<std::shared_mutex> lock(mtx);
    settings_config_driver->updataConfig(*(SettingInfoManager::getInstance().getAllConfig()));

    for (const auto& [module, key_value_map] : updated_config) {
        for (const auto& [key, value] : key_value_map) {
            EventBus::getInstance().publish(EventBus::EventType::Config_ModuleConfigUpdated, std::move(module), std::move(key), std::move(value));
        }
    }
    updated_config.clear();
}

void ConfigController::onRecvDeviceCode(std::string code)
{
    UserInfoManager::getInstance().setCurrentUserId(code);
    onUpdateModule("User","user_id", std::move(code), true);
}


void ConfigController::onLoginResult(bool status)
{
    if(status)
    {
        onUpdateModule("User","user_name", std::move(UserInfoManager::getInstance().getUserName()), true);
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
    std::filesystem::copy_file(
        source_path, des_path,
        std::filesystem::copy_options::overwrite_existing
    );
    if(callback)
        callback();
}

void ConfigController::onRenameFile(std::string source_path, std::string des_path, std::function<void()> callback)
{
    try {
        std::filesystem::rename(source_path, des_path);
        callback();
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error renaming file: " << e.what() << '\n';
    }
}