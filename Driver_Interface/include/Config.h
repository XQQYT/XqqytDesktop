/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>

class ConfigInterface
{
public:
    virtual std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string,std::string>>> getAllConfig() = 0;
    virtual void updataConfig(std::unordered_map<std::string, std::unordered_map<std::string,std::string>>& config) = 0;
    virtual std::vector<std::map<std::string, std::string>> getDeviceList() = 0;
    virtual void updateDeviceList(const std::vector<std::map<std::string, std::string>>& list) = 0;
};

#endif  //CONFIG_H