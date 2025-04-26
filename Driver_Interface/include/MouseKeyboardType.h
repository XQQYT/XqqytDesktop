#ifndef _TYPE_H
#define _TYPE_H

#include <stdint.h>

enum class MouseEventType : uint8_t {
    Move,
    Press,
    Hold,
    Release,
    Wheel
};

enum class MouseButton : uint8_t {
    NoButton,
    LeftButton,
    RightButton,
    MiddleButton
};

struct MouseEventPacket
{
    MouseEventType type;    // 事件类型
    MouseButton button;     // 按键类型（move事件是NoButton）
    int32_t x;              // 鼠标X坐标（可以是比例换算后的）
    int32_t y;              // 鼠标Y坐标
    int32_t wheelDelta;     // 滚轮滚动幅度
};

struct KeyEventPacket
{
    uint32_t key;
    uint32_t modifiers;
    uint8_t is_pressed;
};

#endif