#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QStyle>
#include <QScreen>
#include <QGuiApplication>
#include "RemoteControlWidget.h"
#include "EventBus.h"
#include "BubbleMessage.h"
#include "ConfirmBeConnectDialog.h"

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
    void on_btn_connect_clicked();
private:
    void initSubscribe();
private:
    void onTargetOffline();
    void onConnectServerFailed();
    void onRegistrationRejected();
    void onConnectRequest(std::string target_id);
private:
    Ui::MainWidget *ui;
    RemoteControlWidget* w;
    BubbleMessage bubble_message;
};
#endif // WIDGET_H
