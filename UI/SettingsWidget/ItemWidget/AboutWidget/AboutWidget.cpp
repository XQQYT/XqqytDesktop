#include "AboutWidget.h"
#include "ui_AboutWidget.h"

AboutWidget::AboutWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
}

AboutWidget::~AboutWidget()
{
    delete ui;
}

void AboutWidget::onAboutConfig(std::unordered_map<std::string,std::string> about_config)
{
    ui->label_version->setText(about_config["version"].data());
}