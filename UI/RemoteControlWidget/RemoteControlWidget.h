/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef REMOTECONTROLWIDGET_H
#define REMOTECONTROLWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QElapsedTimer>
#include "RenderWidgetInterface/RenderWidgetInterface.h"

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

protected:
    void closeEvent(QCloseEvent *event) override;

signals:
    void remote_widget_closed();

private:
    void onSettingChanged(std::string module, std::string key, std::string value);
    void setFPS(QString config_frame);
private:
    QWidget *render_widget;
    RenderWidgetInterface* render_widget_interface;
    Ui::RemoteControlWidget *ui;
    QElapsedTimer* elapsed_timer;
    qint64 frame_interval_ms;
    qint64 last_render_time;
    int render_count;
    int stats_start_time;
};
#endif // WIDGET_H
