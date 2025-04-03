#include "MainWidget.h"
#include "ui_MainWidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    w=nullptr;
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_clicked()
{
    if(w==nullptr)
    {
        w=new RemoteControlWidget();
        w->show();
    }
}

