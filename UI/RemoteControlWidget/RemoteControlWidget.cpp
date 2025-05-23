/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "RemoteControlWidget.h"
#include "OpenGLWidget/OpenGLWidget.h"
#include "QImageWidget/QImageWidget.h"
#include "ui_RemoteControlWidget.h"
#include "EventBus.h"
#include "SettingInfo.h"
#include <iostream>

RemoteControlWidget::RemoteControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RemoteControlWidget)
{
    ui->setupUi(this);

    std::string use_gpu = SettingInfoManager::getInstance().getValue("Display","gpu_acceleration");
    if(use_gpu == "0")
    {
        render_widget = new QImageWidget(this);
    }
    else
    {
        render_widget = new OpenGLWidget(this);

        QSurfaceFormat format;
        format.setRenderableType(QSurfaceFormat::OpenGL);
        format.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
        format.setSwapInterval(1);
    
        QSurfaceFormat::setDefaultFormat(format);
    }

    auto layout = this->layout();
    layout->addWidget(render_widget);
    EventBus::getInstance().publish(EventBus::EventType::Render_SetRenderInstance,dynamic_cast<RenderInterface*>(this));
    EventBus::getInstance().subscribe(EventBus::EventType::Config_UpdateModuleConfigDone,std::bind(
        &RemoteControlWidget::onSettingChanged,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    elapsed_timer = new QElapsedTimer();
    elapsed_timer->start();
    last_render_time = 0;
    QString config_frame = QString::fromStdString(SettingInfoManager::getInstance().getValue("Display","render_rate"));
    setFPS(config_frame);
    render_count = 0;
    stats_start_time = 0;

    transferhub_widget = new TransferHubWidget(nullptr);
}

RemoteControlWidget::~RemoteControlWidget()
{
    delete elapsed_timer;
    delete transferhub_widget;
    delete ui;
}

void RemoteControlWidget::closeEvent(QCloseEvent *event)
{
    std::cout<<"publish close control"<<std::endl;
    EventBus::getInstance().publish(EventBus::EventType::Control_CloseControl);
    transferhub_widget->stop();
    emit remote_widget_closed();
}


void RemoteControlWidget::addRenderFrame(VideoFrame&& render_frame) {
    qint64 current_time = elapsed_timer->elapsed();
    if(frame_interval_ms == 0 || current_time - last_render_time >= frame_interval_ms)
    {
        RenderWidgetInterface* interface = dynamic_cast<RenderWidgetInterface*>(render_widget);
        QMetaObject::invokeMethod(render_widget, [f = std::move(render_frame), interface]() mutable {
            if(interface)
                interface->setCurrent(std::move(f));
        }, Qt::QueuedConnection);
        last_render_time = current_time;
        render_count++;
        if (stats_start_time == 0) {
            stats_start_time = current_time;
        }

        if (current_time - stats_start_time >= 1000) {
            std::cout << "Current Render Frame Rate: " << render_count << " FPS" << std::endl;
            render_count = 0;
            stats_start_time = current_time;
        }
    }
}

void RemoteControlWidget::setFPS(QString config_frame)
{
    bool to_int_ok = false;
    int render_rate = config_frame.remove("fps").toInt(&to_int_ok);
    if(to_int_ok)
        frame_interval_ms = 1000/render_rate;
    else
        frame_interval_ms = 0;
}

void RemoteControlWidget::onSettingChanged(std::string module, std::string key, std::string value)
{
    if(key == "render_rate")
    {
        QMetaObject::invokeMethod(this, [=]() {
            setFPS(QString::fromStdString(value));
        }, Qt::QueuedConnection);
    }
}

void RemoteControlWidget::showWithTransfer()
{
    EventBus::getInstance().publish(EventBus::EventType::Render_SetRenderInstance,dynamic_cast<RenderInterface*>(this));
    transferhub_widget->start();
    show();
}