/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "SecurityWidget.h"
#include "ui_SecurityWidget.h"
#include "utils.h"
#include "SettingInfo.h"

static const std::string module_name = "Security";

SecurityWidget::SecurityWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SecurityWidget)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/SecurityWidget.qss")),this);
    init_done = false;
}

SecurityWidget::~SecurityWidget()
{
    delete ui;
}

void SecurityWidget::onSecurityConfig(std::unordered_map<std::string,std::string> security_config)
{
    ui->combobox_update_frequency->setCurrentText(security_config["key_update_frequency"].data());
    init_done = true;
}


void SecurityWidget::on_combobox_update_frequency_currentTextChanged(const QString &arg1)
{
    sendUpdataSignal("key_update_frequency",arg1.toStdString());
}

void SecurityWidget::sendUpdataSignal(std::string key,std::string value)
{
    if(init_done)
        emit updateSecurityConfig(module_name,key,value);
}

void SecurityWidget::retranslateUi()
{
    ui->retranslateUi(this);
}