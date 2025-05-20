/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef GENERALLINEEDITDIALOG_H
#define GENERALLINEEDITDIALOG_H

#include <QDialog>
#include <QVector>
#include <QLineEdit>

QT_BEGIN_NAMESPACE
namespace Ui { class GeneralLineEditDialog; }
QT_END_NAMESPACE

class GeneralLineEditDialog : public QDialog
{
    Q_OBJECT

public:
    GeneralLineEditDialog(QString title, QWidget *parent = nullptr);
    ~GeneralLineEditDialog();
    void addLineEdit(QString text);
signals:
    void enterDone(QVector<QString> input_content);
private slots:
    void on_btn_done_clicked();
    void on_btn_cancel_clicked();
private:
    Ui::GeneralLineEditDialog *ui;
    QVector<QLineEdit*> line_edit_list;
};
#endif // EDITDEVICECOMMENTDIALOG_H
