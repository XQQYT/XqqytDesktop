/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "ConnectWidget.h"
#include <QDateTime>
#include "utils.h"
#include "SettingInfo.h"
#include "ui_ConnectWidget.h"
#include <iostream>
#include <sstream>
#include "GlobalEnum.h"
#include "BubbleMessage.h"

ConnectWidget::ConnectWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ConnectWidget)
{
    remote_widget = nullptr;
    remote_widget_alive = false;
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/ConnectWidget.qss")),this);
    info_dialog.setPargentWidget(this);
    initSubscribe();

    update_dynamic_key_timer = new QTimer(this);
    connect(update_dynamic_key_timer, &QTimer::timeout, this, &ConnectWidget::onTimeToUpdateKey);
    setUpdateKeyTimer();

    connect(&key_authenticate_dialog,&KeyAuthenticationDialog::EnterDone,this,&ConnectWidget::onEnterKeyDone);

    EventBus::getInstance().publish("/ui/connectwidget_init_done");
}

ConnectWidget::~ConnectWidget()
{
    delete ui;
}

void ConnectWidget::initSubscribe()
{
    EventBus::getInstance().subscribe("/network/target_status",std::bind(&ConnectWidget::onTargetStatus,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/network/registration_result",std::bind(&ConnectWidget::onRegistrationResult,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/network/failed_to_connect_server",std::bind(&ConnectWidget::onConnectServerFailed,this));
    EventBus::getInstance().subscribe("/network/has_connect_request",std::bind(&ConnectWidget::onConnectRequest,this,std::placeholders::_1,std::placeholders::_2));
    EventBus::getInstance().subscribe("/network/recv_connect_request_result",std::bind(&ConnectWidget::onRecvConnectRequestResult,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/webrtc/connection_status",std::bind(&ConnectWidget::onConnectionStatus,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
        &ConnectWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe("/network/connect_to_user_server_result",std::bind(&ConnectWidget::onConnectUserServerResult,this,std::placeholders::_1));
    EventBus::getInstance().subscribe("/network/receive_device_code",std::bind(&ConnectWidget::onReceiveDeviceCode,this,std::placeholders::_1));
}

void ConnectWidget::setUpdateKeyTimer()
{
    if (update_dynamic_key_timer->isActive())
            update_dynamic_key_timer->stop();
    bool is_first_time = false;
    auto security_config = SettingInfoManager::getInstance().getModuleConfig("Security");
    std::string key_update_frequency = (*security_config)["key_update_frequency"];
    std::string last_key = (*security_config)["last_key"];

    QFont font = ui->btn_dynamic_key_value->font();
    font.setUnderline(false);
    if(key_update_frequency == "Manual")
    {
        UserInfoManager::getInstance().setCurrentUserKey(last_key);
        font.setUnderline(true);
        ui->btn_dynamic_key_value->setFont(font);
        ui->btn_dynamic_key_value->setCursor(Qt::PointingHandCursor);
        ui->btn_dynamic_key_value->setEnabled(true);
        return;
    }
    ui->btn_dynamic_key_value->setCursor(Qt::ArrowCursor);
    ui->btn_dynamic_key_value->setFont(font);
    ui->btn_dynamic_key_value->setEnabled(false);

    int last_update_timestamp;
    try{
        last_update_timestamp = std::stoi((*security_config)["last_update_timestamp"]);
    }
    catch(...){
        last_update_timestamp = -1;
    }

    //第一次生成
    if(last_update_timestamp < 0 || last_key.empty())
    {
        std::string new_key = generateRandomString(8).toStdString();
        UserInfoManager::getInstance().setCurrentUserKey(new_key);

        ui->btn_dynamic_key_value->setText(QString::fromStdString(new_key));
        qint64 timestamp = QDateTime::currentSecsSinceEpoch();
        last_update_timestamp = static_cast<int64_t>(timestamp);
        EventBus::getInstance().publish("/config/update_module_config",std::string("Security"),std::string("last_update_timestamp"),std::to_string(last_update_timestamp));
        EventBus::getInstance().publish("/config/update_module_config",std::string("Security"),std::string("last_key"),new_key);
        EventBus::getInstance().publish("/config/write_into_file");
        is_first_time = true;
    }

    int64_t remaining_time;
    qint64 now_timestamp = QDateTime::currentSecsSinceEpoch();
    if(key_update_frequency == "Every hours")
        remaining_time = (last_update_timestamp + 1 * 60 * 60) - now_timestamp;
    else if(key_update_frequency == "Every 12hours")
        remaining_time = (last_update_timestamp + 12 * 60 * 60) - now_timestamp;

    //当前已超出时间
    if(remaining_time < 0)
    {
        onTimeToUpdateKey();
    }
    else
    {
        if(!is_first_time)
            UserInfoManager::getInstance().setCurrentUserKey(last_key);
        if (update_dynamic_key_timer->isActive())
            update_dynamic_key_timer->stop();
        std::cout<<"remain "<<remaining_time<<" s"<<std::endl;
        update_dynamic_key_timer->start(remaining_time * 1000);
    }
}

void ConnectWidget::on_btn_connect_clicked()
{
    std::string target_id = ui->lineEdit_target_id->text().toStdString();
    EventBus::getInstance().publish("/network/get_target_status",target_id);
    SettingInfoManager::getInstance().updataModuleConfig("ConnectInfo","last_connect_id",target_id);
    EventBus::getInstance().publish("/config/write_into_file");
}

void ConnectWidget::onEnterKeyDone(QString key)
{
    UserInfoManager::getInstance().setCurrentRole(UserInfoManager::Role::Controller);
    std::string establishing_target_id = UserInfoManager::getInstance().getEstablishingTargetId();
    SettingInfoManager::getInstance().updataModuleConfig("ConnectInfo",establishing_target_id,key.toStdString());
    EventBus::getInstance().publish("/config/write_into_file");
    EventBus::getInstance().publish("/network/connect_to_target",establishing_target_id,key.toStdString());
}

void ConnectWidget::onTargetStatus(bool target_status)
{
    if(target_status)
    {
        std::string establishing_target_id = UserInfoManager::getInstance().getEstablishingTargetId();
        key_authenticate_dialog.show(SettingInfoManager::getInstance().getValue("ConnectInfo",establishing_target_id));
    }
    else
    {
        BubbleMessage::getInstance().error("Target is offline");
    }
}

void ConnectWidget::onRegistrationResult(bool result)
{
    if(!result)
    BubbleMessage::getInstance().error("RegistrationRejected");
}

void ConnectWidget::onConnectUserServerResult(bool result)
{
    if(result)
    {
        std::cout<<"连接用户服务器成功"<<std::endl;
        if(UserInfoManager::getInstance().getCurrentUserId().empty())
        {
            std::vector<std::string> args = {getDeviceName()};
            EventBus::getInstance().publish("/network/send_to_user_server",UserMsgType::RegisterDeviceCode,std::move(args)); 
        }
    }
}

void ConnectWidget::onConnectServerFailed()
{
    BubbleMessage::getInstance().error("Failed to connect Server");
}

void ConnectWidget::onConnectRequest(std::string target_id, std::string key)
{
    if(key != UserInfoManager::getInstance().getCurrentUserKey())
    {
        EventBus::getInstance().publish("/network/send_connect_request_result",target_id,false);
        return;
    }
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
        UserInfoManager::getInstance().setCurrentRole(UserInfoManager::Role::UN_DEFINED);
        QMetaObject::invokeMethod(this, [this]() {
            reconnect(&info_dialog,&InfoDialog::OK,this,[](){
                std::cout<<"test"<<std::endl;
            });
            info_dialog <<"Connection Response"<<"The peer rejected your connection request. Possible reasons include:\n1,Password authentication failed.\n2,The peer explicitly denied the connection."<< InfoDialog::InfoType::OK << InfoDialog::end;
        }, Qt::QueuedConnection);
    }
}
void ConnectWidget::onConnectionStatus(bool status)
{
    if(status)
    {
        UserInfoManager::getInstance().setCurrentTargetId(UserInfoManager::getInstance().getEstablishingTargetId());
        if(!remote_widget_alive && UserInfoManager::getInstance().getCurrentRole() == UserInfoManager::Role::Controller)
        {
            QMetaObject::invokeMethod(this, [this]() {
                std::cout<<"new a remote widget"<<std::endl;
                remote_widget = new RemoteControlWidget;
                remote_widget->show();
                connect(remote_widget,&RemoteControlWidget::remote_widget_closed,this,[this](){
                    std::cout<<"reset remote_widget_alive"<<std::endl;
                    remote_widget_alive = false;
                });
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

void ConnectWidget::onSettingChanged(std::string module, std::string key, std::string value)
{
    std::cout<<"on changed 5"<<module<<" "<<key<<" "<<value<<std::endl;
    if(key == "theme")
    {
        std::cout<<"change theme "<<std::endl;
        QMetaObject::invokeMethod(this, [=]() {
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/ConnectWidget.qss")),this);
        }, Qt::QueuedConnection);
    }
    else if(key == "language")
    {
        QMetaObject::invokeMethod(this, [=]() {
            ui->retranslateUi(this);
            QString new_code = QString::fromStdString(UserInfoManager::getInstance().getCurrentUserId());
            turnToRegularNum(new_code);
            ui->label_user_id_value->setText(new_code);
            ui->lineEdit_target_id->setText(QString::fromStdString(SettingInfoManager::getInstance().getValue("ConnectInfo","last_connect_id")));
            ui->btn_dynamic_key_value->setText(QString::fromStdString(UserInfoManager::getInstance().getCurrentUserKey()));
        }, Qt::QueuedConnection);
    }
    else if(key == "key_update_frequency")
    {
        QMetaObject::invokeMethod(this, [=]() {
            setUpdateKeyTimer();
        }, Qt::QueuedConnection);
    }
}

void ConnectWidget::onTimeToUpdateKey()
{
    std::string new_dynamic_key = generateRandomString(8).toStdString();
    ui->btn_dynamic_key_value->setText(QString::fromStdString(new_dynamic_key));
    UserInfoManager::getInstance().setCurrentUserKey(new_dynamic_key);
    EventBus::getInstance().publish("/config/update_module_config",std::string("Security"),std::string("last_key"),new_dynamic_key);
    qint64 timestamp = QDateTime::currentSecsSinceEpoch();
    int64_t last_update_timestamp = static_cast<int64_t>(timestamp);
    EventBus::getInstance().publish("/config/update_module_config",std::string("Security"),std::string("last_update_timestamp"),std::to_string(last_update_timestamp));
    EventBus::getInstance().publish("/config/write_into_file");
    if(update_dynamic_key_timer->isActive())
        resetUpdateKeyTimer(last_update_timestamp);
}

void ConnectWidget::resetUpdateKeyTimer(int64_t last_update_timestamp)
{
    std::string key_update_frequency = SettingInfoManager::getInstance().getValue("Security","key_update_frequency");

    uint64_t remaining_time;
    if(key_update_frequency == "Every hours")
        remaining_time = 1 * 60 * 60;
    else if(key_update_frequency == "Every 12hours")
        remaining_time = 12 * 60 * 60;

    if (update_dynamic_key_timer->isActive())
        update_dynamic_key_timer->stop();
    update_dynamic_key_timer->start(remaining_time * 1000);
}

void ConnectWidget::on_btn_dynamic_key_value_clicked()
{
    onTimeToUpdateKey();
}

void ConnectWidget::on_btn_share_clicked()
{
    std::string userid = ui->label_user_id_value->text().toStdString();
    std::string dynamic_key = ui->btn_dynamic_key_value->text().toStdString();
    std::ostringstream ss;
    ss << "I invite you to remote control\n"
    << "XqqytDesktop ID: " << userid << "\n"
    << "Dynamic Key: " << dynamic_key;
    std::string share_content = ss.str();
    EventBus::getInstance().publish("/clipboard/write_into_clipboard", std::move(share_content));
    BubbleMessage::getInstance().show("The sharing information has been copied to the clipboard");
}

void ConnectWidget::onReceiveDeviceCode(std::string code)
{
    QMetaObject::invokeMethod(this, [this, code = std::move(code)]() {
        QString new_code = QString::fromStdString(code);
        turnToRegularNum(new_code);
        ui->label_user_id_value->setText(new_code);
    }, Qt::QueuedConnection);
}