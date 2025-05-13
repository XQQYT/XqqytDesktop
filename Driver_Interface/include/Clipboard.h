/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _CLIPBOARD_H
#define _CLIPBOARD_H

#include <string>

class ClipboardInterface
{
public:
    ClipboardInterface(){};
    virtual ~ClipboardInterface(){};
    virtual void startMonitor() = 0;
    virtual void stopMonitor() = 0;
    virtual void setClipboardText(std::string text) = 0;
};

#endif