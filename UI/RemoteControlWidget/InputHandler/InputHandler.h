/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _INPUTHANDLER_H
#define _INPUTHANDLER_H

#include <QWidget>
#include <QMouseEvent>
#include <QTimer>
#include "EventBus.h"
#include "MouseKeyboardType.h"

class InputHandler : public QObject
{
    Q_OBJECT
public:
    explicit InputHandler(QWidget *parent);
    ~InputHandler();

    inline void setScale(const float scalx, const float scaley){scale_x = scalx; scale_y = scaley;}

    void handleMouseMoveEvent(QMouseEvent* event);
    void handleMousePressEvent(QMouseEvent* event);
    void handleMouseReleaseEvent(QMouseEvent* event);
    void handleWheelEvent(QWheelEvent* event);

    void handleKeyPressEvent(QKeyEvent* event);
    void handleKeyReleaseEvent(QKeyEvent* event);

private:
    void convertPos(MouseEventPacket& packet);
    MouseButton toMouseButton(Qt::MouseButton qtButton);
    void sendHoldPackets();
private:

    float scale_x;
    float scale_y;

    QTimer* hold_timer = nullptr;
    bool left_button_pressed = false;
    bool right_button_pressed = false;
    QWidget* parent;
};

#endif //INPUTHANDLER_H