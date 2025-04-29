#include "utils.h"

void applyStyleSheet(const QString& filePath, QWidget* widget)
{
    QFile file(filePath);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to load QSS:" << filePath;
        return;
    }

    QString style = QString::fromUtf8(file.readAll());
    qDebug() << "Loaded QSS: " << style;

    widget->setStyleSheet(style);
}