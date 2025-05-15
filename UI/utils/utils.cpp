/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "utils.h"
#include <QRandomGenerator>
#include <QPainter>

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

QPixmap createCircularPixmap(const QPixmap& src, int size) {
    QPixmap dst(size, size);
    dst.fill(Qt::transparent);

    QPainter painter(&dst);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    QPainterPath path;
    path.addEllipse(0, 0, size, size);
    painter.setClipPath(path);  // 使用剪切路径

    QPixmap scaled = src.scaled(size, size, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaled);

    return dst;
}

void setButtonTextWithElide(QPushButton *btn, const QString &fullText)
{
    QFontMetrics fm(btn->font());
    QString elidedText = fm.elidedText(fullText, Qt::ElideRight, btn->width() - 10);
    btn->setText(elidedText);
    btn->setToolTip(fullText);
}

void centerDialog(QWidget *parent, QDialog &dialog)
{
    if (!parent)
        return;
    QPoint center = parent->geometry().center();
    QSize dlgSize = dialog.sizeHint();
    dialog.move(center.x() - dlgSize.width() / 2, center.y() - dlgSize.height() / 2);
}