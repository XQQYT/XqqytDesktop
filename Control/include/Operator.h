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
};


#endif