/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "InputHandler.h"
#include <QOpenGLFunctions>
#include "RemoteControlWidget.h"
#include <iostream>
#include "Render.h"
#include <fstream>

InputHandler::InputHandler(QWidget *parent)
:parent(parent)
{
    hold_timer = new QTimer();
    connect(hold_timer, &QTimer::timeout, this, &InputHandler::sendHoldPackets);
    hold_timer->start(50);
}

InputHandler::~InputHandler()
{
    hold_timer->stop();
    delete hold_timer;
}

void InputHandler::convertPos(MouseEventPacket& packet)
{
    packet.x = packet.x * scale_x;
    packet.y = packet.y * scale_y;
}

MouseButton InputHandler::toMouseButton(Qt::MouseButton qtButton)
{
    switch (qtButton)
    {
    case Qt::LeftButton:
        return MouseButton::LeftButton;
    case Qt::RightButton:
        return MouseButton::RightButton;
    case Qt::MiddleButton:
        return MouseButton::MiddleButton;
    default:
        return MouseButton::NoButton;
    }
}

void InputHandler::handleMouseMoveEvent(QMouseEvent* event)
{
    // if (!event | left_button_pressed |right_button_pressed) return;

    if (!event) return;
    QPoint pos = event->pos();

    MouseEventPacket packet;
    packet.type = MouseEventType::Move;
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = 0;
    std::cout<<"locale "<<packet.x<<","<<packet.y<<std::endl;
    convertPos(packet);
    std::cout<<"remote "<<packet.x<<","<<packet.y<<std::endl;
    EventBus::getInstance().publish(EventBus::EventType::MouseEvent_HasEvent,packet);
}

void InputHandler::handleMousePressEvent(QMouseEvent* event)
{
    if (!event) return;

    if (event->button() == Qt::LeftButton)
        left_button_pressed = true;
    if (event->button() == Qt::RightButton)
        right_button_pressed = true;

    QPoint pos = event->pos();

    MouseEventPacket packet;
    packet.type = MouseEventType::Press;
    packet.button = toMouseButton(event->button());
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = 0;
    convertPos(packet);
    EventBus::getInstance().publish(EventBus::EventType::MouseEvent_HasEvent,packet);
}

void InputHandler::handleMouseReleaseEvent(QMouseEvent* event)
{
    if (!event) return;

    if (event->button() == Qt::LeftButton)
        left_button_pressed = false;
    if (event->button() == Qt::RightButton)
        right_button_pressed = false;

    QPoint pos = event->pos();

    MouseEventPacket packet;
    packet.type = MouseEventType::Release;
    packet.button = toMouseButton(event->button()); // 哪个键释放
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = 0; // 无滚轮
    convertPos(packet);
    EventBus::getInstance().publish(EventBus::EventType::MouseEvent_HasEvent,packet);
}

void InputHandler::handleWheelEvent(QWheelEvent* event)
{
    if (!event) return;

    QPoint pos = event->position().toPoint(); // Qt6用position()，Qt5用pos()

    MouseEventPacket packet;
    packet.type = MouseEventType::Wheel;
    packet.button = MouseButton::NoButton; // 滚轮事件没有按钮
    packet.x = pos.x();
    packet.y = pos.y();
    packet.wheelDelta = event->angleDelta().y(); // y方向的滚动，单位通常是120或-120
    convertPos(packet);
    EventBus::getInstance().publish(EventBus::EventType::MouseEvent_HasEvent,packet);
}

void InputHandler::sendHoldPackets()
{
    QPoint pos = parent->mapFromGlobal(QCursor::pos()); // 获取当前鼠标位置（相对于窗口）

    if (parent->rect().contains(pos)) { // 确保鼠标还在窗口内
        if (left_button_pressed || right_button_pressed) {
            MouseEventPacket packet;
            packet.type = MouseEventType::Press;
            packet.button = left_button_pressed ? MouseButton::LeftButton :
                           right_button_pressed ? MouseButton::RightButton :
                           MouseButton::NoButton;
            packet.x = pos.x();
            packet.y = pos.y();
            packet.wheelDelta = 0;
            convertPos(packet);
            EventBus::getInstance().publish(EventBus::EventType::MouseEvent_HasEvent, packet);
        }
    }
}

void InputHandler::handleKeyPressEvent(QKeyEvent* event)
{
    std::cout<<"keyPressEvent"<<std::endl;
    KeyEventPacket packet;
    packet.key = event->key();
    packet.modifiers = event->modifiers();
    packet.is_pressed = true;
    EventBus::getInstance().publish(EventBus::EventType::KeyboardEvent_HasEvent,packet);
}

void InputHandler::handleKeyReleaseEvent(QKeyEvent* event)
{
    std::cout<<"keyReleaseEvent"<<std::endl;
    KeyEventPacket packet;
    packet.key = event->key();
    packet.modifiers = event->modifiers();
    packet.is_pressed = false;
    EventBus::getInstance().publish(EventBus::EventType::KeyboardEvent_HasEvent,packet);
}