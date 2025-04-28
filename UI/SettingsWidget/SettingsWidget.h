#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "GeneralWidget.h"
#include "DisplayWidget.h"
#include "NetworkWidget.h"
#include "AboutWidget.h"

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
    void on_btn_network_clicked(bool checked);
    void on_btn_about_clicked(bool checked);
private:
    Ui::SettingsWidget *ui;
    QPushButton *current_btn;
    GeneralWidget *general_widget;
    DisplayWidget *display_widget;
    NetworkWidget *network_widget;
    AboutWidget *about_widget;
};
#endif // SETTINGSWIDGET_H
