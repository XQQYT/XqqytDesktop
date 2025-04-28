#include "NetworkWidget.h"
#include "ui_NetworkWidget.h"

static const std::string module_name = "Network";

NetworkWidget::NetworkWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkWidget)
{
    ui->setupUi(this);
    init_done = false;
}

NetworkWidget::~NetworkWidget()
{
    delete ui;
}

void NetworkWidget::onNetworkConfig(std::unordered_map<std::string,std::string> network_config)
{
    ui->lineedit_username->setText(network_config["proxy_username"].data());
    ui->lineedit_proxy_ip->setText(network_config["proxy_ip"].data());
    ui->lineedit_proxy_port->setText(network_config["proxy_port"].data());
    init_done = true;
}

void NetworkWidget::on_lineedit_proxy_ip_editingFinished()
{
    sendUpdataSignal("proxy_ip",ui->lineedit_proxy_ip->text().toStdString());
}

void NetworkWidget::on_lineedit_proxy_port_editingFinished()
{
    sendUpdataSignal("proxy_port",ui->lineedit_proxy_port->text().toStdString());
}

void NetworkWidget::on_lineedit_username_editingFinished()
{
    sendUpdataSignal("proxy_username",ui->lineedit_username->text().toStdString());
}

void NetworkWidget::sendUpdataSignal(std::string key,std::string value)
{
    if(init_done)
        emit updataNetworkConfig(module_name,key,value);
}
