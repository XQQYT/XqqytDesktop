/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "KeyAuthenticationDialog.h"
#include "ui_KeyAuthenticationDialog.h"
#include <iostream>
#include "utils.h"
#include "SettingInfo.h"

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

void KeyAuthenticationDialog::on_btn_enter_done_clicked()
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

void KeyAuthenticationDialog::showExec(std::string target_last_key)
{
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/Dialog/Dialog/KeyAuthenticationDialog.qss")),this);

    if(!target_last_key.empty())
        ui->lineEdit->setText(QString::fromStdString(target_last_key));
    dynamic_cast<QDialog*>(this)->exec();
}