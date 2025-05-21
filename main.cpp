/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "MainWidget.h"
#include "EventBus.h"
#include <QApplication>

//使模块订阅好事件
void initModuleSubscribe()
{
    EventBus::getInstance().initModuleSubscribe();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initModuleSubscribe();
    MainWidget w;
    w.show();
    return a.exec();
}
