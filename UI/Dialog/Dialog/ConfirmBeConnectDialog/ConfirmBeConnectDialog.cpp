/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "ConfirmBeConnectDialog.h"
#include "ui_ConfirmBeConnectDialog.h"

ConfirmBeConnectDialog::ConfirmBeConnectDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmBeConnectDialog)
{
    ui->setupUi(this);
}

ConfirmBeConnectDialog::~ConfirmBeConnectDialog()
{
    delete ui;
}

void ConfirmBeConnectDialog::on_btn_accept_clicked()
{
    emit acceptConnection();
    close();
}
void ConfirmBeConnectDialog::on_btn_reject_clicked()
{
    emit rejectConnection();
    close();
}
