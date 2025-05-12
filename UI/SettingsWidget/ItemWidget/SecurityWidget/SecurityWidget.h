/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef SECURITYWIDGET_H
#define SECURITYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class SecurityWidget; }
QT_END_NAMESPACE

class SecurityWidget : public QWidget
{
    Q_OBJECT

public:
    SecurityWidget(QWidget *parent = nullptr);
    ~SecurityWidget();
    void retranslateUi();
signals:
    void updateSecurityConfig(std::string module,std::string key,std::string value);

public slots:
    void onSecurityConfig(std::unordered_map<std::string,std::string> general_config);
    void on_combobox_update_frequency_currentTextChanged(const QString &arg1);

private:
    void sendUpdataSignal(std::string key,std::string value);

private:
    Ui::SecurityWidget *ui;
    bool init_done;
};
#endif // SECURITYWIDGET_H
