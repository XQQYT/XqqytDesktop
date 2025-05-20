/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "EditDeviceCommentDialog.h"
#include "ui_EditDeviceCommentDialog.h"
#include "utils.h"
#include <iostream>

EditDeviceCommentDialog::EditDeviceCommentDialog(QString devicename, QWidget *parent)
    : QDialog(parent),
    device_name(devicename)
    , ui(new Ui::EditDeviceCommentDialog)
{
    ui->setupUi(this);
    DialogOperator::centerDialog(*this);
    ui->label_device->setText("Editing comment for: " + devicename);
}

EditDeviceCommentDialog::~EditDeviceCommentDialog()
{
    delete ui;
}

void EditDeviceCommentDialog::on_btn_done_clicked()
{
    emit editComment(ui->lineEdit->text());
    reject();
}

void EditDeviceCommentDialog::on_btn_cancel_clicked()
{

}