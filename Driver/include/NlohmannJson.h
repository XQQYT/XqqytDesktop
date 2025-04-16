#ifndef _NLOHMANNJSON_H
#define _NLOHMANNJSON_H
#include "JsonFactory.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class NlohmannJsonParser : public Parser{
public:
    NlohmannJsonParser();
    NlohmannJsonParser(const json& msg);
    void loadJson(std::string& msg) override;
    std::string getKey(std::string&& key) override;
    std::unique_ptr<Parser> getObj(std::string&& key) override;
    bool contain(std::string&& key) override;
    std::string toString() override;
private:
    json msg_json;
    bool has_loaded;
};

class NlohmannJson : public JsonFactory{
public:
    NlohmannJson();
    ~NlohmannJson();
    NlohmannJson(const NlohmannJson&) = delete;
    std::unique_ptr<Parser> getParser() override;
    std::shared_ptr<std::string> ws_register(const std::string&& id) override;
    std::shared_ptr<std::string> ws_message(const std::string&& user_id,const std::string&& target_id,const std::string&& msg) override;
    std::shared_ptr<std::string> ws_get_target_status(const std::string&& user_id,const std::string&& target_id) override;
    std::shared_ptr<std::string> ws_sdp_offer(const std::string&& user_id,const std::string&& target_id,const std::string&& sdp) override;

};

#endif