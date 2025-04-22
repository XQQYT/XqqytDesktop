#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    setCurrentWidget(WidgetManager::WidgetType::Connect_Widget);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::setCurrentWidget(const WidgetManager::WidgetType type)
{
    QWidget* new_widget = WidgetManager::getInstance().getWidget(WidgetManager::WidgetType::Connect_Widget);
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
}