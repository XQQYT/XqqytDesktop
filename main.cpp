#include "MainWidget.h"
#include "EventBus.h"
#include <QApplication>

//注册必需事件
void initEventBusRegisterEvent()
{
    EventBus::getInstance().registerEvent("/network/connect_to_server_and_target");
    EventBus::getInstance().registerEvent("/network/registration_rejected");
    EventBus::getInstance().registerEvent("/network/target_is_offline");
}
//使模块订阅好事件
void initModuleSubscribe()
{
    EventBus::getInstance().initModuleSubscribe();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initEventBusRegisterEvent();
    initModuleSubscribe();
    MainWidget w;
    w.show();
    return a.exec();
}
