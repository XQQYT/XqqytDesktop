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
private slots:
    void on_btn_device_clicked(bool checked);
    void on_btn_connection_clicked(bool checked);
    void on_btn_settings_clicked(bool checked);
    void on_btn_username_clicked();
    void onEnterLoginDone(QString username, QString password);

private:
    void onSettingChanged(std::string module, std::string key, std::string value);
    void switchLanguage(const std::string language);
    void loadUserInfo(std::string user_name);
    void updateUserNameBtn();
private:
    Ui::MainWidget *ui;
    WidgetManager::WidgetType current_widget;
    QPushButton* current_btn;
    QTranslator *translator;
    LoginDialog login_dialog;
};
#endif // MAINWIDGET_H
