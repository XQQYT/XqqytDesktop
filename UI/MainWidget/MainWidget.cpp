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
    EventBus::getInstance().publish("/ui/mainwidget_init_done");
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
    EventBus::getInstance().subscribe("/network/recv_connect_request_result",std::bind(&MainWidget::onRecvConnectRequestResult,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/webrtc/connection_status",std::bind(&MainWidget::onConnectionStatus,this,std::placeholders::_1));
}

void MainWidget::on_btn_connect_clicked()
{
    EventBus::getInstance().publish("/network/connect_to_target",
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
    QMetaObject::invokeMethod(this, [this,target_id]() {
    ConfirmBeConnectDialog dialog(this);
    connect(&dialog,&ConfirmBeConnectDialog::acceptConnection,this,[=](){
        EventBus::getInstance().publish("/network/send_connect_request_result",target_id,true);
    });
    connect(&dialog,&ConfirmBeConnectDialog::rejectConnection,this,[=](){
        EventBus::getInstance().publish("/network/send_connect_request_result",target_id,false);
    });
    dialog.exec();
    }, Qt::QueuedConnection);
}

void MainWidget::onRecvConnectRequestResult(bool status)
{
    if (!status)
    {
        QMetaObject::invokeMethod(this, [this]() {
            reconnect(&info_dialog,&InfoDialog::OK,this,[](){
                std::cout<<"test"<<std::endl;
            });
            info_dialog <<"Info"<<"The Peer reject your connect request"<< InfoDialog::InfoType::OK << InfoDialog::end;
        }, Qt::QueuedConnection);
    }
}
void MainWidget::onConnectionStatus(bool status)
{
    if(status)
    {
        std::cout<<"Connection successed"<<std::endl;
    }
    else
    {
        std::cout<<"Connection failed"<<std::endl;
    }
}