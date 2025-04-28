#include "GeneralWidget.h"
#include "ui_GeneralWidget.h"

GeneralWidget::GeneralWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralWidget)
{
    ui->setupUi(this);
}

GeneralWidget::~GeneralWidget()
{
    delete ui;
}
