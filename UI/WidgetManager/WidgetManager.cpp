#include "WidgetManager.h"

WidgetManager::WidgetManager()
{
    initWidget();
}

WidgetManager::~WidgetManager()
{
    
}

void WidgetManager::initWidget()
{
    widget_map[WidgetType::ConnectWidget] = new ConnectWidget();
    widget_map[WidgetType::DeviceWidget] = new DeviceWidget();
}

QWidget* WidgetManager::getWidget(const WidgetType type)
{
    return widget_map[type];
}

void WidgetManager::closeAllWidget()
{
    for(auto& widget_ptr : widget_map)
    {
        widget_ptr->close();
    }
}
