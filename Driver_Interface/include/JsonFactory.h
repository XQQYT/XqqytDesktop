#ifndef _JSONFACTORY_H
#define _JSONFACTORY_H

#include <memory>
#include <string>

class JsonFactory
{
public:
    JsonFactory();
    ~JsonFactory();
    JsonFactory(const JsonFactory&) = delete;
    virtual std::shared_ptr<std::string> ws_register(const std::string&& id);
};

#endif