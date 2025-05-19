/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "MoreDialog.h"
#include "ui_MoreDialog.h"
#include <iostream>

MoreDialog::MoreDialog(QString code, QWidget *parent)
    : QDialog(parent),
    device_code(code)
    , ui(new Ui::MoreDialog)
{
    ui->setupUi(this);
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
    emit editComment("qyt");
    reject();
}

void MoreDialog::on_btn_delete_clicked()
{
    emit deleteDevice();
    reject();
}