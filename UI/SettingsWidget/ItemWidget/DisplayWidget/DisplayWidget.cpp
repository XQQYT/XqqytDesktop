#include "DisplayWidget.h"
#include "ui_DisplayWidget.h"

DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}
