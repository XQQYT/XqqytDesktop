#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "WidgetManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    void setCurrentWidget(const WidgetManager::WidgetType type);
private slots:
    void on_btn_device_clicked(bool checked);
    void on_btn_connect_clicked(bool checked);
private:
    Ui::MainWidget *ui;
    WidgetManager::WidgetType current_widget;
    QPushButton* current_btn;
};
#endif // MAINWIDGET_H
