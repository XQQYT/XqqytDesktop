/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef UTILS_H
#define UTILS_H

#include <QWidget>
#include <QDialog>
#include <QFile>
#include <QPushButton>
#include <QDebug>

std::string getDeviceName();
void turnToRegularNum(QString& str);
void applyStyleSheet(const QString filePath, QWidget* widget);
QString generateRandomString(int length);
QPixmap createCircularPixmap(const QPixmap& src, int size);
void setButtonTextWithElide(QPushButton *btn, const QString &fullText);

class DialogOperator{
public:
    static void centerDialog(QDialog &dialog, QWidget *parent = nullptr);
    static void setDefaultWidget(QWidget *parent)
    {
        default_parent = parent;
    }
private:
    static QWidget* default_parent;
};

#endif