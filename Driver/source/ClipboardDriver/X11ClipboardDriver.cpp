/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include "WebRTC.h"

#include "ClipboardDriver/X11ClipboardDriver.h"

X11ClipboardDriver::X11ClipboardDriver(WebRTC& instance)
 :webrtc_instance(instance)
 {
    display = XOpenDisplay(nullptr);
        if (!display) {
            std::cerr << "Unable to open X display\n";
            std::exit(1);
        }

        // 创建隐藏窗口用于事件处理
        window = XCreateSimpleWindow(display, DefaultRootWindow(display),
                                     0, 0, 1, 1, 0, 0, 0);

        // 初始化 XFixes
        if (!XFixesQueryExtension(display, &xfixes_event_base, &xfixes_error_base)) {
            std::cerr << "XFixes extension not available\n";
            std::exit(1);
        }

        // 监听 CLIPBOARD 拥有者变化事件
        Atom clipboard = XInternAtom(display, "CLIPBOARD", False);
        XFixesSelectSelectionInput(display, window, clipboard,
                                   XFixesSetSelectionOwnerNotifyMask);

        // 其他 Atoms 初始化
        utf8 = XInternAtom(display, "UTF8_STRING", False);
        target = clipboard;
        property = XInternAtom(display, "MY_CLIP_TEMP", False);

        ignore_next_clipboard_event = false;
 }

 X11ClipboardDriver::~X11ClipboardDriver()
 {
    stopMonitor();
    XDestroyWindow(display, window);
    XCloseDisplay(display);
 }

void X11ClipboardDriver::startMonitor()
{
    if (!display || is_running) return;
    is_running = true;
    monitor_thread = new std::thread(&X11ClipboardDriver::run, this);
}

void X11ClipboardDriver::stopMonitor()
{
    is_running = false;
    // 发送假事件以唤醒 XNextEvent
    XClientMessageEvent msg = {};
    msg.type = ClientMessage;
    msg.display = display;
    msg.window = window;
    msg.message_type = XInternAtom(display, "DUMMY", False);
    msg.format = 32;
    XSendEvent(display, window, False, NoEventMask, (XEvent*)&msg);
    XFlush(display);
    if (monitor_thread && monitor_thread->joinable()) {
        monitor_thread->join();
        delete monitor_thread;
        monitor_thread = nullptr;
    }
}

void X11ClipboardDriver::run() {
    if (!display) return;
    std::cout << "Clipboard watcher running...\n";
    XEvent event;

    while (is_running) {
        XNextEvent(display, &event);

        if (event.type == xfixes_event_base + XFixesSelectionNotify) {
            if (ignore_next_clipboard_event) {
                ignore_next_clipboard_event = false;
                continue;
            }
            std::cout << "Clipboard changed. Requesting contents...\n";
            // 请求剪贴板内容
            XConvertSelection(display, target, utf8, property, window, CurrentTime);
        } else if (event.type == SelectionNotify) {
            if (event.xselection.property == None) {
                std::cerr << "Clipboard content unavailable.\n";
                continue;
            }

            Atom actual_type;
            int actual_format;
            unsigned long nitems, bytes_after;
            unsigned char* prop = nullptr;

            XGetWindowProperty(display, window, property, 0, 100000, False,
                               AnyPropertyType, &actual_type, &actual_format,
                               &nitems, &bytes_after, &prop);

            if (actual_type == utf8 && prop) {
                std::string content(reinterpret_cast<char*>(prop), nitems);
                webrtc_instance.sendClipboardContent(std::move(content));
                XFree(prop);
            } else {
                std::cerr << "Unsupported clipboard format\n";
            }
        }
    }
}

void X11ClipboardDriver::setClipboardText(std::string text) 
{
    ignore_next_clipboard_event = true;
    std::string cmd = "echo \"" + text + "\" | xclip -selection clipboard";
    int result = std::system(cmd.c_str());
    if (result != 0) {
        std::cerr << "Failed to set clipboard text\n";
    }
}