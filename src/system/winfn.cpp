#ifdef _WIN32
#include "../utils.h"

#include <Windows.h>
#include <iostream>

#define IDD_CUSTOM_DIALOG 101
#define IDC_EDIT 102

const WORD MODIFIERS[] = {
    // accept, add, alt, altleft, altright, apps, backspace,
    VK_ACCEPT, VK_ADD, VK_MENU, VK_LMENU, VK_RMENU, VK_APPS, VK_BACK,
    // browserback, browserfavorites, browserforward, browserhome,
    VK_BROWSER_BACK, VK_BROWSER_FAVORITES, VK_BROWSER_FORWARD, VK_BROWSER_HOME,
    // browserrefresh, browsersearch, browserstop, capslock, clear,
    VK_BROWSER_REFRESH, VK_BROWSER_SEARCH, VK_BROWSER_STOP, VK_CAPITAL, VK_CLEAR,
    // convert, ctrl, ctrlleft, ctrlright, decimal, del, delete,
    VK_CONVERT, VK_CONTROL, VK_LCONTROL, VK_RCONTROL, VK_DECIMAL, VK_DELETE, VK_DELETE,
    // divide, down, end, enter, esc, escape, execute, f1, f10,
    VK_DIVIDE, VK_DOWN, VK_END, VK_RETURN, VK_ESCAPE, VK_ESCAPE, VK_EXECUTE, VK_F1, VK_F10,
    // f11, f12, f13, f14, f15, f16, f17, f18, f19, f2, f20,
    VK_F11, VK_F12, VK_F13, VK_F14, VK_F15, VK_F16, VK_F17, VK_F18, VK_F19, VK_F2, VK_F20,
    // f21, f22, f23, f24, f3, f4, f5, f6, f7, f8, f9,
    VK_F21, VK_F22, VK_F23, VK_F24, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9,
    // final, hanguel, hangul, hanja, help, home, insert, junja,
    VK_FINAL, VK_HANGUL, VK_HANGUL, VK_HANJA, VK_HELP, VK_HOME, VK_INSERT, VK_JUNJA,
    // kana, kanji, launchapp1, launchapp2, launchmail,
    VK_KANA, VK_KANJI, VK_LAUNCH_APP1, VK_LAUNCH_APP2, VK_LAUNCH_MAIL,
    // launchmediaselect, left, modechange, multiply, nexttrack,
    VK_LAUNCH_MEDIA_SELECT, VK_LEFT, VK_MODECHANGE, VK_MULTIPLY, VK_MEDIA_NEXT_TRACK,
    // nonconvert, num0, num1, num2, num3, num4, num5, num6,
    VK_NONCONVERT, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,
    // num7, num8, num9, numlock, pagedown, pageup, pause, pgdn,
    VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9, VK_NUMLOCK, VK_NEXT, VK_PRIOR, VK_PAUSE, VK_NEXT,
    // pgup, playpause, prevtrack, print, printscreen, prntscrn,
    VK_PRIOR, VK_MEDIA_PLAY_PAUSE, VK_MEDIA_PREV_TRACK, VK_PRINT, VK_SNAPSHOT, VK_SNAPSHOT,
    // prtsc, prtscr, return, right, scrolllock, select, separator,
    VK_SNAPSHOT, VK_SNAPSHOT, VK_RETURN, VK_RIGHT, VK_SCROLL, VK_SELECT, VK_SEPARATOR,
    // shift, shiftleft, shiftright, sleep, space, stop, subtract, tab,
    VK_SHIFT, VK_LSHIFT, VK_RSHIFT, VK_SLEEP, VK_SPACE, VK_MEDIA_STOP, VK_SUBTRACT, VK_TAB,
    // up, volumedown, volumemute, volumeup, win, winleft, winright, yen,
    VK_UP, VK_VOLUME_DOWN, VK_VOLUME_MUTE, VK_VOLUME_UP, VK_LWIN, VK_LWIN, VK_RWIN, VK_OEM_5,
    // command, option, optionleft, optionright
    VK_LWIN, VK_MENU, VK_LMENU, VK_RMENU
};

