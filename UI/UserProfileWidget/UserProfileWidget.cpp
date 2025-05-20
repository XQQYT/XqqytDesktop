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
#include "InfoDialog.h"
#include "BubbleMessage.h"
#include "GeneralLineEditDialog.h"
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

    //备份原头像 -> 拷贝选择的头像到程序目录 -> 发送给服务器
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
    GeneralLineEditDialog *dialog = new GeneralLineEditDialog("Update Password", this);
    
    connect(dialog, &GeneralLineEditDialog::enterDone, this, [this,&dialog](QVector<QString> content) {
        if (content.size() < 3) {
            dialog->setTip("Incomplete input");
        }
        else if (content[0].isEmpty()) {
            dialog->setTip("Current password is empty");
        }
        else if (content[1] != content[2]) {
            dialog->setTip("Passwords do not match");
        }
        dialog->close();
        std::vector<std::string> args = {content[0].toStdString(), content[1].toStdString()};
        EventBus::getInstance().publish("/network/send_to_user_server", UserMsgType::UPDATEPASSWORD, std::move(args));
    });

    dialog->addLineEdit("Current Password", true);
    dialog->addLineEdit("New Password", true);
    dialog->addLineEdit("Confirm New Password", true);
    
    dialog->exec(); 
}

void UserProfileWidget::on_btn_change_username_clicked()
{
    GeneralLineEditDialog dialog("Update User Name", this);
    connect(&dialog,&GeneralLineEditDialog::enterDone,this,[=](QVector<QString> content){
        std::vector<std::string> args = {content[0].toStdString()};
        EventBus::getInstance().publish("/network/send_to_user_server", UserMsgType::UPDATEUSERNAME, std::move(args));
        UserInfoManager::getInstance().setChangingUserName(content[0].toStdString());
        ui->label_username->setText(content[0]);
    });
    dialog.addLineEdit("New User Name", false);
    dialog.exec(); 
}

void UserProfileWidget::on_btn_logout_clicked()
{
    std::cout<<"log out"<<std::endl;
}
