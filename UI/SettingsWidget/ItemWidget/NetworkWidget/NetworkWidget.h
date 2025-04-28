#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class NetworkWidget; }
QT_END_NAMESPACE

class NetworkWidget : public QWidget
{
    Q_OBJECT

public:
    NetworkWidget(QWidget *parent = nullptr);
    ~NetworkWidget();
private:
    Ui::NetworkWidget *ui;
};
#endif // NETWORKWIDGET_H
