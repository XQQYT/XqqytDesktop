/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "UpdateDialog.h"
#include "ui_UpdateDialog.h"
#include "utils.h"
#include "SettingInfo.h"

UpdateDialog::UpdateDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UpdateDialog)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/Dialog/Dialog/ConfirmDialog.qss")),this);
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::setVersionText(std::string version, std::string description, std::string date)
{
    QString version_content = QString("Version %0 - Released on %1").arg(QString::fromStdString(version), QString::fromStdString(date));
    ui->label_version->setText(version_content);
    ui->textedit_change->setText(QString::fromStdString(description));
}

void UpdateDialog::on_btn_update_clicked()
{
    emit update();
    close();
}