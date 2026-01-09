#ifdef __linux__

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#include <string>
#include <thread>
#include <vector>

#include "../utils.h"

#define XK_accept 0
#define XK_Favorites 0
#define XK_Forward 0
#define XK_HomePage 0
#define XK_Refresh 0
#define XK_Search 0
#define XK_Stop 0
#define XK_Launch0 0
#define XK_Launch1 0
#define XK_LaunchMail 0
#define XK_LaunchMusic 0
#define XK_AudioNext 0
#define XK_AudioPlay 0
#define XK_AudioPrev 0
#define XK_Sleep 0
#define XK_AudioStop 0
#define XK_AudioLowerVolume 0
#define XK_AudioMute 0
#define XK_AudioRaiseVolume 0
#define XK_Yen 0

static const KeySym MODIFIERS[] = {
    // accept, add, alt, altleft, altright, apps, backspace,
    XK_accept, XK_KP_Add, XK_Alt_L, XK_Alt_L, XK_Alt_R, XK_Menu, XK_BackSpace,
    // browserback, browserfavorites, browserforward, browserhome,
    0, XK_Favorites, XK_Forward, XK_HomePage,
    // browserrefresh, browsersearch, browserstop, capslock, clear,
    XK_Refresh, XK_Search, XK_Stop, XK_Caps_Lock, XK_Clear,
    // convert, ctrl, ctrlleft, ctrlright, decimal, del, delete,
    0, XK_Control_L, XK_Control_L, XK_Control_R, XK_KP_Decimal, XK_Delete, XK_Delete,
    // divide, down, end, enter, esc, escape, execute, f1, f10,
    XK_KP_Divide, XK_Down, XK_End, XK_Return, XK_Escape, XK_Escape, XK_Execute, XK_F1, XK_F10,
    // f11, f12, f13, f14, f15, f16, f17, f18, f19, f2, f20,
    XK_F11, XK_F12, XK_F13, XK_F14, XK_F15, XK_F16, XK_F17, XK_F18, XK_F19, XK_F2, XK_F20,
    // f21, f22, f23, f24, f3, f4, f5, f6, f7, f8, f9,
    XK_F21, XK_F22, XK_F23, XK_F24, XK_F3, XK_F4, XK_F5, XK_F6, XK_F7, XK_F8, XK_F9,
    // final, hanguel, hangul, hanja, help, home, insert, junja,
    0, XK_Hangul, XK_Hangul, XK_Hangul_Hanja, XK_Help, XK_Home, XK_Insert, 0,
    // kana, kanji, launchapp1, launchapp2, launchmail,
    XK_Kana_Lock, XK_Kanji, XK_Launch0, XK_Launch1, XK_LaunchMail,
    // launchmediaselect, left, modechange, multiply, nexttrack,
    XK_LaunchMusic, XK_Left, 0, XK_KP_Multiply, XK_AudioNext,
    // nonconvert, num0, num1, num2, num3, num4, num5, num6,
    0, XK_KP_0, XK_KP_1, XK_KP_2, XK_KP_3, XK_KP_4, XK_KP_5, XK_KP_6,
    // num7, num8, num9, numlock, pagedown, pageup, pause, pgdn,
    XK_KP_7, XK_KP_8, XK_KP_9, XK_Num_Lock, XK_Page_Down, XK_Page_Up, XK_Pause, XK_Page_Down,
    // pgup, playpause, prevtrack, print, printscreen, prntscrn,
    XK_Page_Up, XK_AudioPlay, XK_AudioPrev, XK_Print, XK_Print, XK_Print,
    // prtsc, prtscr, return, right, scrolllock, select, separator,
    XK_Print, XK_Print, XK_Return, XK_Right, XK_Scroll_Lock, 0, XK_KP_Separator,
    // shift, shiftleft, shiftright, sleep, space, stop, subtract, tab,
    XK_Shift_L, XK_Shift_L, XK_Shift_R, XK_Sleep, XK_space, XK_AudioStop, XK_KP_Subtract, XK_Tab,
    // up, volumedown, volumemute, volumeup, win, winleft, winright, yen,
    XK_Up, XK_AudioLowerVolume, XK_AudioMute, XK_AudioRaiseVolume, XK_Super_L, XK_Super_L, XK_Super_R, XK_Yen,
    // command, option, optionleft, optionright
    XK_Meta_L, XK_Alt_L, XK_Alt_L, XK_Alt_R
};

#define GetDisplay(ret)                       \
    Display *display = XOpenDisplay(nullptr); \
    if (display == nullptr)                   \
    {                                         \
        return (ret);                         \
    }

ScreenPoint f_get_screen_size() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) return ScreenPoint(0, 0, true);
    int screen_num = DefaultScreen(display);
    int width = DisplayWidth(display, screen_num);
    int height = DisplayHeight(display, screen_num);
    XCloseDisplay(display);
    return ScreenPoint(width, height);
}

ScreenPoint f_get_cursor_position() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) return ScreenPoint(0, 0, true);
    Window rootWindow = DefaultRootWindow(display);
    XEvent event;
    XQueryPointer(display, rootWindow, &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    XFlush(display);
    XCloseDisplay(display);
    return ScreenPoint(event.xbutton.x_root, event.xbutton.y_root);
}

bool f_set_cursor_position(int x, int y) {
    Display* display = XOpenDisplay(nullptr);
    if (!display) return false;
    XWarpPointer(display, None, DefaultRootWindow(display), 0, 0, 0, 0, x, y);
    XFlush(display);
    XCloseDisplay(display);
    return true;
}

