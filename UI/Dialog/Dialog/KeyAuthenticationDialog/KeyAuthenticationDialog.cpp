/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "KeyAuthenticationDialog.h"
#include "ui_KeyAuthenticationDialog.h"
#include <iostream>

KeyAuthenticationDialog::KeyAuthenticationDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::KeyAuthenticationDialog)
{
    ui->setupUi(this);
}

KeyAuthenticationDialog::~KeyAuthenticationDialog()
{
    delete ui;
}

void KeyAuthenticationDialog::on_btn_connect_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        emit EnterDone(ui->lineEdit->text());
        this->close();
        ui->lineEdit->clear();
    }
}

void KeyAuthenticationDialog::on_btn_cancel_clicked()
{
    this->close();
}

void KeyAuthenticationDialog::show(std::string target_last_key)
{
    if(!target_last_key.empty())
        ui->lineEdit->setText(QString::fromStdString(target_last_key));
    static_cast<QWidget*>(this)->show();
}