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
#include "ConfirmBeConnectDialog.h"
#include "InfoDialog.h"
#include "UserInfo.h"
#include "KeyAuthenticationDialog.h"
#include "TransferHubWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ConnectWidget; }
QT_END_NAMESPACE

class ConnectWidget : public QWidget
{
    Q_OBJECT

public:
    ConnectWidget(QWidget *parent = nullptr);
    ~ConnectWidget();
    void doConnect(QString code);
private slots:
    void on_btn_connect_clicked();
    void on_btn_dynamic_key_value_clicked();
    void on_btn_share_clicked();
    void on_textChanged(const QString &text);
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
    void onConnectSignalServerResult(bool result);
    void onSignalRegistrationResult(bool result);
    void onConnectRequest(std::string target_id, std::string key);
    void onRecvConnectRequestResult(bool status);
    void onConnectionStatus(bool status);
    void onSettingChanged(std::string module, std::string key, std::string value);
    void onEnterKeyDone(QString key);
    void onTimeToUpdateKey();
    void onConnectUserServerResult(bool result);
    void onReceiveDeviceCode(std::string code);
private:
    Ui::ConnectWidget *ui;
    RemoteControlWidget* remote_widget;
    InfoDialog* info_dialog;
    KeyAuthenticationDialog* key_authenticate_dialog;
    bool remote_widget_alive;
    QTimer* update_dynamic_key_timer;
    TransferHubWidget* transferhub_widget;
};
#endif // WIDGET_H