ScreenPoint f_get_screen_size() {
    return ScreenPoint(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
}

ScreenPoint f_get_cursor_position() {
    POINT point;
    if (!GetCursorPos(&point)) return ScreenPoint(0, 0, true);
    return ScreenPoint(point.x, point.y);
}

bool f_set_cursor_position(int x, int y) {
    return SetCursorPos(x, y);
}

bool f_is_mouse_left_down() {
    return GetAsyncKeyState(VK_LBUTTON) & 0x8000;
}

bool f_is_mouse_right_down() {
    return GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}

bool f_is_mouse_middle_down() {
    return GetAsyncKeyState(VK_MBUTTON) & 0x8000;
}

inline bool send_mouse_event(DWORD flags) {
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = flags;
    return SendInput(1, &input, sizeof(INPUT)) == 1;
}

bool f_click_left() {
    return send_mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
}

bool f_click_right() {
    return send_mouse_event(MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);
}

bool f_click_middle() {
    return send_mouse_event(MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP);
}

bool f_mouse_left_down() {
    return send_mouse_event(MOUSEEVENTF_LEFTDOWN);
}

bool f_mouse_right_down() {
    return send_mouse_event(MOUSEEVENTF_RIGHTDOWN);
}

bool f_mouse_middle_down() {
    return send_mouse_event(MOUSEEVENTF_MIDDLEDOWN);
}

bool f_mouse_left_up() {
    return send_mouse_event(MOUSEEVENTF_LEFTUP);
}

bool f_mouse_right_up() {
    return send_mouse_event(MOUSEEVENTF_RIGHTUP);
}

bool f_mouse_middle_up() {
    return send_mouse_event(MOUSEEVENTF_MIDDLEUP);
}

bool f_is_mouse_swapped() {
    return GetSystemMetrics(SM_SWAPBUTTON) != 0;
}

bool f_mouse_scroll(long x, long y) {
    if (x == 0 && y == 0) return true;
    INPUT inputs[2];
    unsigned int i = 0;

    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dx = 0;
    input.mi.dy = 0;
    input.mi.time = 0;
    input.mi.dwExtraInfo = 0;

    if (x != 0) {
        input.mi.mouseData = static_cast<DWORD>(x);
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        inputs[i++] = input;
    }
    if (y != 0) {
        input.mi.mouseData = static_cast<DWORD>(y);
        input.mi.dwFlags = MOUSEEVENTF_HWHEEL;
        inputs[i++] = input;
    }

    return SendInput(i, inputs, sizeof(INPUT)) == i;
}

bool f_keys_press(const KeyPressInfo* ch, size_t amount) {
    auto inputs = new INPUT[amount * 8]; // A single key can possibly trigger 7 more

    size_t j = 0;

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wScan = 0;
    input.ki.dwFlags = 0;
    input.ki.time = 0;
    input.ki.dwExtraInfo = 0;

    for (size_t i = 0; i < amount; i++) {
        auto [down,up, mode, key] = ch[i];
        switch (mode) {
        case KeyPressMode::ASCII: {
            SHORT scan = VkKeyScanA(static_cast<char>(key));
            if (scan == -1) continue;
            BYTE vk = LOBYTE(scan);
            BYTE state = HIBYTE(scan);
            input.ki.wScan = 0;
            if (down) {
                input.ki.dwFlags = 0;
                if (state & 1) {
                    input.ki.wVk = VK_SHIFT;
                    inputs[j++] = input;
                }
                if (state & 2) {
                    input.ki.wVk = VK_CONTROL;
                    inputs[j++] = input;
                }
                if (state & 4) {
                    input.ki.wVk = VK_MENU;
                    inputs[j++] = input;
                }
                input.ki.wVk = vk;
                inputs[j++] = input;
            }
            if (up) {
                input.ki.dwFlags = KEYEVENTF_KEYUP;
                input.ki.wVk = vk;
                if (state & 4) {
                    input.ki.wVk = VK_MENU;
                    inputs[j++] = input;
                }
                if (state & 2) {
                    input.ki.wVk = VK_CONTROL;
                    inputs[j++] = input;
                }
                if (state & 1) {
                    input.ki.wVk = VK_SHIFT;
                    inputs[j++] = input;
                }
            }
            break;
        }
        case KeyPressMode::UNICODE: {
            input.ki.wVk = 0;
            input.ki.wScan = key;
            if (down) {
                input.ki.dwFlags = KEYEVENTF_UNICODE;
                inputs[j++] = input;
            }
            if (up) {
                input.ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
                inputs[j++] = input;
            }
            break;
        }
        case KeyPressMode::SPECIAL: {
            if (key >= sizeof(MODIFIERS) / sizeof(WORD)) continue;
            input.ki.wScan = 0;
            if (down) {
                input.ki.wVk = MODIFIERS[key];
                input.ki.dwFlags = 0;
                inputs[j++] = input;
            }
            if (up) {
                input.ki.wVk = MODIFIERS[key];
                input.ki.dwFlags = KEYEVENTF_KEYUP;
                inputs[j++] = input;
            }
            break;
        }
        }
    }

    if (j == 0) {
        delete[] inputs;
        return true;
    }

    bool res = SendInput(j, inputs, sizeof(INPUT)) == j;
    delete[] inputs;
    return res;
}

#endif
