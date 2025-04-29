#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DisplayWidget; }
QT_END_NAMESPACE

class DisplayWidget : public QWidget
{
    Q_OBJECT

public:
    DisplayWidget(QWidget *parent = nullptr);
    ~DisplayWidget();

public slots:
    void onDisplayConfig(std::unordered_map<std::string,std::string> display_config);
private:
    Ui::DisplayWidget *ui;
};
#endif // DISPLAYWIDGET_H
