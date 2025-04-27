#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QPushButton>
#include <any>
#include <functional>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class InfoDialog; }
QT_END_NAMESPACE

class InfoDialog : public QDialog
{
public:
    struct exec_trigger {};
    static constexpr exec_trigger end{};

    enum class InfoType
    {
        YES,
        NO,
        OK,
        CANCEL
    };

    Q_OBJECT

public:
    InfoDialog(QWidget *parent = nullptr);
    InfoDialog& operator<<(const std::any& input);
    void setPargentWidget(QWidget* parent_widget);
    ~InfoDialog();
signals:
    void YES();
    void NO();
    void OK();
    void CANCEL();
private:
    void addButton(InfoType type);
    void sendSignal(InfoType type);
    void setTitle(QString&& str);
    void setContent(QString&& str);
    void appendContent(QString&& str);
    void reset();
protected:
    void showEvent(QShowEvent* event);
private:
    Ui::InfoDialog *ui;
    int title_content_count;
    QWidget* parent_widget;
};
#endif // INFODIALOG_H
