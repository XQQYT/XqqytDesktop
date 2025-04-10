#ifndef _JSONFACTORY_H
#define _JSONFACTORY_H

#include <memory>
#include <string>

class Parser
{
public:
    virtual void loadJson(std::string&);
    virtual std::string getKey(std::string&& key);
    virtual std::unique_ptr<Parser> getObj(std::string&& key);
    virtual bool contain(std::string&& key);
    virtual std::string toString();
};
class JsonFactory
{
public:
    JsonFactory();
    ~JsonFactory();
    JsonFactory(const JsonFactory&) = delete;
    virtual std::unique_ptr<Parser> getParser();
    virtual std::shared_ptr<std::string> ws_register(const std::string&& id);
    virtual std::shared_ptr<std::string> ws_message(const std::string&& user_id,const std::string&& target_id,const std::string&& msg);
};

#endif