/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef MOREDIALOG_H
#define MOREDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MoreDialog; }
QT_END_NAMESPACE

class MoreDialog : public QDialog
{
    Q_OBJECT

public:
    MoreDialog(QString code,QString name, QWidget *parent = nullptr);
    ~MoreDialog();
signals:
    void copyDeviceInfo();
    void editComment(QString new_comment);
    void deleteDevice();
private slots:
    void on_btn_copy_info_clicked();
    void on_btn_edit_comment_clicked();
    void on_btn_delete_clicked();
private:
    Ui::MoreDialog *ui;
    QString device_code;
    QString device_name;
};
#endif // MOREDIALOG_H
