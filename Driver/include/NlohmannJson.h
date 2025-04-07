#ifndef _NLOHMANNJSON_H
#define _NLOHMANNJSON_H
#include "JsonFactory.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class NlohamnnJson : public JsonFactory{
public:
    NlohamnnJson();
    ~NlohamnnJson();
    NlohamnnJson(const NlohamnnJson&) = delete;
    std::shared_ptr<std::string> ws_register(const std::string&& id) override;
};

#endif