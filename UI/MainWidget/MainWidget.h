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
#include "InfoDialog.h"

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
    template <typename Sender, typename Signal, typename Receiver, typename Slot>
    void reconnect(Sender* sender, Signal signal, Receiver* receiver, Slot slot)
    {
        QObject::disconnect(sender, nullptr, nullptr, nullptr);
        QObject::connect(sender, signal, receiver, slot);
    }

private:
    void onTargetOffline();
    void onConnectServerFailed();
    void onRegistrationRejected();
    void onConnectRequest(std::string target_id);
    void onRecvConnectRequestResult(bool status);
private:
    Ui::MainWidget *ui;
    RemoteControlWidget* w;
    BubbleMessage bubble_message;
    InfoDialog info_dialog;
};
#endif // WIDGET_H
