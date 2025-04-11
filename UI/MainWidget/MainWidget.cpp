#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    w=nullptr;
    ui->setupUi(this);

    this->setFixedSize(800, 600);
    this->setGeometry(QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    this->size(),
    QGuiApplication::primaryScreen()->availableGeometry()
));
    initSubscribe();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initSubscribe()
{
    EventBus::getInstance().subscribe("/network/target_is_offline",std::bind(&MainWidget::onTargetOffline,this));
    EventBus::getInstance().subscribe("/network/registration_rejected",std::bind(&MainWidget::onRegistrationRejected,this));
}

void MainWidget::on_btn_connect_clicked()
{
    EventBus::getInstance().publish("/network/connect_to_server_and_target",
        ui->lineEdit_id->text().toStdString(),
        ui->lineEdit_target_id->text().toStdString());
}

void MainWidget::onTargetOffline()
{
    std::cout<<"target is offline"<<std::endl;
    bubble_message.error(this,"Target is offline");
}

void MainWidget::onRegistrationRejected()
{
    std::cout<<"registration is rejected"<<std::endl;
    bubble_message.error(this,"Target is offline");

}