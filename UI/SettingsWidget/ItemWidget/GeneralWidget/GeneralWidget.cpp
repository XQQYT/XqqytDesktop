#include "GeneralWidget.h"
#include "ui_GeneralWidget.h"
#include <iostream>

GeneralWidget::GeneralWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GeneralWidget)
{
    ui->setupUi(this);
}

GeneralWidget::~GeneralWidget()
{
    delete ui;
}

void GeneralWidget::onGeneralConfig(std::unordered_map<std::string,std::string> general_config)
{
    std::cout<<"recv general config"<<std::endl;
    ui->checkbox_boot->setChecked(general_config["start_with_window"]=="true");
    ui->combobox_theme->setCurrentText(general_config["theme"].data());
    ui->combobox_language->setCurrentText(general_config["language"].data());
}