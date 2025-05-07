#include "AboutWidget.h"
#include "utils.h"
#include "SettingInfo.h"
#include "ui_AboutWidget.h"
#include <iostream>

AboutWidget::AboutWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/AboutWidget.qss")),this);
}

AboutWidget::~AboutWidget()
{
    delete ui;
}

void AboutWidget::onAboutConfig(std::unordered_map<std::string,std::string> about_config)
{
    ui->label_version->setText(ui->label_version->text() + QString::fromStdString(about_config["version"]));
    version = QString::fromStdString(about_config["version"]);
    std::cout<<"version -> "<<about_config["version"]<<std::endl;
}

void AboutWidget::retranslateUi()
{
    ui->retranslateUi(this);
    ui->label_version->setText(ui->label_version->text() + version);
}