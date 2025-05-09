/*
 * XqqytDesktop
 * Author: XQQYT
 * License: MIT
 * Year: 2025
 */

#include <iostream>
#include "KeyboardMouseDriver/X11.h"
#include <unordered_map>

static std::unordered_map<uint32_t, KeySym> qtKeyToX11KeySym = {
    // 字母键 (A-Z)
    { 0x41, XK_a },  // Qt::Key_A
    { 0x42, XK_b },  // Qt::Key_B
    { 0x43, XK_c },  // Qt::Key_C
    { 0x44, XK_d },  // Qt::Key_D
    { 0x45, XK_e },  // Qt::Key_E
    { 0x46, XK_f },  // Qt::Key_F
    { 0x47, XK_g },  // Qt::Key_G
    { 0x48, XK_h },  // Qt::Key_H
    { 0x49, XK_i },  // Qt::Key_I
    { 0x4a, XK_j },  // Qt::Key_J
    { 0x4b, XK_k },  // Qt::Key_K
    { 0x4c, XK_l },  // Qt::Key_L
    { 0x4d, XK_m },  // Qt::Key_M
    { 0x4e, XK_n },  // Qt::Key_N
    { 0x4f, XK_o },  // Qt::Key_O
    { 0x50, XK_p },  // Qt::Key_P
    { 0x51, XK_q },  // Qt::Key_Q
    { 0x52, XK_r },  // Qt::Key_R
    { 0x53, XK_s },  // Qt::Key_S
    { 0x54, XK_t },  // Qt::Key_T
    { 0x55, XK_u },  // Qt::Key_U
    { 0x56, XK_v },  // Qt::Key_V
    { 0x57, XK_w },  // Qt::Key_W
    { 0x58, XK_x },  // Qt::Key_X
    { 0x59, XK_y },  // Qt::Key_Y
    { 0x5a, XK_z },  // Qt::Key_Z

    // 数字键 (0-9)
    { 0x29, XK_0 },  // Qt::Key_0
    { 0x30, XK_0 },
    { 0x31, XK_1 },  // Qt::Key_1
    { 0x21, XK_1 },
    { 0x32, XK_2 },  // Qt::Key_2
    { 0x40, XK_2 },
    { 0x33, XK_3 },  // Qt::Key_3
    { 0x23, XK_3 },
    { 0x34, XK_4 },  // Qt::Key_4
    { 0x24, XK_4 },
    { 0x35, XK_5 },  // Qt::Key_5
    { 0x25, XK_5 },
    { 0x36, XK_6 },  // Qt::Key_6
    { 0x5e, XK_6 },
    { 0x37, XK_7 },  // Qt::Key_7
    { 0x26, XK_7 },
    { 0x38, XK_8 },  // Qt::Key_8
    { 0x2a, XK_8 },
    { 0x39, XK_9 },  // Qt::Key_9
    { 0x28, XK_9 },

    // 符号键 (上档键未按下)
    { 0x20, XK_space },      // Qt::Key_Space
    { 0x2d, XK_minus },      // Qt::Key_Minus
    { 0x3d, XK_equal },      // Qt::Key_Equal
    { 0x5b, XK_bracketleft },  // Qt::Key_BracketLeft
    { 0x5d, XK_bracketright }, // Qt::Key_BracketRight
    { 0x5c, XK_backslash },    // Qt::Key_Backslash
    { 0x3b, XK_semicolon },    // Qt::Key_Semicolon
    { 0x27, XK_apostrophe },   // Qt::Key_Apostrophe
    { 0x2c, XK_comma },        // Qt::Key_Comma
    { 0x2e, XK_period },       // Qt::Key_Period
    { 0x2f, XK_slash },        // Qt::Key_Slash
    { 0x60, XK_grave },        // Qt::Key_QuoteLeft
    { 0x7e, XK_grave },
    // 功能键
    { 0x01000004, XK_Return },       // Qt::Key_Enter/Return
    { 0x01000005, XK_Return },       // Qt::Key_Enter (小键盘)
    { 0x01000003, XK_BackSpace },    // Qt::Key_Backspace
    { 0x01000001, XK_Tab },          // Qt::Key_Tab
    { 0x00000000, XK_Clear },        // Qt::Key_Clear
    { 0x01000000, XK_Escape },       // Qt::Key_Escape
    { 0x00000000, XK_Mode_switch },  // Qt::Key_Mode_switch
    { 0x01000020, XK_Shift_L },      // Qt::Key_Shift (左)
    { 0x01000020, XK_Shift_R },      // Qt::Key_Shift (右)
    { 0x01000021, XK_Control_L },    // Qt::Key_Control (左)
    { 0x01000021, XK_Control_R },    // Qt::Key_Control (右)
    { 0x00000000, XK_Meta_L },       // Qt::Key_Meta (左)
    { 0x00000000, XK_Meta_R },       // Qt::Key_Meta (右)
    { 0x01000023, XK_Alt_L },        // Qt::Key_Alt (左)
    { 0x01000023, XK_Alt_R },        // Qt::Key_Alt (右)
    { 0x01000024, XK_Caps_Lock },    // Qt::Key_CapsLock
    { 0x01000025, XK_Num_Lock },     // Qt::Key_NumLock
    { 0x0100002a, XK_Scroll_Lock },  // Qt::Key_ScrollLock
    { 0x01000030, XK_F1 },           // Qt::Key_F1
    { 0x01000031, XK_F2 },           // Qt::Key_F2
    { 0x01000032, XK_F3 },           // Qt::Key_F3
    { 0x01000033, XK_F4 },           // Qt::Key_F4
    { 0x01000034, XK_F5 },           // Qt::Key_F5
    { 0x01000035, XK_F6 },           // Qt::Key_F6
    { 0x01000036, XK_F7 },           // Qt::Key_F7
    { 0x01000037, XK_F8 },           // Qt::Key_F8
    { 0x01000038, XK_F9 },           // Qt::Key_F9
    { 0x01000039, XK_F10 },          // Qt::Key_F10
    { 0x0100003a, XK_F11 },          // Qt::Key_F11
    { 0x0100003b, XK_F12 },          // Qt::Key_F12
    { 0x0100003c, XK_F13 },          // Qt::Key_F13
    { 0x0100003d, XK_F14 },          // Qt::Key_F14
    { 0x0100003e, XK_F15 },          // Qt::Key_F15
    { 0x0100003f, XK_F16 },          // Qt::Key_F16
    { 0x01000040, XK_F17 },          // Qt::Key_F17
    { 0x01000041, XK_F18 },          // Qt::Key_F18
    { 0x01000042, XK_F19 },          // Qt::Key_F19
    { 0x01000043, XK_F20 },          // Qt::Key_F20
    { 0x01000044, XK_F21 },          // Qt::Key_F21
    { 0x01000045, XK_F22 },          // Qt::Key_F22
    { 0x01000046, XK_F23 },          // Qt::Key_F23
    { 0x01000047, XK_F24 },          // Qt::Key_F24
    { 0x01000048, XK_Menu },         // Qt::Key_Menu
    { 0x01000051, XK_Help },         // Qt::Key_Help
    { 0x01000016, XK_Prior },        // Qt::Key_PageUp
    { 0x01000017, XK_Next },         // Qt::Key_PageDown
    { 0x01000010, XK_Home },         // Qt::Key_Home
    { 0x01000011, XK_End },          // Qt::Key_End
    { 0x01000012, XK_Left },         // Qt::Key_Left
    { 0x01000013, XK_Up },           // Qt::Key_Up
    { 0x01000014, XK_Right },        // Qt::Key_Right
    { 0x01000015, XK_Down },         // Qt::Key_Down
    { 0x01000060, XK_Print },        // Qt::Key_Print
    { 0x01000006, XK_Insert },       // Qt::Key_Insert
    { 0x01000007, XK_Delete },       // Qt::Key_Delete
    { 0x01000063, XK_Pause },        // Qt::Key_Pause
    { 0x01000064, XK_Sys_Req },      // Qt::Key_SysReq

    // 小键盘数字键
    { 0x01000070, XK_KP_0 },        // Qt::Key_0 (小键盘)
    { 0x01000071, XK_KP_1 },        // Qt::Key_1 (小键盘)
    { 0x01000072, XK_KP_2 },        // Qt::Key_2 (小键盘)
    { 0x01000073, XK_KP_3 },        // Qt::Key_3 (小键盘)
    { 0x01000074, XK_KP_4 },        // Qt::Key_4 (小键盘)
    { 0x01000075, XK_KP_5 },        // Qt::Key_5 (小键盘)
    { 0x01000076, XK_KP_6 },        // Qt::Key_6 (小键盘)
    { 0x01000077, XK_KP_7 },        // Qt::Key_7 (小键盘)
    { 0x01000078, XK_KP_8 },        // Qt::Key_8 (小键盘)
    { 0x01000079, XK_KP_9 },        // Qt::Key_9 (小键盘)
    { 0x2b, XK_KP_Add },      // Qt::Key_Plus (小键盘)
    { 0x0100007b, XK_KP_Subtract }, // Qt::Key_Minus (小键盘)
    { 0x2a, XK_KP_Multiply }, // Qt::Key_Asterisk (小键盘)
    { 0x0100007d, XK_KP_Divide },   // Qt::Key_Slash (小键盘)
    { 0x0100007e, XK_KP_Enter },    // Qt::Key_Enter (小键盘)
    { 0x0100007f, XK_KP_Equal },    // Qt::Key_Equal (小键盘)
    { 0x01000080, XK_KP_Separator },// Qt::Key_Separator (小键盘)
    { 0x01000081, XK_KP_Decimal },  // Qt::Key_Period (小键盘)

    // 其他特殊键
    { 0x01001103, XK_ISO_Left_Tab }, // Qt::Key_Tab (Shift+Tab)
    { 0x01001120, XK_Multi_key },    // Qt::Key_Multi_key
    { 0x01001137, XK_Super_L },      // Qt::Key_Super_L (左Win键)
    { 0x01001138, XK_Super_R },      // Qt::Key_Super_R (右Win键)
    { 0x0100117e, XK_Hyper_L },      // Qt::Key_Hyper_L
    { 0x0100117f, XK_Hyper_R },      // Qt::Key_Hyper_R

    { 0x5f, XK_underscore},    //_
    { 0x7b, XK_braceleft },   // {
    { 0x7d, XK_braceright },  // }
    { 0x7c, XK_bar },         // |
    { 0x3a, XK_colon },       // :
    { 0x22, XK_quotedbl },    // "
    { 0x3f, XK_question },    // ?
    { 0x3c, XK_less },      // <
    { 0x3e, XK_greater },   // >
};

