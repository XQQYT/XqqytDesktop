/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef KEYAUTHENTICATIONDIALOG_H
#define KEYAUTHENTICATIONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <any>
#include <functional>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class KeyAuthenticationDialog; }
QT_END_NAMESPACE

class KeyAuthenticationDialog : public QDialog
{
    Q_OBJECT

public:
    KeyAuthenticationDialog(QWidget *parent = nullptr);
    ~KeyAuthenticationDialog();
    void showExec(std::string target_last_key);
signals:
    void EnterDone(QString password);
private slots:
    void on_btn_enter_done_clicked();
    void on_btn_cancel_clicked();
private:
    Ui::KeyAuthenticationDialog *ui;
};
#endif // KEYAUTHENTICATIONDIALOG_H
