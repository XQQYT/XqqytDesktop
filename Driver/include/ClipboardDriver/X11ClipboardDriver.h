/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#ifndef _X11ClipboardDriver_H
#define _X11ClipboardDriver_H

extern "C" {
    #include <X11/Xlib.h>
    #include <X11/Xatom.h>
    #include <X11/extensions/Xfixes.h>
}

#include <iostream>
#include <string>
#include <cstring>
#include <thread>
#include <atomic>


class WebRTC;
class X11ClipboardDriver
{
public:
    X11ClipboardDriver(WebRTC& instance);
    ~X11ClipboardDriver();
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
    WebRTC& webrtc_instance;
};

#endif