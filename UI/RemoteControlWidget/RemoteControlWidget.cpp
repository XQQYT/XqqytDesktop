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
    opengl_widget = new OpenGLWidget(this);
    auto layout = this->layout();
    layout->addWidget(opengl_widget);
    opengl_widget->show();
    EventBus::getInstance().publish("/render/set_render_instance",dynamic_cast<RenderInterface*>(this));
}

RemoteControlWidget::~RemoteControlWidget()
{
    delete opengl_widget;
    delete ui;
}

void RemoteControlWidget::addRenderFrame(VideoFrame&& render_frame)
{
    std::cout<<" RemoteControlWidget  addRenderFrame"<<std::endl;
    opengl_widget->addRenderFrame(std::move(render_frame));
    opengl_widget->update();
}