#define IsDownMacro(check)                                                                                                          \
    GetDisplay(false);                                                                                                              \
    Window root = DefaultRootWindow(display);                                                                                       \
    XEvent event;                                                                                                                   \
    XGrabPointer(display, root, False, ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime); \
    XMaskEvent(display, ButtonPressMask, &event);                                                                                   \
    if (event.type == ButtonPress && (check)) {                                                                                     \
        XUngrabPointer(display, CurrentTime);                                                                                       \
        XCloseDisplay(display);                                                                                                     \
        return true;                                                                                                                \
    }                                                                                                                               \
    XUngrabPointer(display, CurrentTime);                                                                                           \
    XCloseDisplay(display);                                                                                                         \
    return false;

bool f_is_mouse_left_down() {
    IsDownMacro(event.xbutton.button == Button1);
}

bool f_is_mouse_right_down() {
    IsDownMacro(event.xbutton.button == Button3);
}

bool f_is_mouse_middle_down() {
    IsDownMacro(event.xbutton.button == Button2);
}

#define ClickMacro(btn)                                       \
    GetDisplay(false);                                        \
    XTestFakeButtonEvent(display, (btn), True, CurrentTime);  \
    XFlush(display);                                          \
    usleep(10000); /* Required for linux */                   \
    XTestFakeButtonEvent(display, (btn), False, CurrentTime); \
    XFlush(display);                                          \
    XCloseDisplay(display);                                   \
    return true;

bool f_click_left() {
    ClickMacro(Button1);
}

bool f_click_right() {
    ClickMacro(Button3);
}

bool f_click_middle() {
    ClickMacro(Button2);
}

#define DownUpMacro(btn, type)                                 \
    GetDisplay(false);                                         \
    XTestFakeButtonEvent(display, (btn), (type), CurrentTime); \
    XFlush(display);                                           \
    XCloseDisplay(display);                                    \
    return true;

bool f_mouse_left_down() {
    DownUpMacro(Button1, True);
}

bool f_mouse_right_down() {
    DownUpMacro(Button3, True);
}

bool f_mouse_middle_down() {
    DownUpMacro(Button2, True);
}

bool f_mouse_left_up() {
    DownUpMacro(Button1, False);
}

bool f_mouse_right_up() {
    DownUpMacro(Button3, False);
}

bool f_mouse_middle_up() {
    DownUpMacro(Button2, False);
}

bool f_is_mouse_swapped() {
    Display* display = XOpenDisplay(nullptr);
    if (!display) return false;

    unsigned char map[5];
    int nmap = XGetPointerMapping(display, map, 5);
    XCloseDisplay(display);

    if (nmap >= 1 && map[0] != 1) {
        return true;
    }
    return false;
}

bool f_mouse_scroll(long x, long y) {
    GetDisplay(false);

    if (y > 0) {
        for (long i = 0; i < y; ++i) {
            XTestFakeButtonEvent(display, Button4, True, CurrentTime);
            XFlush(display);
            usleep(10000);
            XTestFakeButtonEvent(display, Button4, False, CurrentTime);
            XFlush(display);
        }
    } else if (y < 0) {
        long absY = -y;
        for (long i = 0; i < absY; ++i) {
            XTestFakeButtonEvent(display, Button5, True, CurrentTime);
            XFlush(display);
            usleep(10000);
            XTestFakeButtonEvent(display, Button5, False, CurrentTime);
            XFlush(display);
        }
    }

    if (x > 0) {
        for (long i = 0; i < x; ++i) {
            XTestFakeButtonEvent(display, 7, True, CurrentTime);
            XFlush(display);
            usleep(10000);
            XTestFakeButtonEvent(display, 7, False, CurrentTime);
            XFlush(display);
        }
    } else if (x < 0) {
        long absX = -x;
        for (long i = 0; i < absX; ++i) {
            XTestFakeButtonEvent(display, 6, True, CurrentTime);
            XFlush(display);
            usleep(10000);
            XTestFakeButtonEvent(display, 6, False, CurrentTime);
            XFlush(display);
        }
    }

    XCloseDisplay(display);
    return true;
}

bool f_keys_press(const KeyPressInfo* ch, size_t amount) {
    Display* disp = XOpenDisplay(nullptr);
    if (!disp) return false;

    int ev, er;
    if (!XTestQueryExtension(disp, &ev, &er, &ev, &er)) {
        XCloseDisplay(disp);
        return false;
    }

    for (size_t i = 0; i < amount; ++i) {
        const auto [down, up, mode, key] = ch[i];
        KeySym ks = NoSymbol;

        switch (mode) {
        case KeyPressMode::ASCII:
            ks = XStringToKeysym(std::string(1, static_cast<char>(key)).c_str());
            break;
        case KeyPressMode::UNICODE:
            if (key < 0x100) {
                ks = key;
            } else {
                ks = 0x01000000 | key;
            }
            break;
        case KeyPressMode::SPECIAL:
            if (key < std::size(MODIFIERS)) ks = MODIFIERS[key];
            break;
        }

        if (ks == NoSymbol) {
            continue;
        }

        KeyCode kc = XKeysymToKeycode(disp, ks);
        if (kc == 0) continue;

        if (down) XTestFakeKeyEvent(disp, kc, True, 0);
        if (up) XTestFakeKeyEvent(disp, kc, False, 0);
    }

    XFlush(disp);
    XCloseDisplay(disp);
    return true;
}

#endif
