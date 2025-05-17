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

QT_BEGIN_NAMESPACE
namespace Ui { class LoginDialog; }
QT_END_NAMESPACE

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();
signals:
    void EnterDone(QString username, QString password);
    void RegisterEnterDone(QString username, QString password, QString avatar_path);
private slots:
    void on_btn_login_clicked();
    void on_btn_register_clicked();
private:
    Ui::LoginDialog *ui;
    QWidget* parent;
    RegisterDialog register_dialog;
};
#endif // LOGIN_H
