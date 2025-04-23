#include "DeviceItem.h"
#include "ui_DeviceItem.h"
#include <iostream>

DeviceItem::DeviceItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DeviceItem)
{
    ui->setupUi(this);
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