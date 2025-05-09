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
#include "EventBus.h"
#include <QGraphicsDropShadowEffect>

DeviceWidget::DeviceWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceWidget)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/DeviceWidget/DeviceWidget.qss")),this);
    DeviceItem *device_item = new DeviceItem;
    auto *shadow = new QGraphicsDropShadowEffect(device_item);
    shadow->setBlurRadius(12);
    shadow->setOffset(0, 4);
    shadow->setColor(QColor(0, 0, 0, 30));
    device_item->setGraphicsEffect(shadow);
    QListWidgetItem *item = new QListWidgetItem("");
    item->setSizeHint(device_item->sizeHint());
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item,device_item);
    ui->listWidget->setSelectionMode(QAbstractItemView::NoSelection);
    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
        &DeviceWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
}

DeviceWidget::~DeviceWidget()
{
    delete ui;
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