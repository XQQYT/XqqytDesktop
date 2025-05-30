/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

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
    std::vector<std::unique_ptr<Parser>> getArray(std::string&& key) override;
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
    std::shared_ptr<std::string> ws_register(std::string id) override;
    std::shared_ptr<std::string> ws_message(std::string user_id,std::string target_id,std::string msg) override;
    std::shared_ptr<std::string> ws_get_target_status(std::string user_id,std::string target_id) override;
    std::shared_ptr<std::string> ws_ready(std::string user_id,std::string target_id) override;
    std::shared_ptr<std::string> ws_sdp_offer(std::string user_id,std::string target_id,std::string sdp) override;
    std::shared_ptr<std::string> ws_sdp_answer(std::string user_id,std::string target_id,std::string sdp) override;
    std::shared_ptr<std::string> ws_connect_request(std::string user_id,std::string target_id, std::string key) override;
    std::shared_ptr<std::string> ws_connect_request_result(std::string user_id,std::string target_id,bool result) override;
    std::shared_ptr<std::string> ws_ice_condidate(std::string user_id,std::string target_id,std::string ice_str,std::string sdp_mid,std::string sdp_mline_index) override;
    std::shared_ptr<std::string> ws_ice_gather_done(std::string user_id,std::string target_id) override;
    std::shared_ptr<std::string> ws_logout(std::string user_id) override;

    std::shared_ptr<std::string> user_register_device_code(std::string device_name) override;
    std::shared_ptr<std::string> user_login(std::string user_name, std::string password, std::string code) override;
    std::shared_ptr<std::string> user_register(std::string user_name, std::string password) override;
    std::shared_ptr<std::string> user_get_device_list(std::string user_name) override;
    std::shared_ptr<std::string> user_update_device_comment(std::string user_name, std::string device_code, std::string new_comment) override;
    std::shared_ptr<std::string> user_delete_device(std::string user_name, std::string device_code) override;
    std::shared_ptr<std::string> user_update_user_name(std::string user_name, std::string new_username) override;
    std::shared_ptr<std::string> user_update_user_password(std::string user_name, std::string old_password, std::string new_password) override;
    std::shared_ptr<std::string> user_get_lastest_version() override;
    std::shared_ptr<std::string> user_get_version_package() override;

    std::shared_ptr<std::string> syncfile_add_file(std::string id, std::string filename, std::string filesize) override;
    std::shared_ptr<std::string> syncfile_get_file(std::string id) override;
};

#endif