X11Driver::X11Driver()
{
    display = XOpenDisplay(NULL);
}

X11Driver::~X11Driver()
{
    if(display)
    {
        XCloseDisplay(display);
        display = nullptr;
    }
}
void X11Driver::syncKeyboard(const KeyEventPacket& packet)
{
    if (!display) {
        std::cerr << "Failed to open X display" << std::endl;
        return;
    }

    auto it = qtKeyToX11KeySym.find(packet.key);
    if (it == qtKeyToX11KeySym.end()) {
        std::cerr << "Unknown Qt Key: " << packet.key << std::endl;
        return;
    }

    KeySym keysym = it->second;
    KeyCode keycode = XKeysymToKeycode(display, keysym);

    if (keycode == 0) {
        std::cerr << "Failed to convert KeySym to KeyCode" << std::endl;
        return;
    }

    Window root = DefaultRootWindow(display);

    if(keycode == 94)//if key is less, need to disable shift, 0x3c->94 
    {
        XTestFakeKeyEvent(display, 50, false, CurrentTime);//0x1000020->50
    }
    XTestFakeKeyEvent(display, keycode, packet.is_pressed, CurrentTime);
    XFlush(display);

}

void X11Driver::syncMouseEvent(const MouseEventPacket& packet) {
    if (!display) return;

    switch (packet.type) {
        case MouseEventType::Move:
            // 移动鼠标
            XTestFakeMotionEvent(display, -1, packet.x, packet.y, CurrentTime);
            break;

        case MouseEventType::Press:
        case MouseEventType::Release: {
            // 按下或释放按键
            unsigned int button = 0;
            switch (packet.button) {
                case MouseButton::LeftButton: button = Button1; break;
                case MouseButton::MiddleButton: button = Button2; break;
                case MouseButton::RightButton: button = Button3; break;
                case MouseButton::NoButton: 
                if(packet.wheelDelta == 0)
                    break;
                button = packet.wheelDelta > 0 ? Button4 : Button5; 
                break;
                default: break;
            }
            if (button != 0) {
                XTestFakeButtonEvent(display, button, packet.type == MouseEventType::Press, CurrentTime);
            }
            break;
        }

        case MouseEventType::Wheel: {
            // 滚轮滚动，这里 wheelDelta > 0 上滚，<0 下滚
            int clicks = abs(packet.wheelDelta) / 120; // 1滚动 = 120单位（兼容Windows、Qt）
            unsigned int button = (packet.wheelDelta > 0) ? Button4 : Button5;
            for (int i = 0; i < clicks; ++i) {
                XTestFakeButtonEvent(display, button, True, CurrentTime);
                XTestFakeButtonEvent(display, button, False, CurrentTime);
            }
            break;
        }

        default:
            break;
    }
    XFlush(display);
}