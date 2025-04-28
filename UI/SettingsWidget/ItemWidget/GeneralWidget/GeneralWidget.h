#ifndef GENERALWIDGET_H
#define GENERALWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GeneralWidget; }
QT_END_NAMESPACE

class GeneralWidget : public QWidget
{
    Q_OBJECT

public:
    GeneralWidget(QWidget *parent = nullptr);
    ~GeneralWidget();
private:
    Ui::GeneralWidget *ui;
};
#endif // GENERALWIDGET_H
