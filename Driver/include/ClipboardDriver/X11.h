/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _ClipboardDriver_H
#define _ClipboardDriver_H

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xfixes.h>
#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <atomic>

class ClipboardDriver
{
public:
    ClipboardDriver();
    ~ClipboardDriver();
    void startMonitor();
    void stopMonitor();

private:
    void run();

private:
    std::atomic<bool> is_running{false};
    std::thread *monitor_thread;
    Display* display;
    Window window;
    Atom target;
    Atom utf8;
    Atom property;
    int xfixes_event_base;
    int xfixes_error_base;
};

#endif