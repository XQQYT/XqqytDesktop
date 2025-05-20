/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "GeneralLineEditDialog.h"
#include "ui_GeneralLineEditDialog.h"
#include "utils.h"
#include <iostream>

GeneralLineEditDialog::GeneralLineEditDialog(QString title, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GeneralLineEditDialog)
{
    ui->setupUi(this);
    DialogOperator::centerDialog(*this);
    ui->label_title->setText(title);
}

GeneralLineEditDialog::~GeneralLineEditDialog()
{
    delete ui;
}

void GeneralLineEditDialog::on_btn_done_clicked()
{
    if(line_edit_list.size() < 1 || line_edit_list.at(0)->text().isEmpty())
        return;
    QVector<QString> content;
    for(auto& i : line_edit_list)
    {
        content.append(i->text());
    }
    emit enterDone(content);
    reject();
}

void GeneralLineEditDialog::on_btn_cancel_clicked()
{
    reject();
}

void GeneralLineEditDialog::addLineEdit(QString text)
{
    QLineEdit* line_edit = new QLineEdit(this);
    line_edit->setPlaceholderText(text);
    ui->verticalLayout->addWidget(line_edit);
    line_edit_list.append(line_edit);
    line_edit_list[0]->setFocus();
}
