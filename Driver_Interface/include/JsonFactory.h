#ifndef _JSONFACTORY_H
#define _JSONFACTORY_H

#include <memory>
#include <string>

class Parser
{
public:
    virtual void loadJson(std::string&) = 0;
    virtual std::string getKey(std::string&& key) = 0;
    virtual std::unique_ptr<Parser> getObj(std::string&& key) = 0;
    virtual bool contain(std::string&& ksssey) = 0;
    virtual std::string toString() = 0;
};
class JsonFactory
{
public:
    JsonFactory(){};
    virtual ~JsonFactory(){};
    JsonFactory(const JsonFactory&) = delete;
    virtual std::unique_ptr<Parser> getParser() = 0;
    virtual std::shared_ptr<std::string> ws_register(std::string id) = 0;
    virtual std::shared_ptr<std::string> ws_message(std::string user_id,std::string target_id,std::string msg) = 0;
    virtual std::shared_ptr<std::string> ws_get_target_status(std::string user_id,std::string target_id) = 0;
    virtual std::shared_ptr<std::string> ws_ready(std::string user_id,std::string target_id) = 0;
    virtual std::shared_ptr<std::string> ws_sdp_offer(std::string user_id,std::string target_id,std::string sdp) = 0;
    virtual std::shared_ptr<std::string> ws_sdp_answer(std::string user_id,std::string target_id,std::string sdp) = 0;
    virtual std::shared_ptr<std::string> ws_connect_request(std::string user_id,std::string target_id) = 0;
    virtual std::shared_ptr<std::string> ws_connect_request_result(std::string user_id,std::string target_id,bool result) = 0;
    virtual std::shared_ptr<std::string> ws_ice_condidate(std::string user_id,std::string target_id,std::string ice_str,std::string sdp_mid,std::string sdp_mline_index) = 0;
    virtual std::shared_ptr<std::string> ws_ice_gather_done(std::string user_id,std::string target_id) = 0;
    virtual std::shared_ptr<std::string> ws_logout(std::string user_id) = 0;
};

#endif