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
#include "UserInfo.h"
#include "BubbleMessage.h"
#include "MoreDialog/MoreDialog.h"
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
    this->name = QString::fromStdString(name);
    QString device_name= comment.empty() ? QString::fromStdString(name) : QString::fromStdString(comment);
    if(UserInfoManager::getInstance().getCurrentUserId() == code.toStdString())
    {
        device_name = device_name.append("  (LocalHost)");
    }
    ui->label_device_name->setText(device_name);
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
    this->code = QString::fromStdString(code);
}

void DeviceItem::loadDeviceInfo(DevicelistManager::DeviceInfo& info)
{
    setDeviceCode(info.code);
    setDeviceName(info.device_name, info.comment);
    setDeviceIP(info.ip);
    if(UserInfoManager::getInstance().getCurrentUserId() == code.toStdString())
    {
        ui->btn_connect_to_device->hide();
    }
}

void DeviceItem::on_btn_connect_to_device_clicked()
{
    emit onConnect(code);
}

void DeviceItem::on_btn_more_clicked()
{
    MoreDialog* dialog = new MoreDialog(code,name,this);
    connect(dialog,&MoreDialog::copyDeviceInfo,this,[this](){
        emit copyDeviceInfo(ui->label_device_name->text().chopped(13), code, ui->label_ip->text().remove("   IP: "));
    });
    connect(dialog,&MoreDialog::editComment,this,[this](QString new_comment){
        if(UserInfoManager::getInstance().getUserConnectStatus())
        {
            std::string device_name = name.toStdString();
            std::string comment = new_comment.toStdString();
            setDeviceName(device_name, comment);
            emit editDeviceComment(code ,new_comment);
        }
        else
        {
            BubbleMessage::getInstance().error("Failed to connect User Server");
        }

    });
    connect(dialog,&MoreDialog::deleteDevice,this,[this](){
        if(UserInfoManager::getInstance().getUserConnectStatus())
        {
            emit deleteDevice(code);
        }
        else
        {
            BubbleMessage::getInstance().error("Failed to connect User Server");
        }
    });
    QPoint pos = ui->btn_more->mapToGlobal(QPoint(0, ui->btn_more->height()));
    dialog->move(pos);
    dialog->exec();
}