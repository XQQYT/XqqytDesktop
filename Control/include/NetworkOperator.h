#ifndef _NETWORKOPERATOR_H
#define _NETWORKOPERATOR_H

#include <string>

class NetworkOperator
{
public:
    virtual ~NetworkOperator() = default;
    virtual void sendToServer(std::string formattedMsg) = 0;
    virtual void dispatch_void(const std::string event_name) = 0;
};


#endif