#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "RemoteControlWidget.h"
#include "SettingInfo.h"
#include "utils.h"
#include <QDebug>
#include <QTranslator>
#include "GlobalEnum.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    BubbleMessage::getInstance().setDefaultWidget(this);
    DialogOperator::setDefaultWidget(this);
    translator = nullptr;
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/MainWidget.qss")),this);
    current_widget = WidgetManager::WidgetType::UnDefined;
    current_btn = ui->btn_connection;
    this->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    
    login_dialog = new LoginDialog(this);

    connect(login_dialog,&LoginDialog::EnterDone,this,&MainWidget::onEnterLoginDone);
    connect(login_dialog,&LoginDialog::RegisterEnterDone,this,&MainWidget::onEnterRegisterDone);
    connect(this, &MainWidget::LoginResult, login_dialog, &LoginDialog::onLoginResult);
    connect(this, &MainWidget::RegisterResult, &login_dialog->register_dialog, &RegisterDialog::onRegisterResult);
    
    connect(&WidgetManager::getInstance(),&WidgetManager::transConnectFromDevice,this,&MainWidget::onConnectFromDevice);

    initSubscribe();

    setCurrentWidget(WidgetManager::WidgetType::ConnectWidget);
    // 居中窗口
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = screenGeometry.x() + (screenGeometry.width() - this->width()) / 2;
    int y = screenGeometry.y() + (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);

    loadUserInfo(SettingInfoManager::getInstance().getValue("User","user_name"));
    switchLanguage(SettingInfoManager::getInstance().getValue("General","language"));
}

void MainWidget::initSubscribe()
{
    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
        &MainWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));

    EventBus::getInstance().subscribe("/network/login_result",std::bind(
        &MainWidget::onLoginResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/register_result",std::bind(
        &MainWidget::onRegisterResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/user_avatar_update",std::bind(
        &MainWidget::onUserAvatarUpdated,
        this
    ));
    EventBus::getInstance().subscribe("/network/upload_avatar_result",std::bind(
        &MainWidget::onUploadUserAvatarResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/update_username_result",std::bind(
        &MainWidget::onUserNameUpdateResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().subscribe("/network/update_user_password_result",[this](bool result){
        if(result)
            BubbleMessage::getInstance().show("Update password success!");
        else
            BubbleMessage::getInstance().error("Failed to update password");
    });
    EventBus::getInstance().subscribe("/network/register_device_result",[this](bool result){
        if(!result)
            BubbleMessage::getInstance().error("Failed to register device");
    });
    EventBus::getInstance().subscribe("/network/get_device_list_result",[this](bool result){
        if(!result)
            BubbleMessage::getInstance().error("Failed to get device list");
    });
}

MainWidget::~MainWidget()
{
    EventBus::getInstance().publish("/network/send_logout");
    WidgetManager::getInstance().closeAllWidget();
    delete ui;
}

void MainWidget::setCurrentWidget(const WidgetManager::WidgetType type)
{
    static bool is_first = true;
    if(current_widget == type)
        return;
    QWidget* new_widget = WidgetManager::getInstance().getWidget(type);
    if(!new_widget)
    {
        std::cout<<"New Widget is null"<<std::endl;
    }

    if(is_first)
    {
        EventBus::getInstance().publish("/config/update_module_config_done",std::string("General"),std::string("language"),SettingInfoManager::getInstance().getValue("General","language"));
        is_first = false;
    }
    QLayout* layout = ui->right_content_widget->layout();

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* old_widget = item->widget()) {
            old_widget->hide();
            old_widget->setParent(nullptr);
        }
        delete item;
    }

    layout->addWidget(new_widget);
    new_widget->show();
    current_widget = type;
}

