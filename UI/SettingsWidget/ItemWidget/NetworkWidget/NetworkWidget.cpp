#include "NetworkWidget.h"
#include "ui_NetworkWidget.h"

NetworkWidget::NetworkWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkWidget)
{
    ui->setupUi(this);
}

NetworkWidget::~NetworkWidget()
{
    delete ui;
}

void NetworkWidget::onNetworkConfig(std::unordered_map<std::string,std::string> network_config)
{
    ui->lineedit_username->setText(network_config["user_name"].data());
    ui->lineedit_proxy_ip->setText(network_config["proxy_ip"].data());
    ui->lineedit_proxy_port->setText(network_config["proxy_port"].data());
}
