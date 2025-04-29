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

public slots:
    void onNetworkConfig(std::unordered_map<std::string,std::string> network_config);
private:
    Ui::NetworkWidget *ui;
};
#endif // NETWORKWIDGET_H
