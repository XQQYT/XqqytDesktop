/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "RegisterDialog.h"
#include "LoadingDialog.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
    RegisterDialog register_dialog;
signals:
    void EnterDone(QString username, QString password);
    void RegisterEnterDone(QString username, QString password, QString avatar_path);
public slots:
    void onLoginResult(bool status);
protected:
    void showEvent(QShowEvent* event);
private slots:
    void on_btn_login_clicked();
    void on_btn_register_clicked();
private:
    Ui::LoginDialog *ui;
    QWidget* parent;
    LoadingDialog* loading_dialog;
    QTimer* timeout_timer;
};
#endif // LOGIN_H
