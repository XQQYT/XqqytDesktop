/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include <iostream>
#include <QFileDialog>
#include <QFileInfo>
#include "BubbleMessage.h"
#include "SettingInfo.h"
#include "utils.h"

RegisterDialog::RegisterDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/Dialog/Dialog/RegisterDialog.qss")),this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::closeEvent(QCloseEvent *event)
{
    on_btn_login_clicked();
}

void RegisterDialog::on_btn_login_clicked()
{
    emit RegisterDialogClosed();
    this->close();
}

void RegisterDialog::on_btn_register_clicked()
{
    QString username = ui->lineedit_username->text();
    QString password = ui->lineedit_password->text();
    QString confirm_password = ui->lineedit_confirm_password->text();
    if(username.isEmpty() || password.isEmpty() || confirm_password.isEmpty() 
        || confirm_password.compare(password) || selected_avatar_path.isEmpty())
    {
        std::cout<<"user info has errors"<<username.isEmpty()<<password.isEmpty()<<confirm_password.isEmpty()<<std::endl;
        return;
    }
    emit EnterDone(username, password, selected_avatar_path);
}

void RegisterDialog::on_btn_select_avatar_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("Select Avatar"),
        "",
        tr("Image File (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (!filePath.isEmpty()) {
        selected_avatar_path = filePath;
    }
    ui->avatarPreview->setPixmap(QPixmap(selected_avatar_path).scaled(ui->avatarPreview->width(),ui->avatarPreview->height()));
}

void RegisterDialog::onRegisterResult(bool status)
{
    if(!status)
    {
        BubbleMessage::getInstance().error("Failed to register");
    }
    else
    {
        BubbleMessage::getInstance().show("Register successed");
        on_btn_login_clicked();
    }
}
