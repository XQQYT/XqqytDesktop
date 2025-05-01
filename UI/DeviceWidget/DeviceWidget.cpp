#include "DeviceWidget.h"
#include "ui_DeviceWidget.h"
#include "utils.h"
#include "SettingInfo.h"
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
}

DeviceWidget::~DeviceWidget()
{
    delete ui;
}
