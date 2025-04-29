#include "GeneralWidget.h"
#include "ui_GeneralWidget.h"
#include "utils.h"
#include <iostream>

static const std::string module_name = "General";

GeneralWidget::GeneralWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralWidget)
{
    ui->setupUi(this);
    applyStyleSheet("./Theme/Light/SettingsWidget/ItemWidget/GeneralWidget.qss",this);
    init_done = false;
}

GeneralWidget::~GeneralWidget()
{
    delete ui;
}

void GeneralWidget::onGeneralConfig(std::unordered_map<std::string,std::string> general_config)
{
    ui->checkbox_boot->setChecked(general_config["start_with_window"]=="true");
    ui->combobox_theme->setCurrentText(general_config["theme"].data());
    ui->combobox_language->setCurrentText(general_config["language"].data());
    init_done = true;
}

void GeneralWidget::on_checkbox_boot_stateChanged(int arg1)
{
    sendUpdataSignal("start_with_window",std::to_string((bool)arg1));
}

void GeneralWidget::on_combobox_theme_currentTextChanged(const QString &arg1)
{
    sendUpdataSignal("theme",arg1.toStdString());
}

void GeneralWidget::on_combobox_language_currentTextChanged(const QString &arg1)
{
    sendUpdataSignal("language",arg1.toStdString());
}

void GeneralWidget::sendUpdataSignal(std::string key,std::string value)
{
    if(init_done)
        emit updataGeneralConfig(module_name,key,value);
}
