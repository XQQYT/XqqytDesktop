/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "DisplayWidget.h"
#include "ui_DisplayWidget.h"
#include "utils.h"
#include "SettingInfo.h"

static const std::string module_name = "Display";

DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/DisplayWidget.qss")),this);
    init_done = false;
}

DisplayWidget::~DisplayWidget()
{
    delete ui;
}

void DisplayWidget::onDisplayConfig(std::unordered_map<std::string,std::string> display_config)
{
    ui->checkbox_render->setChecked(display_config["gpu_acceleration"]=="true");
    ui->combobox_render_rate->setCurrentText(display_config["render_rate"].data());
    ui->combobox_capture_rate->setCurrentText(display_config["capture_rate"].data());
    init_done = true;
}

void DisplayWidget::on_checkbox_render_stateChanged(int arg1)
{
    sendUpdataSignal("gpu_acceleration",std::to_string((bool)arg1));
}

void DisplayWidget::on_combobox_render_rate_currentTextChanged(const QString &arg1)
{
    sendUpdataSignal("render_rate",arg1.toStdString());
}

void DisplayWidget::on_combobox_capture_rate_currentTextChanged(const QString &arg1)
{
    sendUpdataSignal("capture_rate",arg1.toStdString());
}

void DisplayWidget::sendUpdataSignal(std::string key,std::string value)
{
    if(init_done)
        emit updateDisplayConfig(module_name,key,value);
}

void DisplayWidget::retranslateUi()
{
    ui->retranslateUi(this);
}