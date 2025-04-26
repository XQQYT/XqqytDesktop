#ifndef _KEYBOARDMOUSEOPERATOR_H
#define _KEYBOARDMOUSEOPERATOR_H

#include "MouseKeyboardType.h"

class KeyboardMouseInterface
{
public:
    virtual void syncKeyboard(KeyEventPacket packet) = 0;
};

#endif