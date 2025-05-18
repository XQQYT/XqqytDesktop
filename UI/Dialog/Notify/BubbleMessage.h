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

    static BubbleMessage& getInstance()
    {
        static BubbleMessage instance;
        return instance;
    }
    void show(const QString &message, QWidget *parent = nullptr, int displayTime = 3000);
    void error(const QString &message, QWidget *parent = nullptr,int displayTime = 3000);
    void setDefaultWidget(QWidget* widget)
    {
        m_parentWidget = widget;
    };
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private:
    explicit BubbleMessage(QWidget *parent = nullptr);
    ~BubbleMessage();
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