void MainWidget::on_btn_device_clicked(bool checked)
{
    if(current_btn == ui->btn_device && !checked)
    {
        ui->btn_device->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    current_btn = ui->btn_device;
    setCurrentWidget(WidgetManager::WidgetType::DeviceWidget);
    current_btn = ui->btn_device;
}

void MainWidget::on_btn_connection_clicked(bool checked)
{
    if(current_btn == ui->btn_connection && !checked)
    {
        ui->btn_connection->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    setCurrentWidget(WidgetManager::WidgetType::ConnectWidget);
    current_btn = ui->btn_connection;

}

void MainWidget::on_btn_settings_clicked(bool checked)
{
    if(current_btn == ui->btn_settings && !checked)
    {
        ui->btn_settings->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    setCurrentWidget(WidgetManager::WidgetType::SettingsWidget);
    current_btn = ui->btn_settings;
}

void MainWidget::switchLanguage(const std::string language)
{
    if (translator) {
        qApp->removeTranslator(translator);
        delete translator;
        translator = nullptr;
    }

    // 加载新的翻译器
    translator = new QTranslator(qApp);
    if (translator->load(QString("Translations/XqqytDesktop_%1").arg(QString::fromStdString(language)))) {
        qApp->installTranslator(translator);
    }
    ui->retranslateUi(this);
}

void MainWidget::onSettingChanged(std::string module, std::string key, std::string value)
{
    if(key == "theme")
    {
        QMetaObject::invokeMethod(this, [=]() {
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/MainWidget.qss")),this);
        }, Qt::QueuedConnection);
    }
    else if(key == "language")
    {
        QMetaObject::invokeMethod(this, [=]() {
            switchLanguage((value));
            updateUserNameBtn();
        }, Qt::QueuedConnection);
    }
}

void MainWidget::updateUserNameBtn()
{
    std::string user_name = UserInfoManager::getInstance().getUserName();
    if("null" == user_name)
    {
        ui->btn_username->setText("Click here to login");
        ui->btn_username->setStyleSheet(R"(
        QPushButton {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                            stop:0 #ffa726, stop:1 #fb8c00);
            color: white;
            padding: 6px 12px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #f57c00;
        }
        QPushButton:pressed {
            background-color: #ef6c00;
        }
        )");
    }
    else
    {
        setButtonTextWithElide(ui->btn_username, QString::fromStdString(user_name));
        ui->btn_username->setStyleSheet(R"(
        QPushButton {
            background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                                            stop:0 #66bb6a, stop:1 #43a047);
            color: white;
            padding: 6px 12px;
            border: none;
            border-radius: 6px;
            font-weight: bold;
            font-size: 14px;
        }
        QPushButton:hover {
            background-color: #388e3c;
        }
        QPushButton:pressed {
            background-color: #2e7d32;
        }
        )");

    }
    update();
}

void MainWidget::loadUserInfo(std::string user_name)
{
    QString user_name_qstring = QString::fromStdString(user_name);
    ui->btn_username->setText(user_name_qstring);
    QLabel* label_avatar = ui->label_avatar;
    QPixmap avatar(QString("User/Avatar/") + user_name_qstring);
    QPixmap circular = createCircularPixmap(avatar, label_avatar->width());
    label_avatar->setPixmap(circular);

    UserInfoManager::getInstance().setUserName(std::move(user_name));
}

void MainWidget::on_btn_username_clicked()
{
    std::string current_user_name = UserInfoManager::getInstance().getUserName();
    if(current_user_name == "null")
    {
        DialogOperator::centerDialog(*login_dialog);
        login_dialog->exec();
    }
    else
    {
        UserProfileWidget* personal_center = new UserProfileWidget(this);
        connect(personal_center,&UserProfileWidget::logout,this,[=](){
            EventBus::getInstance().publish("/config/update_module_config",std::string("User"),std::string("user_name"),std::string("null"), true);
            loadUserInfo("null");
            updateUserNameBtn();
            dynamic_cast<DeviceWidget*>(WidgetManager::getInstance().getWidget(WidgetManager::WidgetType::DeviceWidget))->clearDevices();
        });
        personal_center->exec();
        DialogOperator::centerDialog(*personal_center);
    }
}

void MainWidget::onEnterLoginDone(QString username, QString password)
{
    if(UserInfoManager::getInstance().getUserConnectStatus())
    {
        std::vector<std::string> args = {username.toStdString(), password.toStdString(),UserInfoManager::getInstance().getCurrentUserId()};
        EventBus::getInstance().publish("/network/send_to_user_server",UserMsgType::LOGIN, std::move(args));
    }
    else
    {
        BubbleMessage::getInstance().error("Failed to connect User Server");
    }
}

void MainWidget::onEnterRegisterDone(QString username, QString password, QString avatar_path)
{  
    if(UserInfoManager::getInstance().getUserConnectStatus())
    {
        std::vector<std::string> args = {username.toStdString(), password.toStdString(), avatar_path.toStdString()};
        EventBus::getInstance().publish("/network/send_to_user_server",UserMsgType::REGISTER, std::move(args));
    }
    else
    {
        BubbleMessage::getInstance().error("Failed to connect User Server");
    }
}

void MainWidget::onLoginResult(bool status)
{
    QMetaObject::invokeMethod(this, [=]() {
        emit LoginResult(status);
        if(status)
        {
            updateUserNameBtn();
            BubbleMessage::getInstance().show("Success");
        }
    }, Qt::QueuedConnection);

}

void MainWidget::onRegisterResult(bool status)
{
    emit RegisterResult(status);
}

void MainWidget::onUserAvatarUpdated()
{
    QString user_name_qstring = QString::fromStdString(UserInfoManager::getInstance().getUserName());
    QPixmap avatar(QString("User/Avatar/") + user_name_qstring);
    QPixmap circular = createCircularPixmap(avatar, ui->label_avatar->width());
    ui->label_avatar->setPixmap(circular);
}

void MainWidget::onConnectFromDevice(QString code)
{
    dynamic_cast<ConnectWidget*>(WidgetManager::getInstance().getWidget(WidgetManager::WidgetType::ConnectWidget))->doConnect(code);
    ui->btn_connection->setChecked(true);
    on_btn_connection_clicked(true);
}

void MainWidget::onUploadUserAvatarResult(bool status)
{
    QMetaObject::invokeMethod(this, [=]() {
        std::string user_name = UserInfoManager::getInstance().getUserName();
        if(status)
        {
            loadUserInfo(user_name);
            BubbleMessage::getInstance().show("Upload avatar success!");
        }
        else
        {
            std::string avatar_path("User/Avatar/" + user_name);
            std::string tmp_path("User/tmp/"+ user_name);

            QPixmap avatar(QString::fromStdString(tmp_path));
            QPixmap circular = createCircularPixmap(avatar, ui->label_avatar->width());
            ui->label_avatar->setPixmap(circular);

            EventBus::getInstance().publish("/config/copy_file", tmp_path, avatar_path, std::function<void()>());
            BubbleMessage::getInstance().error("Failed to upload avatar");
        }
    }, Qt::QueuedConnection);
}

void MainWidget::onUserNameUpdateResult(bool status)
{
    QMetaObject::invokeMethod(this, [=]() {
        if(status)
        {
            std::string avatar_dir("User/Avatar/" + UserInfoManager::getInstance().getUserName());
            std::string new_avatar_dir("User/Avatar/" + UserInfoManager::getInstance().getChangingUserName());

            EventBus::getInstance().publish("/config/rename_file",avatar_dir, new_avatar_dir,std::function<void()>([this](){
                UserInfoManager::getInstance().setUserName(UserInfoManager::getInstance().getChangingUserName());
                UserInfoManager::getInstance().setChangingUserName("");
                EventBus::getInstance().publish("/config/update_module_config",std::string("User"),std::string("user_name"),UserInfoManager::getInstance().getUserName(), true);
                QMetaObject::invokeMethod(this, [=]() {
                    loadUserInfo(UserInfoManager::getInstance().getUserName());
                }, Qt::QueuedConnection);
            }));
            BubbleMessage::getInstance().show("Update user name success!");
        }
        else
        {
            BubbleMessage::getInstance().error("Failed to update user name");
        }
    }, Qt::QueuedConnection);
}