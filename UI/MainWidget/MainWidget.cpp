#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "RemoteControlWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    current_widget = WidgetManager::WidgetType::UnDefined;
    current_btn = ui->btn_connect;
    setCurrentWidget(WidgetManager::WidgetType::ConnectWidget);
    auto i = new RemoteControlWidget();
    i->show();
}

MainWidget::~MainWidget()
{
    WidgetManager::getInstance().closeAllWidget();
    delete ui;
}

void MainWidget::setCurrentWidget(const WidgetManager::WidgetType type)
{
    if(current_widget == type)
        return;
    QWidget* new_widget = WidgetManager::getInstance().getWidget(type);
    if(!new_widget)
    {
        std::cout<<"New Widget is null"<<std::endl;
    }

    QLayout* layout = ui->right_content_widget->layout();

    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* old_widget = item->widget()) {
            old_widget->hide();
            old_widget->setParent(nullptr);
        }
        delete item;
    }

    layout->addWidget(new_widget);
    new_widget->show();
    current_widget = type;
}

void MainWidget::on_btn_device_clicked(bool checked)
{
    if(current_btn == ui->btn_device && !checked)
    {
        ui->btn_device->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    current_btn = ui->btn_device;
    setCurrentWidget(WidgetManager::WidgetType::DeviceWidget);
    current_btn = ui->btn_device;
}

void MainWidget::on_btn_connect_clicked(bool checked)
{
    if(current_btn == ui->btn_connect && !checked)
    {
        ui->btn_connect->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    setCurrentWidget(WidgetManager::WidgetType::ConnectWidget);
    current_btn = ui->btn_connect;

}
