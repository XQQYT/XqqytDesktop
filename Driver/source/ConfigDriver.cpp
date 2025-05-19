/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "ConfigDriver.h"
#include <fstream>
#include <iostream>

ConfigDriver::ConfigDriver(const std::string path)
{
    config_path = path;
    loadConfigFromFile();
}

void ConfigDriver::loadConfigFromFile()
{
    if(config_path.empty())
    {
        std::cout<<"config path is empty"<<std::endl;
        return;
    }
    std::ifstream infile(config_path);
    std::string line;
    std::string config_str;
    if(infile.is_open())
    {
        while(std::getline(infile,line))
        {
            config_str.append(line);
        }
        infile.close();
        config_json = json::parse(config_str);
    }
    else
    {
        std::cout<<"open config file failed"<<std::endl;
    }
}


std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>> ConfigDriver::getAllConfig()
{
    auto result_ptr = std::make_unique<std::unordered_map<std::string, std::unordered_map<std::string, std::string>>>();

    if (!config_json.is_object())
    {
        std::cout << "config_json is not an object" << std::endl;
        return result_ptr;
    }

    for (auto& [module, module_value] : config_json.items())
    {
        if (module_value.is_object())
        {
            for (auto& [key, value] : module_value.items())
            {
                (*result_ptr)[module][key] = value.get<std::string>();
            }
        }
    }

    return result_ptr;
}

void ConfigDriver::updataConfig(std::unordered_map<std::string, std::unordered_map<std::string,std::string>>& config)
{
    if(config_path.empty())
    {
        std::cout << "config path is empty" << std::endl;
        return;
    }
    json new_json;
    // 将 unordered_map 转换为 json 对象
    for (const auto& [module, kv_map] : config)
    {
        for (const auto& [key, value] : kv_map)
        {
            new_json[module][key] = value;
        }
    }
    // 写入文件
    std::ofstream out_file(config_path);
    if (out_file.is_open())
    {
        out_file << new_json.dump();
        out_file.close();
        config_json = new_json;
    }
    else
    {
        std::cout << "Failed to open config file for writing" << std::endl;
    }
}

std::vector<std::map<std::string, std::string>> ConfigDriver::getDeviceList()
{
    std::vector<std::map<std::string, std::string>> result;
    if (!config_json.contains("Devices") || !config_json["Devices"].is_array())
        return result;

    for (const auto& item : config_json["Devices"])
    {
        std::map<std::string, std::string> device;
        for (auto it = item.begin(); it != item.end(); ++it)
        {
            if (it.value().is_string())
                device[it.key()] = it.value();
            else
                device[it.key()] = it.value().dump();
        }
        result.push_back(std::move(device));
    }
    return result;
}

void ConfigDriver::updateDeviceList(const std::vector<std::map<std::string, std::string>>& list)
{
    json devices_json = json::array();
    for (const auto& device_map : list)
    {
        json device_json;
        for (const auto& [key, value] : device_map)
        {
            device_json[key] = value;
        }
        devices_json.push_back(std::move(device_json));
    }

    config_json["Devices"] = std::move(devices_json);

    std::ofstream out_file(config_path);
    if (out_file.is_open())
    {
        out_file << config_json.dump();
        out_file.close();
    }
    else
    {
        std::cout << "Failed to open config file for writing" << std::endl;
    }
}
