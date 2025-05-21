/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class RegisterDialog; }
QT_END_NAMESPACE

class RegisterDialog : public QDialog
{
    Q_OBJECT

public:
    RegisterDialog(QWidget *parent = nullptr);
    ~RegisterDialog();
signals:
    void EnterDone(QString username, QString password , QString avatar_path);
    void RegisterDialogClosed();
public slots:
    void onRegisterResult(bool status);
private slots:
    void on_btn_login_clicked();
    void on_btn_register_clicked();
    void on_btn_select_avatar_clicked();
protected:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;
private:
    Ui::RegisterDialog *ui;
    QString selected_avatar_path;
};
#endif // REGISTERDIALOG_H
