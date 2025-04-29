#ifndef CONFIGDRIVER_H
#define CONFIGDRIVER_H

#include "Config.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ConfigDriver : public ConfigInterface
{
public:
    ConfigDriver() = delete;
    ConfigDriver(const std::string path);
    std::unique_ptr<std::unordered_map<std::string, std::unordered_map<std::string,std::string>>> getAllConfig() override;
    void updataConfig(std::unordered_map<std::string, std::unordered_map<std::string,std::string>>& config) override;
private:
    void loadConfigFromFile();
private:
    std::string config_path;
    json config_json;
};
#endif