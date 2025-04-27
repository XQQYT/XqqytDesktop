#include "InfoDialog.h"
#include "ui_InfoDialog.h"
#include <iostream>

InfoDialog::InfoDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    title_content_count = 0;
}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::setPargentWidget(QWidget* parent_widget)
{
    this->parent_widget =  parent_widget;
}

InfoDialog& InfoDialog::operator<<(const std::any& input)
{
    if (input.type() == typeid(QString)) {
        if(title_content_count == 0)
            setTitle(std::any_cast<QString>(input));
        else if(title_content_count == 1)
            setContent(std::any_cast<QString>(input));
        else
            appendContent(std::any_cast<QString>(input));
        title_content_count++;
    }
    else if (input.type() == typeid(const char*)) {
        if(title_content_count == 0)
            setTitle(QString::fromUtf8(std::any_cast<const char*>(input)));
        else if(title_content_count == 1)
            setContent(QString::fromUtf8(std::any_cast<const char*>(input)));
        else
            appendContent(QString::fromUtf8(std::any_cast<const char*>(input)));
        title_content_count++;
    }
    else if (input.type() == typeid(std::string)) {
        if(title_content_count == 0)
            setTitle(QString::fromStdString(std::any_cast<std::string>(input)));
        else if(title_content_count == 1)
            setContent(QString::fromStdString(std::any_cast<std::string>(input)));
        else
            appendContent(QString::fromStdString(std::any_cast<std::string>(input)));
        title_content_count++;
    }
    else if (input.type() == typeid(InfoType)) {
        addButton(std::any_cast<InfoType>(input));
    }
    else if (input.type() == typeid(exec_trigger)) {
        exec();  
    }
    else {
        setTitle("Unsupported type");
    }

    return *this;
}

void InfoDialog::sendSignal(InfoType type)
{
    switch (type)
    {
    case InfoType::YES:
        emit YES();
        break;
    case InfoType::NO:
        emit NO();
        break;
    case InfoType::OK:
        emit OK();
        break;
    case InfoType::CANCEL:
        emit CANCEL();
        break;
    default:
        break;
    }
}


void InfoDialog::addButton(InfoType type)
{
    QPushButton *btn = new QPushButton(this);

    QString buttonText;
    switch (type) {
    case InfoType::YES: buttonText = "Yes"; break;
    case InfoType::NO: buttonText = "No"; break;
    case InfoType::OK: buttonText = "OK"; break;
    case InfoType::CANCEL: buttonText = "Cancel"; break;
    default: buttonText = "Unknown"; break;
    }
    btn->setText(buttonText);

    btn->setProperty("type", static_cast<int>(type));
    ui->btn_layout->addWidget(btn);

    connect(btn, &QPushButton::clicked, this, [=]() {
        QVariant prop = btn->property("type");
        if (prop.isValid() && prop.canConvert<int>()) {
            InfoType infoType = static_cast<InfoType>(prop.toInt());
            sendSignal(infoType);
            reset();
            close();
        }
    });
}

void InfoDialog::setTitle(QString&& str)
{
    ui->label_title->setText(std::move(str));
}
void InfoDialog::setContent(QString&& str)
{
    ui->label_content->setText(std::move(str));
}

void InfoDialog::appendContent(QString&& str)
{
    QString original = ui->label_content->text();
    original.append(str);
    ui->label_content->setText(original);
}

void InfoDialog::reset()
{
    ui->label_title->clear();
    ui->label_content->clear();
    title_content_count = 0;
    QLayoutItem* item = nullptr;
    while ((item = ui->btn_layout->takeAt(0)) != nullptr) 
    {
        if (QWidget* widget = item->widget()) {
            delete widget;
        }
        delete item;
    }
}

void InfoDialog::showEvent(QShowEvent* event)
{
    QDialog::showEvent(event);

    if (parent_widget) {
        QRect parentRect = parent_widget->geometry();
        move(parentRect.center());
    }
}