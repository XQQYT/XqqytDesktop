#include "RemoteControlWidget.h"
#include "ui_RemoteControlWidget.h"

RemoteControlWidget::RemoteControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RemoteControlWidget)
{
    ui->setupUi(this);
}

RemoteControlWidget::~RemoteControlWidget()
{
    delete ui;
}

