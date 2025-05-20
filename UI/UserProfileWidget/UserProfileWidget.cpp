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
#include "EventBus.h"
#include "GlobalEnum.h"
#include "BubbleMessage.h"
#include <QLabel>
#include <iostream>
#include <QFileDialog>

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

void UserProfileWidget::on_btn_upload_avatar_clicked()
{
    QString selected_avatar_path = QFileDialog::getOpenFileName(
        this,
        tr("Select Avatar"),
        "",
        tr("Image File (*.png *.jpg *.jpeg *.bmp *.gif)")
    );

    if (selected_avatar_path.isEmpty()) {
        return;
    }
    QPixmap avatar(selected_avatar_path);
    QPixmap circular = createCircularPixmap(avatar, ui->label_avatar->width());
    ui->label_avatar->setPixmap(circular);

    std::string avatar_dir("User/Avatar/" + UserInfoManager::getInstance().getUserName());
    std::string tmp_dir("User/tmp/"+ UserInfoManager::getInstance().getUserName());

    //备份原头像
    EventBus::getInstance().publish<std::string, std::string, std::function<void()>>(
        "/config/copy_file",
        avatar_dir,
        tmp_dir,
        [selected_avatar_path,avatar_dir]() {
            EventBus::getInstance().publish<std::string, std::string, std::function<void()>>(
                "/config/copy_file",
                selected_avatar_path.toStdString(),
                avatar_dir,
                [selected_avatar_path]() {
                    std::vector<std::string> args = {
                        UserInfoManager::getInstance().getUserName(),
                        selected_avatar_path.toStdString()
                    };
                    EventBus::getInstance().publish("/network/send_to_user_server", UserMsgType::UPDATEAVATAR, std::move(args));
                }
            );
        }
    );
}

void UserProfileWidget::on_btn_change_password_clicked()
{
    std::cout<<"change password"<<std::endl;
}

void UserProfileWidget::on_btn_change_username_clicked()
{
    std::cout<<"change user name"<<std::endl;
}

void UserProfileWidget::on_btn_logout_clicked()
{
    std::cout<<"log out"<<std::endl;
}
