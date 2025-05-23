/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "RoundedScrollArea.h"
#include <QGraphicsDropShadowEffect>
#include <QPainter>

RoundedScrollArea::RoundedScrollArea(QWidget *parent)
    : QScrollArea(parent)
{
    setWidgetResizable(true);
    setFrameShape(QFrame::NoFrame);
    setAttribute(Qt::WA_TranslucentBackground);
    viewport()->setAttribute(Qt::WA_TranslucentBackground);

    // 背景透明
    setStyleSheet("QScrollArea { background: transparent; border: none; }");
    viewport()->setStyleSheet("background: transparent; border-radius: 20px;");

    // 阴影效果
    auto *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(20);
    shadow->setOffset(0, 2);
    setGraphicsEffect(shadow);
}

void RoundedScrollArea::resizeEvent(QResizeEvent *event) {
    QScrollArea::resizeEvent(event);
    update();
}
