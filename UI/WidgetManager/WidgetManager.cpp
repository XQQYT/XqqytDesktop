#include "WidgetManager.h"

WidgetManager::WidgetManager()
{
    initWidget();
}

WidgetManager::~WidgetManager()
{
    for(auto& widget_ptr : widget_map)
    {
        widget_ptr->close();
    }
}

void WidgetManager::initWidget()
{
    widget_map["ConnectWidget"] = new ConnectWidget();
}

QWidget* WidgetManager::getWidget(const WidgetType type)
{
    QString widget_name = std::move(typeToStiring(type));
    if(widget_name.isEmpty())
    {
        std::cout<<"Invalid Widget Type"<<std::endl;
        return nullptr;
    }
    return widget_map[widget_name];
}

QString WidgetManager::typeToStiring(const WidgetType type)
{
    switch(type)
    {
        case WidgetType::Connect_Widget:
            return "ConnectWidget";
            break;
        default:
            return "";
            break;
    }
}