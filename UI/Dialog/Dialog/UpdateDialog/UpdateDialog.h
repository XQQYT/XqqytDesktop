/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef UPDATEDIALOG_H
#define UPDATEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class UpdateDialog; }
QT_END_NAMESPACE

class UpdateDialog : public QDialog
{
    Q_OBJECT

public:
    UpdateDialog(QWidget *parent = nullptr);
    ~UpdateDialog();
    void setVersionText(std::string version, std::string description, std::string date);
signals:
    void update();
private slots:
    void on_btn_update_clicked();
private:
    Ui::UpdateDialog *ui;
};
#endif // UPDATEDIALOG_H
