#include "NlohmannJson.h"

NlohamnnJson::NlohamnnJson()
{

}

NlohamnnJson::~NlohamnnJson()
{

}

std::shared_ptr<std::string> NlohamnnJson::ws_register(const std::string&& id)
{
    json msg={{"type", "register"},{"id",id}};
    return std::make_shared<std::string>(msg.dump());
}