/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "ConfirmDialog.h"
#include "ui_ConfirmDialog.h"
#include "utils.h"
#include "SettingInfo.h"

ConfirmDialog::ConfirmDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfirmDialog)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/Dialog/Dialog/ConfirmDialog.qss")),this);
}

ConfirmDialog::~ConfirmDialog()
{
    delete ui;
}

void ConfirmDialog::on_btn_yes_clicked()
{
    emit ChooseResult(true);
    close();
}
void ConfirmDialog::on_btn_no_clicked()
{
    emit ChooseResult(false);
    close();
}

void ConfirmDialog::exec(QString text, QString title)
{
    if(!title.isEmpty())
        ui->label_title->setText(title);
    ui->label_content->setText(text);
    dynamic_cast<QDialog*>(this)->exec();
}