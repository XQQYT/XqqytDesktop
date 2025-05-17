/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <iostream>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btn_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();
    if(username.isEmpty() || password.isEmpty())
    {
        return;
    }
    emit EnterDone(username,password);
}

void onEnterLoginDone(QString username, QString password)
{
    
}