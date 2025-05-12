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
    }
}

