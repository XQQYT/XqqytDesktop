/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _WIDGETMANAGER_H
#define _WIDGETMANAGER_H

#include "ConnectWidget.h"
#include "DeviceWidget.h"
#include "SettingsWidget.h"
#include <QMap>
#include <iostream>

class WidgetManager : public QObject
{
public:
    enum class WidgetType
    {
        UnDefined,
        ConnectWidget,
        DeviceWidget,
        SettingsWidget
    };
    Q_OBJECT
public:
    WidgetManager(const WidgetManager&) = delete;
    WidgetManager& operator=(const WidgetManager&) = delete;
    static WidgetManager& getInstance()
    {
        static WidgetManager widget_manager;
        return widget_manager;
    }
    QWidget* getWidget(const WidgetType type);
    ~WidgetManager();
    void closeAllWidget();
private:
    WidgetManager();
    void initWidget();
private:
    QMap<WidgetType,QWidget*> widget_map;
};

#endif