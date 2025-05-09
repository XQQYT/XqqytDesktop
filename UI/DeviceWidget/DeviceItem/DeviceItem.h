/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef DEVICEITEM_H
#define DEVICEITEM_H

#include <QWidget>
#include <QStyle>

QT_BEGIN_NAMESPACE
namespace Ui { class DeviceItem; }
QT_END_NAMESPACE

class DeviceItem : public QWidget
{
    Q_OBJECT

public:
    DeviceItem(QWidget *parent = nullptr);
    ~DeviceItem();
    void retranslateUi();
protected:
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    Ui::DeviceItem *ui;
};
#endif // DEVICEITEM_H
