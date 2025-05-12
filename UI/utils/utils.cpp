/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "utils.h"
#include <QRandomGenerator>

void applyStyleSheet(const QString filePath, QWidget* widget)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to load QSS:" << filePath;
        return;
    }

    QString style = QString::fromUtf8(file.readAll());

    widget->setStyleSheet(style);
}

QString generateRandomString(int length) {
    const QString characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    QString randomString;

    for (int i = 0; i < length; ++i) {
        int randomIndex = QRandomGenerator::global()->bounded(characters.length());
        randomString += characters[randomIndex];
    }

    return randomString;
}