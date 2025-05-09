/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "RemoteControlWidget.h"
#include "OpenGLWidget/OpenGLWidget.h"
#include "ui_RemoteControlWidget.h"
#include "EventBus.h"
#include "SettingInfo.h"
#include <iostream>

RemoteControlWidget::RemoteControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RemoteControlWidget)
{
    ui->setupUi(this);
    opengl_widget = new OpenGLWidget();
    opengl_widget->setMouseTracking(true);
    opengl_widget->setFocusPolicy(Qt::StrongFocus);
    auto layout = this->layout();
    layout->addWidget(opengl_widget);
    EventBus::getInstance().publish("/render/set_render_instance",dynamic_cast<RenderInterface*>(this));
    EventBus::getInstance().subscribe("/config/update_module_config_done",std::bind(
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
}

RemoteControlWidget::~RemoteControlWidget()
{
    delete elapsed_timer;
    delete opengl_widget;
    delete ui;
}

void RemoteControlWidget::closeEvent(QCloseEvent *event)
{
    EventBus::getInstance().publish("/control/close_control");
    emit remote_widget_closed();
}


void RemoteControlWidget::addRenderFrame(VideoFrame&& render_frame) {
    qint64 current_time = elapsed_timer->elapsed();
    if(frame_interval_ms == 0 || current_time - last_render_time >= frame_interval_ms)
    {
        QMetaObject::invokeMethod(opengl_widget, [this,&render_frame]() {
            opengl_widget->setCurrent(std::move(render_frame));
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

void RemoteControlWidget::handleFrameUpdated()
{
    opengl_widget->update();
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