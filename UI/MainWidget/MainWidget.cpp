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
    EventBus::getInstance().publish("/ui/mainwidget_init_done",std::string("7788"));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::initSubscribe()
{
    EventBus::getInstance().subscribe("/network/target_is_offline",std::bind(&MainWidget::onTargetOffline,this));
    EventBus::getInstance().subscribe("/network/registration_rejected",std::bind(&MainWidget::onRegistrationRejected,this));
    EventBus::getInstance().subscribe("/network/failed_to_connect_server",std::bind(&MainWidget::onConnectServerFailed,this));
    EventBus::getInstance().subscribe("/network/has_connect_request",std::bind(&MainWidget::onConnectRequest,this,std::placeholders::_1));
}

void MainWidget::on_btn_connect_clicked()
{
    EventBus::getInstance().publish("/network/connect_to_target",
        ui->lineEdit_id->text().toStdString(),
        ui->lineEdit_target_id->text().toStdString());
}

void MainWidget::onTargetOffline()
{
    bubble_message.error(this, "Target is offline");
}

void MainWidget::onRegistrationRejected()
{
    bubble_message.error(this,"RegistrationRejected");
}

void MainWidget::onConnectServerFailed()
{
    bubble_message.error(this,"Failed to connect Server");
}

void MainWidget::onConnectRequest(std::string target_id)
{
    QMetaObject::invokeMethod(this, [this]() {
    ConfirmBeConnectDialog dialog(this);
    connect(&dialog,&ConfirmBeConnectDialog::acceptConnection,this,[=](){
        std::cout<<"accept"<<std::endl;
    });
    connect(&dialog,&ConfirmBeConnectDialog::rejectConnection,this,[=](){
        std::cout<<"reject"<<std::endl;
    });
    dialog.exec();
    }, Qt::QueuedConnection);
}