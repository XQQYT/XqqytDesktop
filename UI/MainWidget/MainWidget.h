#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "RemoteControlWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
private slots:
    void on_btn_connect_clicked();
private:
    Ui::MainWidget *ui;
    RemoteControlWidget* w;
};
#endif // WIDGET_H
