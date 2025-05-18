#ifndef _USERSERVERMSGPARSER_H
#define _USERSERVERMSGPARSER_H

#include <vector>
#include <stdint.h>
#include <memory>
#include "NlohmannJson.h"

class UserServerMsgParser
{
public:
    UserServerMsgParser();
    ~UserServerMsgParser();
    void ParseMsg(std::vector<uint8_t> msg, bool is_binary);
private:
    std::unique_ptr<JsonFactory> json_interface;
};


#endif //_USERSERVERMSGPARSER_H