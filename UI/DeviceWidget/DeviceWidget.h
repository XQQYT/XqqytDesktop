/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>
#include "DeviceItem/DeviceItem.h"
#include "DevicelistManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceWidget; }
QT_END_NAMESPACE

class DeviceWidget : public QWidget
{
    Q_OBJECT

public:
    DeviceWidget(QWidget *parent = nullptr);
    ~DeviceWidget();
signals:
    void ConnectFromDevice(QString code);
private:
    void onDeviceListUpdated();
    void onSettingChanged(std::string module, std::string key, std::string value);
    void onConnectFromItem(QString code);
    void addDeviceUI(DevicelistManager::DeviceInfo& info);
    DeviceItem * createDeviceItem();
private:
    Ui::DeviceWidget *ui;
};
#endif // DEVICEWIDGET_H
