/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ConfirmDialog; }
QT_END_NAMESPACE

class ConfirmDialog : public QDialog
{
    Q_OBJECT

public:
    ConfirmDialog(QWidget *parent = nullptr);
    ~ConfirmDialog();
    void exec(QString text, QString title = "");
signals:
    void ChooseResult(bool result);
private slots:
    void on_btn_yes_clicked();
    void on_btn_no_clicked();

private:
    Ui::ConfirmDialog *ui;
};
#endif // CONFIRMDIALOG_H
