#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "RemoteControlWidget.h"
#include "websocket.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void on_pushButton_clicked();
private:
    Ui::MainWidget *ui;
    RemoteControlWidget* w;
    std::shared_ptr<WebSocket> ws_ptr;
};
#endif // WIDGET_H
