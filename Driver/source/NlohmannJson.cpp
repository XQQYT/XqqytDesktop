#include "NlohmannJson.h"

NlohmannJson::NlohmannJson()
{

}

NlohmannJson::~NlohmannJson()
{

}

std::shared_ptr<std::string> NlohmannJson::ws_register(const std::string&& id)
{
    json msg={{"type", "register"},{"id",id}};
    return std::make_shared<std::string>(msg.dump());
}