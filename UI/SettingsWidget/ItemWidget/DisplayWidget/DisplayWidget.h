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

signals:
    void updataDisplayConfig(std::string module,std::string key,std::string value);

public slots:
    void onDisplayConfig(std::unordered_map<std::string,std::string> general_config);
    void on_checkbox_render_stateChanged(int arg1);
    void on_combobox_render_rate_currentTextChanged(const QString &arg1);
    void on_combobox_capture_rate_currentTextChanged(const QString &arg1);

private:
    void sendUpdataSignal(std::string key,std::string value);

private:
    Ui::DisplayWidget *ui;
    bool init_done;
};
#endif // DISPLAYWIDGET_H
