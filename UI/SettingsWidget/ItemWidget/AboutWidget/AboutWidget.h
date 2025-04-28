#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class AboutWidget; }
QT_END_NAMESPACE

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    AboutWidget(QWidget *parent = nullptr);
    ~AboutWidget();
private:
    Ui::AboutWidget *ui;
};
#endif // ABOUTWIDGET_H
