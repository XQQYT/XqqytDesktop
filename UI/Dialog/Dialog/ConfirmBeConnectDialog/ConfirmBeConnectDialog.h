#ifndef CONFIRMBECONNECTDIALOG_H
#define CONFIRMBECONNECTDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class ConfirmBeConnectDialog; }
QT_END_NAMESPACE

class ConfirmBeConnectDialog : public QDialog
{
    Q_OBJECT

public:
    ConfirmBeConnectDialog(QWidget *parent = nullptr);
    ~ConfirmBeConnectDialog();
signals:
    void acceptConnection();
    void rejectConnection();
private slots:
    void on_btn_accept_clicked();
    void on_btn_reject_clicked();

private:
    Ui::ConfirmBeConnectDialog *ui;
};
#endif // CONFIRMBECONNECTDIALOG_H
