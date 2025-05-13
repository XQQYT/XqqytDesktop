/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef CONNECTWIDGET_H
#define CONNECTWIDGET_H

#include <QWidget>
#include <QStyle>
#include <QScreen>
#include <QGuiApplication>
#include <QTimer>
#include "RemoteControlWidget.h"
#include "EventBus.h"
#include "BubbleMessage.h"
#include "ConfirmBeConnectDialog.h"
#include "InfoDialog.h"
#include "UserInfo.h"
#include "KeyAuthenticationDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ConnectWidget; }
QT_END_NAMESPACE

class ConnectWidget : public QWidget
{
    Q_OBJECT

public:
    ConnectWidget(QWidget *parent = nullptr);
    ~ConnectWidget();
private slots:
    void on_btn_connect_clicked();
    void on_btn_dynamic_key_value_clicked();
    void on_btn_share_clicked();
private:
    void initSubscribe();
    template <typename Sender, typename Signal, typename Receiver, typename Slot>
    void reconnect(Sender* sender, Signal signal, Receiver* receiver, Slot slot)
    {
        QObject::disconnect(sender, nullptr, nullptr, nullptr);
        QObject::connect(sender, signal, receiver, slot);
    }

    void setUpdateKeyTimer();
    void resetUpdateKeyTimer(int64_t last_update_timestamp);

private:
    void onTargetStatus(bool target_status);
    void onConnectServerFailed();
    void onRegistrationRejected();
    void onConnectRequest(std::string target_id, std::string key);
    void onRecvConnectRequestResult(bool status);
    void onConnectionStatus(bool status);
    void onSettingChanged(std::string module, std::string key, std::string value);
    void onEnterKeyDone(QString key);
    void onTimeToUpdateKey();
private:
    Ui::ConnectWidget *ui;
    RemoteControlWidget* remote_widget;
    BubbleMessage bubble_message;
    InfoDialog info_dialog;
    KeyAuthenticationDialog key_authenticate_dialog;
    bool remote_widget_alive;
    QTimer* update_dynamic_key_timer;
};
#endif // WIDGET_H
