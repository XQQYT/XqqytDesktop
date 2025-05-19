/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "BubbleMessage.h"
#include <QVBoxLayout>
#include <QDebug>

BubbleMessage::BubbleMessage(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    
    initUI();
    setupAnimation();
}

BubbleMessage::~BubbleMessage()
{
    if (m_timer) {
        m_timer->stop();
        delete m_timer;
    }
    delete m_animation;
    delete m_opacityEffect;
}

void BubbleMessage::initUI()
{
    m_messageLabel = new QLabel(this);
    m_messageLabel->setAlignment(Qt::AlignCenter);
    m_messageLabel->setWordWrap(true);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_messageLabel);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
    
    m_timer = new QTimer(this);
    m_timer->setSingleShot(true);
    connect(m_timer, &QTimer::timeout, this, [this]() {
        m_animation->setStartValue(1.0);
        m_animation->setEndValue(0.0);
        m_animation->start();
    });
}

void BubbleMessage::setupAnimation()
{
    m_opacityEffect = new QGraphicsOpacityEffect(this);
    m_opacityEffect->setOpacity(1.0);
    setGraphicsEffect(m_opacityEffect);
    
    m_animation = new QPropertyAnimation(m_opacityEffect, "opacity", this);
    m_animation->setDuration(1500);
    m_animation->setEasingCurve(QEasingCurve::OutQuad);
    
    connect(m_animation, &QPropertyAnimation::finished, this, [this]() {
        if (m_opacityEffect->opacity() <= 0.01) {
            hide();
        }
    });
}

void BubbleMessage::show(const QString &message,QWidget *parent , int displayTime)
{
    QWidget* real_widget = nullptr;
    if(!parent)
        real_widget = m_parentWidget;
    else
        real_widget = parent;
    showInternal(real_widget, message, 
                "background-color: rgba(0, 150, 0, 200);",
                displayTime);
}

void BubbleMessage::error(const QString &message, QWidget *parent, int displayTime)
{
    QWidget* real_widget = nullptr;
    if(!parent)
        real_widget = m_parentWidget;
    else
        real_widget = parent;
    showInternal(real_widget, message, 
                "background-color: rgba(200, 0, 0, 200);",
                displayTime);
}

void BubbleMessage::showInternal(QWidget *parent, const QString &message, 
                               const QString &styleSheet, int displayTime)
{
    if (!parent) {
        qWarning() << "Parent widget is null, cannot show bubble message";
        return;
    }
    
    QMetaObject::invokeMethod(this, [=]() {
        m_animation->stop();
        m_timer->stop();
        
        QString fullStyle = QString("QLabel {"
                                  "color: white;"
                                  "font: 14px;"

                                  "padding: 8px 12px;"
                                  "border-radius: 8px;"
                                  "%1"
                                  "}").arg(styleSheet);
        
        m_messageLabel->setText(message);
        m_messageLabel->setStyleSheet(fullStyle);
        
        adjustSize();
        updatePosition();
        
        parent->installEventFilter(this);
        
        m_opacityEffect->setOpacity(0.0);
        static_cast<QWidget*>(this)->show();
        m_animation->setStartValue(0.0);
        m_animation->setEndValue(1.0);
        m_animation->start();
        raise();
        m_timer->start(displayTime);
    }, Qt::QueuedConnection);
}

void BubbleMessage::updatePosition()
{
    if (!m_parentWidget) return;

    QRect parentRect = m_parentWidget->rect();
    QPoint bottomCenter = m_parentWidget->mapToGlobal(QPoint(
        parentRect.width() / 2, 
        parentRect.height() - height() - m_yOffset
    ));
    
    QRect screenGeometry = QApplication::desktop()->availableGeometry(m_parentWidget);
    bottomCenter.setX(qMax(screenGeometry.left(), 
                         qMin(bottomCenter.x() - width() / 2, 
                             screenGeometry.right() - width())));
    bottomCenter.setY(qMax(screenGeometry.top(), 
                        qMin(bottomCenter.y(), 
                            screenGeometry.bottom() - height())));
    
    move(bottomCenter);
}

bool BubbleMessage::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_parentWidget && 
        (event->type() == QEvent::Move || event->type() == QEvent::Resize)) {
        updatePosition();
    }
    return QWidget::eventFilter(watched, event);
}

void BubbleMessage::hideEvent(QHideEvent *event)
{
    if (m_parentWidget) {
        m_parentWidget->removeEventFilter(this);
        m_parentWidget = nullptr;
    }
    QWidget::hideEvent(event);
}