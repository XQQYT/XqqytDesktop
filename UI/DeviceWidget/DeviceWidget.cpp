/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "DeviceWidget.h"
#include "ui_DeviceWidget.h"
#include "utils.h"
#include "SettingInfo.h"
#include "WidgetManager.h"
#include "EventBus.h"
#include <QGraphicsDropShadowEffect>
#include <sstream>
#include "BubbleMessage.h"

DeviceWidget::DeviceWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceWidget)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/DeviceWidget/DeviceWidget.qss")),this);
    ui->listWidget->setSpacing(5);

    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
        &DeviceWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe("/network/update_device_list",std::bind(
        &DeviceWidget::onDeviceListUpdated,
        this
    ));
}

DeviceWidget::~DeviceWidget()
{
    delete ui;
}

DeviceItem* DeviceWidget::createDeviceItem()
{
    DeviceItem *device_item = new DeviceItem;
    auto *shadow = new QGraphicsDropShadowEffect(device_item);
    shadow->setBlurRadius(12);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 30));
    device_item->setGraphicsEffect(shadow);
    return device_item;
}

void DeviceWidget::onSettingChanged(std::string module, std::string key, std::string value)
{
    if(key == "theme")
    {
        QMetaObject::invokeMethod(this, [=]() {
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/DeviceWidget/DeviceWidget.qss")),this);
            for (int i = 0; i < ui->listWidget->count(); ++i) {
                QListWidgetItem* item = ui->listWidget->item(i);
                if (item) {
                    QWidget* widget = ui->listWidget->itemWidget(item); // 获取 item 对应的 widget
                    if (widget) {
                        applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/DeviceWidget/DeviceItem/DeviceItem.qss")),widget);
                    }
                }
            }
        }, Qt::QueuedConnection);
    }
    else if(key == "language")
    {
        QMetaObject::invokeMethod(this, [=]() {
            ui->retranslateUi(this);
            onDeviceListUpdated();
            for (int i = 0; i < ui->listWidget->count(); ++i) {
                QListWidgetItem* item = ui->listWidget->item(i);
                if (item) {
                    DeviceItem* device_item = dynamic_cast<DeviceItem*>(ui->listWidget->itemWidget(item));
                    if (device_item) {
                        device_item->retranslateUi();
                    }
                }
            }
        }, Qt::QueuedConnection);
    }
}

void DeviceWidget::addDeviceUI(DevicelistManager::DeviceInfo& info)
{
    auto device_item = createDeviceItem();
    device_item->loadDeviceInfo(info);

    connect(device_item,&DeviceItem::onConnect,this,&DeviceWidget::onConnectFromItem);
    connect(device_item,&DeviceItem::copyDeviceInfo,this,&DeviceWidget::onCopyDeviceInfo);
    connect(device_item,&DeviceItem::editDeviceComment,this,&DeviceWidget::onEditDeviceComment);
    connect(device_item,&DeviceItem::deleteDevice,this,&DeviceWidget::onDeleteDevice);

    QListWidgetItem *item = new QListWidgetItem("");
    item->setSizeHint(device_item->sizeHint());
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,device_item);
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
}

void DeviceWidget::onDeviceListUpdated()
{
    connect(this,&DeviceWidget::ConnectFromDevice,&WidgetManager::getInstance(),&WidgetManager::ConnectFromDevice, Qt::UniqueConnection);
    QMetaObject::invokeMethod(this, [=]() {
        ui->listWidget->clear();
        auto device_list =  DevicelistManager::getInstance().getDeviceInfo();
        for(auto& device : device_list)
        {
            addDeviceUI(device);
        }
        update();
    }, Qt::QueuedConnection);

}

void DeviceWidget::onConnectFromItem(QString code)
{
    emit ConnectFromDevice(code);
}

void DeviceWidget::onCopyDeviceInfo(QString device_name, QString device_code, QString device_ip)
{
    std::string username = UserInfoManager::getInstance().getUserName();
    std::string devicename = device_name.toStdString();
    std::string devicecode = device_code.toStdString();
    std::string deviceip = device_ip.toStdString();
    std::ostringstream ss;
    ss << "Device information:\n"
    << "User name: " << username << "\n"
    << "Device name: "<< devicename<<"\n"
    << "Device code: " << devicecode<<"\n"
    << "Device ip: "<<deviceip;
    std::string share_content = ss.str();
    EventBus::getInstance().publish("/clipboard/write_into_clipboard", std::move(share_content));
    BubbleMessage::getInstance().show("The sharing information has been copied to the clipboard");
}

void DeviceWidget::onEditDeviceComment(QString code, QString new_comment)
{
    std::cout<<"edit "<<code.toStdString() <<" "<<new_comment.toStdString()<<std::endl;
}

void DeviceWidget::onDeleteDevice(QString code)
{
    std::cout<<"delete "<<code.toStdString()<<std::endl;
}