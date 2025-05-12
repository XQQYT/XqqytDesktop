#include "MainWidget.h"
#include "ui_MainWidget.h"
#include "RemoteControlWidget.h"
#include "SettingInfo.h"
#include "utils.h"
#include <QDebug>
#include <QTranslator>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    translator = nullptr;
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/MainWidget.qss")),this);
    current_widget = WidgetManager::WidgetType::UnDefined;
    current_btn = ui->btn_connect;
    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
        &MainWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    setCurrentWidget(WidgetManager::WidgetType::ConnectWidget);
    // 居中窗口
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = screenGeometry.x() + (screenGeometry.width() - this->width()) / 2;
    int y = screenGeometry.y() + (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);
}

MainWidget::~MainWidget()
{
    EventBus::getInstance().publish("/network/send_logout");
    WidgetManager::getInstance().closeAllWidget();
    delete ui;
}

void MainWidget::setCurrentWidget(const WidgetManager::WidgetType type)
{
    static bool is_first = true;
    if(current_widget == type)
        return;
    QWidget* new_widget = WidgetManager::getInstance().getWidget(type);
    if(!new_widget)
    {
        std::cout<<"New Widget is null"<<std::endl;
    }

    switchLanguage(SettingInfoManager::getInstance().getValue("General","language"));
    if(is_first)
    {
        EventBus::getInstance().publish("/config/update_module_config_done",std::string("General"),std::string("language"),SettingInfoManager::getInstance().getValue("General","language"));
        is_first = false;
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

void MainWidget::on_btn_settings_clicked(bool checked)
{
    if(current_btn == ui->btn_settings && !checked)
    {
        ui->btn_settings->setChecked(true);
        return;
    }
    current_btn->setChecked(false);
    setCurrentWidget(WidgetManager::WidgetType::SettingsWidget);
    current_btn = ui->btn_settings;
}

void MainWidget::switchLanguage(const std::string language)
{
    if (translator) {
        qApp->removeTranslator(translator);
        delete translator;
        translator = nullptr;
    }

    // 加载新的翻译器
    translator = new QTranslator(qApp);
    if (translator->load(QString("Translations/XqqytDesktop_%1").arg(QString::fromStdString(language)))) {
        qApp->installTranslator(translator);
    }
    ui->retranslateUi(this);
}

void MainWidget::onSettingChanged(std::string module, std::string key, std::string value)
{
    if(key == "theme")
    {
        QMetaObject::invokeMethod(this, [=]() {
            applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/MainWidget.qss")),this);
        }, Qt::QueuedConnection);
    }
    else if(key == "language")
    {
        QMetaObject::invokeMethod(this, [=]() {
            switchLanguage((value));
        }, Qt::QueuedConnection);
    }
}