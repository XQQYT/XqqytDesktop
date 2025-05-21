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

    loading_dialog = new LoadingDialog(this);
    timeout_timer = new QTimer(this);

    connect(timeout_timer,&QTimer::timeout,this,[=](){
        loading_dialog->close();
        ui->label_hint->setText("Request timeout");
    });

    connect(&register_dialog,&RegisterDialog::RegisterDialogClosed,this,[=](){
        this->show();
        DialogOperator::centerDialog(*this);
    });
    connect(&register_dialog,&RegisterDialog::EnterDone,this,[=](QString username, QString password, QString avatar_path){
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
    DialogOperator::centerDialog(*loading_dialog);
    UserInfoManager::getInstance().setUserName(username.toStdString());
    timeout_timer->start(10000);
    loading_dialog->exec();
}

void LoginDialog::on_btn_register_clicked()
{
    this->hide();
    register_dialog.open();
    DialogOperator::centerDialog(register_dialog);
}

void LoginDialog::onLoginResult(bool status)
{
    loading_dialog->close();
    if(status)
    {
        ui->label_hint->clear();
        ui->lineEdit_username->clear();
        close();
    }
    else
    {
        UserInfoManager::getInstance().setUserName("null");
        ui->label_hint->setText("Authentication failed. Please check if the username and password are correct.");
    }
    ui->lineEdit_password->clear();
}
