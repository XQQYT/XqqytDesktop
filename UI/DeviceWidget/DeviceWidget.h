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
    void clearDevices();
signals:
    void ConnectFromDevice(QString code);
private:
    void onDeviceListUpdated();
    void onSettingChanged(std::string module, std::string key, std::string value);
    void onConnectFromItem(QString code);
    void addDeviceUI(DevicelistManager::DeviceInfo& info);
    DeviceItem * createDeviceItem();
    void onCopyDeviceInfo(QString device_name, QString device_code, QString device_ip);
    void onEditDeviceComment(QString code, QString new_comment);
    void onDeleteDevice(QString code);
    void onUpdateDeviceCommentResult(bool result);
    void onDeleteDeviceResult(bool result);
private:
    Ui::DeviceWidget *ui;
    QString code_need_to_delete;
};
#endif // DEVICEWIDGET_H
