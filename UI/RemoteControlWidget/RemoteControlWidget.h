#ifndef REMOTECONTROLWIDGET_H
#define REMOTECONTROLWIDGET_H

#include <QWidget>
#include "Render.h" 

class OpenGLWidget;
QT_BEGIN_NAMESPACE
namespace Ui { class RemoteControlWidget; }
QT_END_NAMESPACE

class RemoteControlWidget : public QWidget, private RenderInterface
{
    Q_OBJECT

public:
    RemoteControlWidget(QWidget *parent = nullptr);
    ~RemoteControlWidget();
    void addRenderFrame(VideoFrame&& render_frame) override;
public slots:
    void handleFrameUpdated();
private:
    OpenGLWidget* opengl_widget;
    Ui::RemoteControlWidget *ui;
};
#endif // WIDGET_H
