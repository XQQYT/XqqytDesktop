/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _NETWORKOPERATOR_H
#define _NETWORKOPERATOR_H

#include "EventBus.h"
#include <string>

class Operator
{
public:
    virtual ~Operator() = default;
    virtual void sendToServer(std::string formattedMsg) {};
    virtual void dispatch_void(EventBus::EventType event_name) {};
    virtual void dispatch_string(EventBus::EventType event_name,std::string str){};
    virtual void dispatch_string_string(EventBus::EventType event_name,std::string str1,std::string str2){};
    virtual void dispatch_string_string_string(EventBus::EventType event_name, std::string str1, std::string str2, std::string str3){};
    virtual void dispatch_bool(EventBus::EventType event_name,bool status){};
};


#endif