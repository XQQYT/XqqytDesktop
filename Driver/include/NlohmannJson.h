#ifndef _NLOHMANNJSON_H
#define _NLOHMANNJSON_H
#include "JsonFactory.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class NlohmannJson : public JsonFactory{
public:
    NlohmannJson();
    ~NlohmannJson();
    NlohmannJson(const NlohmannJson&) = delete;
    std::shared_ptr<std::string> ws_register(const std::string&& id) override;
};

#endif