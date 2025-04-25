#include "RemoteControlWidget.h"
#include "OpenGLWidget/OpenGLWidget.h"
#include "ui_RemoteControlWidget.h"
#include "EventBus.h"
#include <iostream>

RemoteControlWidget::RemoteControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RemoteControlWidget)
{
    ui->setupUi(this);
    opengl_widget = new OpenGLWidget();
    auto layout = this->layout();
    layout->addWidget(opengl_widget);
    EventBus::getInstance().publish("/render/set_render_instance",dynamic_cast<RenderInterface*>(this));
}

RemoteControlWidget::~RemoteControlWidget()
{
    delete opengl_widget;
    delete ui;
}


void RemoteControlWidget::addRenderFrame(VideoFrame&& render_frame) {
    std::cout << "Width: " << render_frame.width << std::endl;
    std::cout << "Height: " << render_frame.height << std::endl;
    std::cout << "Stride (Y): " << render_frame.stride_y << std::endl;
    std::cout << "Stride (U): " << render_frame.stride_u << std::endl;
    std::cout << "Stride (V): " << render_frame.stride_v << std::endl;
    QMetaObject::invokeMethod(opengl_widget, [this,&render_frame]() {
        opengl_widget->setCurrent(std::move(render_frame));
    }, Qt::QueuedConnection);
}

void RemoteControlWidget::handleFrameUpdated()
{
    opengl_widget->update();
}