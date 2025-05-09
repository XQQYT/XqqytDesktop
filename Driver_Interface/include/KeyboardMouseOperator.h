/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _KEYBOARDMOUSEOPERATOR_H
#define _KEYBOARDMOUSEOPERATOR_H

#include "MouseKeyboardType.h"

class KeyboardMouseInterface
{
public:
    virtual void syncKeyboard(const KeyEventPacket& packet) = 0;
    virtual void syncMouseEvent(const MouseEventPacket& packet) = 0;
};

#endif