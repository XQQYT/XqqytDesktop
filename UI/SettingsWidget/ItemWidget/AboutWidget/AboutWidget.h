/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>

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
private:
    Ui::AboutWidget *ui;
    QString version;
};
#endif // ABOUTWIDGET_H
