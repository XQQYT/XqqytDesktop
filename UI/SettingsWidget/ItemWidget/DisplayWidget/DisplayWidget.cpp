#include "DisplayWidget.h"
#include "ui_DisplayWidget.h"

DisplayWidget::DisplayWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DisplayWidget)
{
    ui->setupUi(this);
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
}