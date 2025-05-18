/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class LoadingDialog; }
QT_END_NAMESPACE

class LoadingDialog : public QDialog
{

    Q_OBJECT

public:
    LoadingDialog(QWidget *parent = nullptr);
    ~LoadingDialog();
signals:

private:
    Ui::LoadingDialog *ui;
    QMovie* movie;
};
#endif // LOADINGDIALOG_H
