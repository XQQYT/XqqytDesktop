/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

 #include "ClipboardDriver/X11.h"

 ClipboardDriver::ClipboardDriver()
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
 }

 ClipboardDriver::~ClipboardDriver()
 {
    stopMonitor();
    XDestroyWindow(display, window);
    XCloseDisplay(display);
 }

void ClipboardDriver::startMonitor()
{
    if (!display || is_running) return;
    is_running = true;
    monitor_thread = new std::thread(&ClipboardDriver::run, this);
}

void ClipboardDriver::stopMonitor()
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

void ClipboardDriver::run() {
    if (!display) return;
    std::cout << "Clipboard watcher running...\n";
    XEvent event;

    while (is_running) {
        XNextEvent(display, &event);

        if (event.type == xfixes_event_base + XFixesSelectionNotify) {
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
                std::cout << "Clipboard content: " << content << "\n";
                XFree(prop);
            } else {
                std::cerr << "Unsupported clipboard format\n";
            }
        }
    }
}