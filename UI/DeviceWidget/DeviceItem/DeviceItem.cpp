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