#ifndef _WIDGETMANAGER_H
#define _WIDGETMANAGER_H

#include "ConnectWidget.h"
#include <QMap>
#include <iostream>

class WidgetManager : public QObject
{
public:
    enum class WidgetType
    {
        Connect_Widget
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
    QString typeToStiring(const WidgetType type);
    ~WidgetManager();
private:
    WidgetManager();
    void initWidget();
private:
    QMap<QString,QWidget*> widget_map;
};

#endif