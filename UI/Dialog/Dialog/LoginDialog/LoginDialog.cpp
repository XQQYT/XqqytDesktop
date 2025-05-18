/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include "utils.h"
#include <iostream>
#include "UserInfo.h"

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , parent(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    connect(&register_dialog,&RegisterDialog::RegisterDialogClosed,this,[=](){
        this->show();
        centerDialog(parent, *this);
    });
    connect(&register_dialog,&RegisterDialog::EnterDone,this,[=](QString username, QString password, QString avatar_path){
        std::cout<<"emit RegisterEnterDone(username, password, avatar_path);"<<std::endl;
        emit RegisterEnterDone(username, password, avatar_path);
    });
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
    centerDialog(this,loading_dialog);
    UserInfoManager::getInstance().setUserName(username.toStdString());
    loading_dialog.exec();
}

void LoginDialog::on_btn_register_clicked()
{
    this->hide();
    register_dialog.open();
    centerDialog(parent, register_dialog);
}

void LoginDialog::onLoginResult(bool status)
{
    if(status)
    {
        reject();
        ui->label_hint->clear();
    }
    else
    {
        UserInfoManager::getInstance().setUserName("null");
        ui->label_hint->setText("Authentication failed. Please check if the username and password are correct.");
        ui->lineEdit_password->clear();
    }
    loading_dialog.close();
}
