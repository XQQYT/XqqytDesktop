/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "UserProfileWidget.h"
#include "ui_UserProfileWidget.h"
#include "utils.h"
#include "UserInfo.h"
#include <QLabel>
#include <iostream>

UserProfileWidget::UserProfileWidget(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserProfileWidget)
{
    ui->setupUi(this);
    loadUserInfo();
}

UserProfileWidget::~UserProfileWidget()
{
    delete ui;
}

void UserProfileWidget::loadUserInfo()
{
    QString user_name_qstring = QString::fromStdString(UserInfoManager::getInstance().getUserName());
    QLabel* label_avatar = ui->label_avatar;
    QPixmap avatar(QString("User/Avatar/") + user_name_qstring);
    QPixmap circular = createCircularPixmap(avatar, label_avatar->width());
    label_avatar->setPixmap(circular);

    ui->label_username->setText(user_name_qstring);
}