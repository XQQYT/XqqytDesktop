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
    virtual std::shared_ptr<std::string> ws_register(const std::string&& id) = 0;
    virtual std::shared_ptr<std::string> ws_message(const std::string&& user_id,const std::string&& target_id,const std::string&& msg) = 0;
    virtual std::shared_ptr<std::string> ws_get_target_status(const std::string&& user_id,const std::string&& target_id) = 0;
    virtual std::shared_ptr<std::string> ws_sdp_offer(const std::string&& user_id,const std::string&& target_id,const std::string&& sdp) = 0;

};

#endif