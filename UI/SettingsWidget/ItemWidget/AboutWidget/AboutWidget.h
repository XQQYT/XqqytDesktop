/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>
#include "UpdateDialog.h"
#include "LoadingDialog.h"
#include "ConfirmDialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class AboutWidget; }
QT_END_NAMESPACE

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    AboutWidget(QWidget *parent = nullptr);
    ~AboutWidget();
    void retranslateUi();
public slots:
    void onAboutConfig(std::unordered_map<std::string,std::string> about_config);
private slots:
    void on_btn_checkupdata_clicked();
    void onLastestVersionResult(std::string version, std::string description, std::string date);
    void onUpdate();
private:
    Ui::AboutWidget *ui;
    QString version;
    UpdateDialog update_dialog;
    LoadingDialog loading_dialog;
    ConfirmDialog confirm_dialog;
};
#endif // ABOUTWIDGET_H
