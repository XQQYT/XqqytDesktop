#include "ConnectWidget.h"
#include "ui_ConnectWidget.h"

ConnectWidget::ConnectWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConnectWidget)
{
    remote_widget = nullptr;
    remote_widget_alive = false;
    ui->setupUi(this);

    this->setFixedSize(800, 600);
    this->setGeometry(QStyle::alignedRect(
    Qt::LeftToRight,
    Qt::AlignCenter,
    this->size(),
    QGuiApplication::primaryScreen()->availableGeometry()
));
    initSubscribe();
    EventBus::getInstance().publish("/ui/connectwidget_init_done");
}

ConnectWidget::~ConnectWidget()
{
    delete ui;
}

void ConnectWidget::initSubscribe()
{
    EventBus::getInstance().subscribe("/network/target_is_offline",std::bind(&ConnectWidget::onTargetOffline,this));
    EventBus::getInstance().subscribe("/network/registration_rejected",std::bind(&ConnectWidget::onRegistrationRejected,this));
    EventBus::getInstance().subscribe("/network/failed_to_connect_server",std::bind(&ConnectWidget::onConnectServerFailed,this));
    EventBus::getInstance().subscribe("/network/has_connect_request",std::bind(&ConnectWidget::onConnectRequest,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/network/recv_connect_request_result",std::bind(&ConnectWidget::onRecvConnectRequestResult,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/webrtc/connection_status",std::bind(&ConnectWidget::onConnectionStatus,this,std::placeholders::_1));
}

void ConnectWidget::on_btn_connect_clicked()
{
    EventBus::getInstance().publish("/network/connect_to_target",
        ui->lineEdit_target_id->text().toStdString());
    UserInfoManager::getInstance().setCurrentRole(UserInfoManager::Role::Controller);
}

void ConnectWidget::onTargetOffline()
{
    bubble_message.error(this, "Target is offline");
}

void ConnectWidget::onRegistrationRejected()
{
    bubble_message.error(this,"RegistrationRejected");
}

void ConnectWidget::onConnectServerFailed()
{
    bubble_message.error(this,"Failed to connect Server");
}

void ConnectWidget::onConnectRequest(std::string target_id)
{
    QMetaObject::invokeMethod(this, [this,target_id]() {
    ConfirmBeConnectDialog dialog(this);
    connect(&dialog,&ConfirmBeConnectDialog::acceptConnection,this,[=](){
        EventBus::getInstance().publish("/network/send_connect_request_result",target_id,true);
        UserInfoManager::getInstance().setCurrentRole(UserInfoManager::Role::BeControlled);

    });
    connect(&dialog,&ConfirmBeConnectDialog::rejectConnection,this,[=](){
        EventBus::getInstance().publish("/network/send_connect_request_result",target_id,false);
    });
    dialog.exec();
    }, Qt::QueuedConnection);
}

void ConnectWidget::onRecvConnectRequestResult(bool status)
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
void ConnectWidget::onConnectionStatus(bool status)
{
    if(status)
    {
        if(!remote_widget_alive && UserInfoManager::getInstance().getCurrentRole() == UserInfoManager::Role::Controller)
        {
            QMetaObject::invokeMethod(this, [this]() {
                std::cout<<"new a remote widget"<<std::endl;
                remote_widget = new RemoteControlWidget;
                remote_widget->show();
            }, Qt::QueuedConnection);
            remote_widget_alive = true;
        }
        std::cout<<"Connection successed"<<std::endl;
    }
    else
    {
        std::cout<<"Connection failed"<<std::endl;
    }
}