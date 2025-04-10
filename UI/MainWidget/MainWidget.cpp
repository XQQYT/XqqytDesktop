#include "MainWidget.h"
#include "ui_MainWidget.h"

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

void MainWidget::on_btn_connect_clicked()
{
    EventBus::getInstance().publish("/network/connect_to_server_and_target",
        ui->lineEdit_id->text().toStdString(),
        ui->lineEdit_target_id->text().toStdString());
}

