#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>
#include "DeviceItem/DeviceItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceWidget; }
QT_END_NAMESPACE

class DeviceWidget : public QWidget
{
    Q_OBJECT

public:
    DeviceWidget(QWidget *parent = nullptr);
    ~DeviceWidget();
private:
    void onSettingChanged(std::string module, std::string key, std::string value);

private:
    Ui::DeviceWidget *ui;
};
#endif // DEVICEWIDGET_H
