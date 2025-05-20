/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef EDITDEVICECOMMENTDIALOG_H
#define EDITDEVICECOMMENTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class EditDeviceCommentDialog; }
QT_END_NAMESPACE

class EditDeviceCommentDialog : public QDialog
{
    Q_OBJECT

public:
    EditDeviceCommentDialog(QString devicename, QWidget *parent = nullptr);
    ~EditDeviceCommentDialog();
signals:
    void editComment(QString new_comment);
private slots:
    void on_btn_done_clicked();
    void on_btn_cancel_clicked();
private:
    Ui::EditDeviceCommentDialog *ui;
    QString device_name;
};
#endif // EDITDEVICECOMMENTDIALOG_H
