#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    general_widget = new GeneralWidget(this);
    display_widget = new DisplayWidget(this);
    network_widget = new NetworkWidget(this);
    about_widget = new AboutWidget(this);

    qRegisterMetaType<std::unordered_map<std::string, std::string>>("std::unordered_map<std::string,std::string>");

    connect(this,&SettingsWidget::updataGeneral,general_widget,&GeneralWidget::onGeneralConfig);
    connect(this,&SettingsWidget::updataDisplay,display_widget,&DisplayWidget::onDisplayConfig);
    connect(this,&SettingsWidget::updataNetwork,network_widget,&NetworkWidget::onNetworkConfig);
    connect(this,&SettingsWidget::updataAbout,about_widget,&AboutWidget::onAboutConfig);

    EventBus::getInstance().subscribe("/config/all_config_result",std::bind(
        &SettingsWidget::onAllConfigResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().publish("/config/get_all_config");

    ui->stackedWidget->addWidget(general_widget);
    ui->stackedWidget->addWidget(display_widget);
    ui->stackedWidget->addWidget(network_widget);
    ui->stackedWidget->addWidget(about_widget);

    ui->stackedWidget->setCurrentWidget(general_widget);
    current_btn = ui->btn_general;
    ui->btn_general->setChecked(true);
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

void SettingsWidget::onAllConfigResult(std::unordered_map<std::string, std::unordered_map<std::string, std::string>> all_config)
{
    emit updataGeneral(all_config["General"]);
    emit updataDisplay(all_config["Display"]);
    emit updataNetwork(all_config["Network"]);
    emit updataAbout(all_config["Meta"]);
}