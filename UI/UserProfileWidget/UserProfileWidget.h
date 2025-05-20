/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef USERPROFILEWIDGET_H
#define USERPROFILEWIDGET_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class UserProfileWidget; }
QT_END_NAMESPACE

class UserProfileWidget : public QDialog
{
    Q_OBJECT

public:
    UserProfileWidget(QWidget *parent = nullptr);
    ~UserProfileWidget();
    void loadUserInfo();
private:
private:
    Ui::UserProfileWidget *ui;
};
#endif // USERPROFILEWIDGET_H
