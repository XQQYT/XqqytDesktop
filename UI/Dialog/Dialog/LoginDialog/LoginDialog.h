/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QPushButton>
#include <any>
#include <functional>
#include <QVector>

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
    // void EnterDone(QString password);
private slots:
    // void on_btn_connect_clicked();
    // void on_btn_cancel_clicked();
private:
    Ui::LoginDialog *ui;
};
#endif // LOGIN_H
