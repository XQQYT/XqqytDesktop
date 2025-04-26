#ifndef _X11_H
#define _X11_H

#include "KeyboardMouseOperator.h"
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <X11/keysym.h>

class X11Driver : public KeyboardMouseInterface
{
public:
    X11Driver();
    void syncKeyboard(KeyEventPacket packet) override;
private:
    Display* display;
};
#endif