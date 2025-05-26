/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "AboutWidget.h"
#include "utils.h"
#include "SettingInfo.h"
#include "ui_AboutWidget.h"
#include "EventBus.h"
#include <iostream>
#include <sstream>
#include <filesystem>
#include <QProcess>
#include <QCoreApplication>

namespace fs = std::filesystem;

AboutWidget::AboutWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
    applyStyleSheet(QString::fromStdString(*(SettingInfoManager::getInstance().getCurrentThemeDir()) + std::string("/SettingsWidget/ItemWidget/AboutWidget.qss")),this);
    
    EventBus::getInstance().subscribe(EventBus::EventType::Network_LastestVersionResult,std::bind(
        &AboutWidget::onLastestVersionResult,
        this,
        std::placeholders::_1,
        std::placeholders::_2,
        std::placeholders::_3
    ));
    EventBus::getInstance().subscribe(EventBus::EventType::Network_VersionPackageProgress,[=](uint32_t receive_size, uint32_t total){
        QMetaObject::invokeMethod(this, [=]() {
            uint16_t progress = static_cast<uint16_t>((static_cast<uint64_t>(receive_size) * 100) / total);
            loading_dialog.show();
            loading_dialog.setProgress(progress);
            if(receive_size >= total)
            {
                loading_dialog.hide();
                DialogOperator::centerDialog(confirm_dialog);
                confirm_dialog.exec("Install the new version now","Install");
            }
        });
    });
    connect(&update_dialog,&UpdateDialog::update,this,&AboutWidget::onUpdate);
    connect(&confirm_dialog, &ConfirmDialog::ChooseResult, this, [=](bool result){
        if (result) {
            QProcess::startDetached("/bin/bash", QStringList() << "Scripts/update/update.sh");
            QCoreApplication::exit(0);
        }
    });
}

AboutWidget::~AboutWidget()
{
    delete ui;
}

void AboutWidget::onAboutConfig(std::unordered_map<std::string,std::string> about_config)
{
    ui->label_version->setText(ui->label_version->text() + QString::fromStdString(about_config["version"]));
    version = QString::fromStdString(about_config["version"]);
    std::cout<<"version -> "<<about_config["version"]<<std::endl;
}

void AboutWidget::retranslateUi()
{
    ui->retranslateUi(this);
    ui->label_version->setText(ui->label_version->text() + version);
}

void AboutWidget::on_btn_checkupdata_clicked()
{
    EventBus::getInstance().publish(EventBus::EventType::Network_GetLastestVersion);
}

void createFolder(const std::string &path) {
    try {
        if (fs::create_directories(path)) {
            std::cout << "Folder created: " << path << std::endl;
        } else {
            std::cout << "Folder already exists or failed: " << path << std::endl;
        }
    } catch (const fs::filesystem_error &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

bool isNewerVersion(const std::string& currentVersion, const std::string& newVersion) {
    auto parseVersion = [](const std::string& ver) {
        std::vector<int> nums;
        size_t start = ver.find_first_of("0123456789");  // 跳过 'v'
        std::istringstream iss(ver.substr(start));
        std::string token;
        while (std::getline(iss, token, '.')) {
            nums.push_back(std::stoi(token));
        }
        return nums;
    };

    std::vector<int> currNums = parseVersion(currentVersion);
    std::vector<int> newNums = parseVersion(newVersion);

    // 比较对应数字
    size_t len = std::max(currNums.size(), newNums.size());
    for (size_t i = 0; i < len; ++i) {
        int curr = (i < currNums.size()) ? currNums[i] : 0;
        int newer = (i < newNums.size()) ? newNums[i] : 0;
        if (newer > curr) return true;
        if (newer < curr) return false;
    }
    return false;
}

void AboutWidget::onLastestVersionResult(std::string version, std::string description, std::string date)
{
    QMetaObject::invokeMethod(this, [=]() {
        if(isNewerVersion(SettingInfoManager::getInstance().getValue("Meta","version"),version))
        {
            createFolder("tmp");
            update_dialog.setVersionText(version,description,date);
            DialogOperator::centerDialog(update_dialog);
            update_dialog.show();
        }
        else
        {
            ui->btn_checkupdata->setText("It is already the latest version");
        }
    });
}

void AboutWidget::onUpdate()
{
    EventBus::getInstance().publish(EventBus::EventType::Network_GetVersionPackage);
}