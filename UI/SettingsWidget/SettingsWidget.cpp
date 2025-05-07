#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"
#include "SettingInfo.h"
#include "utils.h"
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/SettingsWidget.qss")),this);
    write_timer = new QTimer(this);
    connect(write_timer,&QTimer::timeout,this,&SettingsWidget::publishWrite);

    general_widget = new GeneralWidget(this);
    display_widget = new DisplayWidget(this);
    network_widget = new NetworkWidget(this);
    about_widget = new AboutWidget(this);

    qRegisterMetaType<std::unordered_map<std::string, std::string>>("std::unordered_map<std::string,std::string>");

    connect(this,&SettingsWidget::updataGeneral,general_widget,&GeneralWidget::onGeneralConfig);
    connect(this,&SettingsWidget::updataDisplay,display_widget,&DisplayWidget::onDisplayConfig);
    connect(this,&SettingsWidget::updataNetwork,network_widget,&NetworkWidget::onNetworkConfig);
    connect(this,&SettingsWidget::updataAbout,about_widget,&AboutWidget::onAboutConfig);

    connect(general_widget,&GeneralWidget::updataGeneralConfig,this,&SettingsWidget::updataModuleConfig);
    connect(display_widget,&DisplayWidget::updataDisplayConfig,this,&SettingsWidget::updataModuleConfig);
    connect(network_widget,&NetworkWidget::updataNetworkConfig,this,&SettingsWidget::updataModuleConfig);

    initConfig();

    ui->stackedWidget->addWidget(general_widget);
    ui->stackedWidget->addWidget(display_widget);
    ui->stackedWidget->addWidget(network_widget);
    ui->stackedWidget->addWidget(about_widget);

    ui->stackedWidget->setCurrentWidget(general_widget);
    current_btn = ui->btn_general;
    ui->btn_general->setChecked(true);

    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
        &SettingsWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::on_btn_general_clicked(bool checked)
{
    if(current_btn == ui->btn_general && !checked)
    {
        ui->btn_general->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    ui->stackedWidget->setCurrentWidget(general_widget);
    current_btn = ui->btn_general;
}

void SettingsWidget::on_btn_display_clicked(bool checked)
{
    if(current_btn == ui->btn_display && !checked)
    {
        ui->btn_display->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    ui->stackedWidget->setCurrentWidget(display_widget);
    current_btn = ui->btn_display;
}

void SettingsWidget::on_btn_network_clicked(bool checked)
{
    if(current_btn == ui->btn_network && !checked)
    {
        ui->btn_network->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    ui->stackedWidget->setCurrentWidget(network_widget);
    current_btn = ui->btn_network;
}

void SettingsWidget::on_btn_about_clicked(bool checked)
{
    if(current_btn == ui->btn_about && !checked)
    {
        ui->btn_about->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    ui->stackedWidget->setCurrentWidget(about_widget);
    current_btn = ui->btn_about;
}

void SettingsWidget::initConfig()
{
    auto all_config = SettingInfoManager::getInstance().getAllConfig();
    emit updataGeneral((*all_config)["General"]);
    emit updataDisplay((*all_config)["Display"]);
    emit updataNetwork((*all_config)["Network"]);
    emit updataAbout((*all_config)["Meta"]);
}

void SettingsWidget::updataModuleConfig(std::string module, std::string key, std::string value)
{
    if((write_timer->isActive()))
    {
        write_timer->stop();
    }
    write_timer->start(2000);
    EventBus::getInstance().publish("/config/update_module_config",std::move(module),std::move(key),std::move(value));
}

void SettingsWidget::publishWrite()
{
    EventBus::getInstance().publish("/config/write_into_file");
    write_timer->stop();
}

void SettingsWidget::onSettingChanged(std::string module, std::string key, std::string value)
{
    if(key == "theme")
    {
        QMetaObject::invokeMethod(this, [=]() {
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/SettingsWidget.qss")),this);
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/GeneralWidget.qss")),general_widget);
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/DisplayWidget.qss")),display_widget);
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/NetworkWidget.qss")),network_widget);
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/AboutWidget.qss")),about_widget);
        }, Qt::QueuedConnection);
    }
    else if(key == "language")
    {
        QMetaObject::invokeMethod(this, [=]() {
            ui->retranslateUi(this);
            general_widget->retranslateUi();
            display_widget->retranslateUi();
            network_widget->retranslateUi();
            about_widget->retranslateUi();
        }, Qt::QueuedConnection);
    }
}