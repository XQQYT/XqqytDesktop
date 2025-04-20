#ifndef _NETWORKOPERATOR_H
#define _NETWORKOPERATOR_H

#include <string>

class Operator
{
public:
    virtual ~Operator() = default;
    virtual void sendToServer(std::string formattedMsg) {};
    virtual void dispatch_void(std::string event_name) {};
    virtual void dispatch_string(std::string event_name,std::string str){};
    virtual void dispatch_string_string_string(std::string event_name, std::string str1, std::string str2, std::string str3){};
    virtual void dispatch_bool(std::string event_name,bool status){};
};


#endif