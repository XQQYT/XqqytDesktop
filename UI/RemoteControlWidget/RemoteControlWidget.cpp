#include "RemoteControlWidget.h"
#include "ui_RemoteControlWidget.h"

RemoteControlWidget::RemoteControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RemoteControlWidget)
{
    ui->setupUi(this);
    auto i = new OpenGLWidget(this);
    auto layout = this->layout();
    layout->addWidget(i);
}

RemoteControlWidget::~RemoteControlWidget()
{
    delete ui;
}

