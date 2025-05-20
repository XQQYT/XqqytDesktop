/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "MoreDialog.h"
#include "ui_MoreDialog.h"
#include "../EditDeviceCommentDialog/EditDeviceCommentDialog.h"
#include "ConfirmDialog.h"
#include "utils.h"
#include "UserInfo.h"
#include <iostream>

MoreDialog::MoreDialog(QString code,QString name, QWidget *parent)
    : QDialog(parent),
    device_name(name),
    device_code(code)
    , ui(new Ui::MoreDialog)
{
    ui->setupUi(this);
    if(UserInfoManager::getInstance().getCurrentUserId() == device_code.toStdString())
    {
        ui->btn_delete->hide();
    }
}

MoreDialog::~MoreDialog()
{
    delete ui;
}

void MoreDialog::on_btn_copy_info_clicked()
{
    emit copyDeviceInfo();
    reject();
}

void MoreDialog::on_btn_edit_comment_clicked()
{
    EditDeviceCommentDialog* edit_dailog = new EditDeviceCommentDialog(device_name);
    connect(edit_dailog,&EditDeviceCommentDialog::editComment,this,[this](QString new_comment){
        emit editComment(new_comment);
    });
    edit_dailog->exec();
    reject();
}

void MoreDialog::on_btn_delete_clicked()
{
    ConfirmDialog dialog;
    connect(&dialog,&ConfirmDialog::ChooseResult,this,[this](bool result){
        if(result)
        emit deleteDevice();
    });
    DialogOperator::centerDialog(dialog);
    dialog.exec("Are you sure to delete " + device_name);
    reject();
}