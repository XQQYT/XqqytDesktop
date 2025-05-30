/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "WidgetManager.h"
#include "LoginDialog.h"
#include "BubbleMessage.h"
#include "UserProfileWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void setCurrentWidget(const WidgetManager::WidgetType type);
public slots:
    void onConnectFromDevice(QString code);
private slots:
    void on_btn_device_clicked(bool checked);
    void on_btn_connection_clicked(bool checked);
    void on_btn_settings_clicked(bool checked);
    void on_btn_username_clicked();
    void onEnterLoginDone(QString username, QString password);
    void onEnterRegisterDone(QString username, QString password, QString avatar_path);
signals:
    void LoginResult(bool status);
    void RegisterResult(bool status);
private:
    void initSubscribe();
    void onSettingChanged(std::string module, std::string key, std::string value);
    void switchLanguage(const std::string language);
    void loadUserInfo(std::string user_name);
    void updateUserNameBtn();
    void onLoginResult(bool status);
    void onRegisterResult(bool status);
    void onUserAvatarUpdated();
    void onUploadUserAvatarResult(bool status);
    void onUserNameUpdateResult(bool status);
private:
    Ui::MainWidget *ui;
    WidgetManager::WidgetType current_widget;
    QPushButton* current_btn;
    QTranslator *translator;
    LoginDialog* login_dialog;
};
#endif // MAINWIDGET_H
