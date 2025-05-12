/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _X11KEYBOARDMOUSEDRIVER_H
#define _X11KEYBOARDMOUSEDRIVER_H

extern "C" {
    #include <X11/Xlib.h>
    #include <X11/extensions/Xfixes.h> 
    #include <X11/extensions/XTest.h>
    #include <X11/keysym.h>
}

#include "KeyboardMouseOperator.h"

class X11KeyboardMouseDriver : public KeyboardMouseInterface
{
public:
    X11KeyboardMouseDriver();
    ~X11KeyboardMouseDriver();
    void syncKeyboard(const KeyEventPacket& packet) override;
    void syncMouseEvent(const MouseEventPacket& packet) override;
private:
    Display* display;
};
#endif