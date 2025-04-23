#ifndef REMOTECONTROLWIDGET_H
#define REMOTECONTROLWIDGET_H

#include <QWidget>
#include "OpenGLWidget/OpenGLWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class RemoteControlWidget; }
QT_END_NAMESPACE

class RemoteControlWidget : public QWidget
{
    Q_OBJECT

public:
    RemoteControlWidget(QWidget *parent = nullptr);
    ~RemoteControlWidget();

private:
    Ui::RemoteControlWidget *ui;
};
#endif // WIDGET_H
