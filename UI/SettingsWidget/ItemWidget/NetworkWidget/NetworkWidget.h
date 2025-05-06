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
    void retranslateUi();
signals:
    void updataNetworkConfig(std::string module,std::string key,std::string value);

public slots:
    void onNetworkConfig(std::unordered_map<std::string,std::string> general_config);
    void on_lineedit_proxy_ip_editingFinished();
    void on_lineedit_proxy_port_editingFinished();
    void on_lineedit_username_editingFinished();

private:
    void sendUpdataSignal(std::string key,std::string value);
private:
    Ui::NetworkWidget *ui;
    bool init_done;
};
#endif // NETWORKWIDGET_H
