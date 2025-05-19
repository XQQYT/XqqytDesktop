/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "DeviceItem.h"
#include "ui_DeviceItem.h"
#include "utils.h"
#include "SettingInfo.h"
#include <iostream>

DeviceItem::DeviceItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceItem)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/DeviceWidget/DeviceItem/DeviceItem.qss")),this);
    setMinimumHeight(30);
}

DeviceItem::~DeviceItem()
{
    delete ui;
}

void DeviceItem::enterEvent(QEvent *event)
{

}

void DeviceItem::leaveEvent(QEvent *event)
{

}

void DeviceItem::retranslateUi()
{
    ui->retranslateUi(this);
}

void DeviceItem::setDeviceName(std::string& name, std::string& comment)
{
    ui->label_device_name->setText(comment.empty() ? QString::fromStdString(name) : QString::fromStdString(comment));
}

void DeviceItem::setDeviceIP(std::string& ip)
{
    ui->label_ip->setText("   IP: " + QString::fromStdString(ip));
}

void DeviceItem::setDeviceCode(std::string& code)
{
    QString code_qstring = QString::fromStdString(code);
    turnToRegularNum(code_qstring);
    ui->label_code->setText("Device Code: " + code_qstring);
}

void DeviceItem::loadDeviceInfo(DevicelistManager::DeviceInfo& info)
{
    setDeviceName(info.device_name, info.comment);
    setDeviceCode(info.code);
    setDeviceIP(info.ip);
}
