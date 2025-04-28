#include "NetworkWidget.h"
#include "ui_NetworkWidget.h"

NetworkWidget::NetworkWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkWidget)
{
    ui->setupUi(this);
}

NetworkWidget::~NetworkWidget()
{
    delete ui;
}
