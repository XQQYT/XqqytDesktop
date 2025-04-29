#include "SettingsWidget.h"
#include "ui_SettingsWidget.h"
#include <QDebug>

SettingsWidget::SettingsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);

    EventBus::getInstance().subscribe("/config/all_config_result",std::bind(
        &SettingsWidget::onAllConfigResult,
        this,
        std::placeholders::_1
    ));
    EventBus::getInstance().publish("/config/get_all_config");
    general_widget = new GeneralWidget(this);
    display_widget = new DisplayWidget(this);
    network_widget = new NetworkWidget(this);
    about_widget = new AboutWidget(this);

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
    std::cout<<"recv all config"<<all_config.size()<<std::endl;
    for (const auto& [outer_key, inner_map] : all_config) {
        std::cout << "Outer key: " << outer_key << std::endl;
        for (const auto& [inner_key, value] : inner_map) {
            std::cout << "  " << inner_key << ": " << value << std::endl;
        }
    }
}