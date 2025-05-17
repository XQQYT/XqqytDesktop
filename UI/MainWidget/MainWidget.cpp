#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "RemoteControlWidget.h"
#include "SettingInfo.h"
#include "utils.h"
#include <QDebug>
#include <QTranslator>
#include <GlobalEnum.h>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    translator = nullptr;
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/MainWidget.qss")),this);
    current_widget = WidgetManager::WidgetType::UnDefined;
    current_btn = ui->btn_connection;
    this->setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
    
    connect(&login_dialog,&LoginDialog::EnterDone,this,&MainWidget::onEnterLoginDone);
    
    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
        &MainWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
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
}

void MainWidget::loadUserInfo(std::string user_name)
{
    QString user_name_qstring = QString::fromStdString(user_name);
    QLabel* label_avatar = ui->label_avatar;
    QPixmap avatar(QString("User/Avatar/") + user_name_qstring + ".png");
    QPixmap circular = createCircularPixmap(avatar, label_avatar->width());
    label_avatar->setPixmap(circular);

    UserInfoManager::getInstance().setUserName(std::move(user_name));
}

void MainWidget::on_btn_username_clicked()
{
    std::string current_user_name = UserInfoManager::getInstance().getUserName();
    if(current_user_name == "null")
    {
        centerDialog(this,login_dialog);
        login_dialog.exec();
    }
    else
    {
        std::cout<<"Personal center"<<std::endl;
    }
}

void MainWidget::onEnterLoginDone(QString username, QString password)
{
    std::vector<std::string> args = {username.toStdString(), password.toStdString()};
    EventBus::getInstance().publish("/network/send_to_user_server",UserMsgType::LOGIN, std::move(args));
    std::cout<<"enter login info done"<<std::endl;
}