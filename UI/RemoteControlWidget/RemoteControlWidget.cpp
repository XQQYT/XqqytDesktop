#include "RemoteControlWidget.h"
#include "ui_RemoteControlWidget.h"

RemoteControlWidget::RemoteControlWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RemoteControlWidget)
{
    ui->setupUi(this);
    auto i = new OpenGLWidget(this);
    auto layout = this->layout();
    layout->addWidget(i);
}

void RemoteControlWidget::initRemoteControlWidget()
{
    if (!opengl_widget)
    {
        opengl_widget = new QOpenGLWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->addWidget(opengl_widget);
        setLayout(layout);
    }
}
RemoteControlWidget::~RemoteControlWidget()
{
    delete ui;
}

