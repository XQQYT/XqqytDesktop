#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "WidgetManager.h"
#include <QThread>

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
private:
    Ui::MainWidget *ui;
};
#endif // MAINWIDGET_H
