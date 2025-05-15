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

void applyStyleSheet(const QString filePath, QWidget* widget);
QString generateRandomString(int length);
QPixmap createCircularPixmap(const QPixmap& src, int size);
void setButtonTextWithElide(QPushButton *btn, const QString &fullText);
void centerDialog(QWidget *parent, QDialog &dialog);

#endif