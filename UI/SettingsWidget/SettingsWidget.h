/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include "GeneralWidget.h"
#include "DisplayWidget.h"
#include "SecurityWidget.h"
#include "NetworkWidget.h"
#include "AboutWidget.h"
#include"EventBus.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SettingsWidget; }
QT_END_NAMESPACE

class SettingsWidget : public QWidget
{
    Q_OBJECT

public:
    SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();

private slots:
    void on_btn_general_clicked(bool checked);
    void on_btn_display_clicked(bool checked);
    void on_btn_security_clicked(bool checked);
    void on_btn_network_clicked(bool checked);
    void on_btn_about_clicked(bool checked);
    void updateModuleConfig(std::string module, std::string key, std::string value);
    void publishWrite();
signals:
    void updateGeneral(std::unordered_map<std::string, std::string> config);
    void updateDisplay(std::unordered_map<std::string, std::string> config);
    void updateSecurity(std::unordered_map<std::string, std::string> config);
    void updateNetwork(std::unordered_map<std::string, std::string> config);
    void updateAbout(std::unordered_map<std::string, std::string> config);

private:
    void initConfig();
    void onSettingChanged(std::string module, std::string key, std::string value);
private:
    Ui::SettingsWidget *ui;
    QPushButton *current_btn;
    GeneralWidget *general_widget;
    DisplayWidget *display_widget;
    SecurityWidget *security_widget;
    NetworkWidget *network_widget;
    AboutWidget *about_widget;
    QTimer* write_timer;
};
#endif // SETTINGSWIDGET_H
