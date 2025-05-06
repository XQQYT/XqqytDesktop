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

signals:
    void updataGeneralConfig(std::string module,std::string key,std::string value);

public slots:
    void onGeneralConfig(std::unordered_map<std::string,std::string> general_config);
    void on_checkbox_boot_stateChanged(int arg1);
    void on_combobox_theme_currentTextChanged(const QString &arg1);
    void on_combobox_language_currentTextChanged(const QString &arg1);

private:
    void sendUpdataSignal(std::string key,std::string value);
private:
    Ui::GeneralWidget *ui;
    bool init_done;
};
#endif // GENERALWIDGET_H
