/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef BUBBLEMESSAGE_H
#define BUBBLEMESSAGE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QDesktopWidget>
#include <QApplication>
#include <QEvent>

class BubbleMessage : public QWidget
{
    Q_OBJECT

public:
    explicit BubbleMessage(QWidget *parent = nullptr);
    ~BubbleMessage();

    void show(QWidget *parent, const QString &message, int displayTime = 3000);
    void error(QWidget *parent, const QString &message, int displayTime = 3000);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    void initUI();
    void setupAnimation();
    void showInternal(QWidget *parent, const QString &message, const QString &styleSheet, int displayTime);
    void updatePosition();

    QLabel *m_messageLabel;
    QTimer *m_timer;
    QPropertyAnimation *m_animation;
    QGraphicsOpacityEffect *m_opacityEffect;
    QWidget *m_parentWidget = nullptr;
    int m_yOffset = 20;
};

#endif // BUBBLEMESSAGE_H