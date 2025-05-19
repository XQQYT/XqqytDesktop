/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include <QWidget>
#include <QStyle>
#include "DevicelistManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceItem; }
QT_END_NAMESPACE

class DeviceItem : public QWidget
{
    Q_OBJECT

public:
    DeviceItem(QWidget *parent = nullptr);
    ~DeviceItem();
    void retranslateUi();
    void setDeviceName(std::string& name, std::string& comment);
    void setDeviceIP(std::string& ip);
    void setDeviceCode(std::string& code);
    void loadDeviceInfo(DevicelistManager::DeviceInfo& info);
signals:
    void onConnect(QString code);
private slots:
    void on_btn_connect_to_device_clicked();
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    Ui::DeviceItem *ui;
    QString code;
};
#endif // DEVICEITEM_H
