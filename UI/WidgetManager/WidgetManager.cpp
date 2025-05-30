/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

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
    widget_map[WidgetType::SettingsWidget] = new SettingsWidget();
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
        delete widget_ptr;
        widget_ptr = nullptr;
    }
}

void WidgetManager::ConnectFromDevice(QString code)
{
    emit transConnectFromDevice(code);
}