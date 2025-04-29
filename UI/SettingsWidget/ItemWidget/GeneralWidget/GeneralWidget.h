#ifndef GENERALWIDGET_H
#define GENERALWIDGET_H

#include <QWidget>
#include <unordered_map>

QT_BEGIN_NAMESPACE
namespace Ui { class GeneralWidget; }
QT_END_NAMESPACE

class GeneralWidget : public QWidget
{
    Q_OBJECT

public:
    GeneralWidget(QWidget *parent = nullptr);
    ~GeneralWidget();

public slots:
    void onGeneralConfig(std::unordered_map<std::string,std::string> general_config);
private:
    Ui::GeneralWidget *ui;
};
#endif // GENERALWIDGET_H
