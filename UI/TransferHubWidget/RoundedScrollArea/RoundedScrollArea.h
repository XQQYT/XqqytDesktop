/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef ROUNDEDSCROLLAREA_H
#define ROUNDEDSCROLLAREA_H

#include <QScrollArea>
#include <QPainter>
#include "Fileitem/Fileitem.h"

// RoundedScrollArea.h
class RoundedScrollArea : public QScrollArea {
    Q_OBJECT
public:
    explicit RoundedScrollArea(QWidget *parent = nullptr);
    void addFile(bool is_remote,QString& detail, size_t size = 0, bool is_dir = false);
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // ROUNDEDSCROLLAREA_H
