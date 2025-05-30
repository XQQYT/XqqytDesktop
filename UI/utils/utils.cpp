/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "utils.h"
#include <QRandomGenerator>
#include <QPainter>
#include <unistd.h>
#include <QStyle>

QWidget* DialogOperator::default_parent = nullptr;

void turnToRegularNum(QString& str)
{
    for (int i = 3; i < str.length(); i += 4) {
        str.insert(i, ' ');
    }
}

std::string getDeviceName() {
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0) {
        return std::string(hostname);
    } else {
        perror("gethostname");
        return "unknown";
    }
}

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

void DialogOperator::centerDialog(QDialog &dialog, QWidget *parent)
{
    QWidget* real_widget = nullptr;
    if (!parent)
        real_widget = default_parent;
    else
        real_widget = parent;
        
    dialog.setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            dialog.size(),
            real_widget->frameGeometry()
        )
    );
}