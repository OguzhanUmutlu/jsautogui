#ifdef _WIN32
#include "utils.h"

using namespace std;

#include <Windows.h>
#include <iostream>
#include <optional>
#include "../main.h"

#define IDD_CUSTOM_DIALOG 101
#define IDC_EDIT 102

const WORD MODIFIERS[] = {
    VK_ACCEPT, VK_ADD, VK_MENU, VK_LMENU, VK_RMENU, VK_APPS, VK_BACK, VK_BROWSER_BACK, VK_BROWSER_FAVORITES,
    VK_BROWSER_FORWARD, VK_BROWSER_HOME, VK_BROWSER_REFRESH, VK_BROWSER_SEARCH, VK_BROWSER_STOP, VK_CAPITAL, VK_CLEAR,
    VK_CONVERT, VK_CONTROL, VK_LCONTROL, VK_RCONTROL, VK_DECIMAL, VK_DELETE, VK_DELETE, VK_DIVIDE, VK_DOWN, VK_END,
    VK_RETURN, VK_ESCAPE, VK_ESCAPE, VK_EXECUTE, VK_F1, VK_F10, VK_F11, VK_F12, VK_F13, VK_F14, VK_F15, VK_F16, VK_F17,
    VK_F18, VK_F19, VK_F20, VK_F21, VK_F22, VK_F23, VK_F24, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_FINAL,
    VK_HANGUL, VK_HANGUL, VK_HANJA, VK_HELP, VK_HOME, VK_INSERT, VK_JUNJA, VK_KANA, VK_KANJI, VK_LAUNCH_APP1,
    VK_LAUNCH_APP2, VK_LAUNCH_MAIL, VK_LAUNCH_MEDIA_SELECT, VK_LEFT, VK_MODECHANGE, VK_MULTIPLY, VK_MEDIA_NEXT_TRACK,
    VK_NONCONVERT, VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7,
    VK_NUMPAD8, VK_NUMPAD9, VK_NUMLOCK, VK_NEXT, VK_PRIOR, VK_PAUSE, VK_NEXT, VK_PRIOR, VK_MEDIA_PLAY_PAUSE,
    VK_MEDIA_PREV_TRACK, VK_PRINT, VK_SNAPSHOT, VK_SNAPSHOT, VK_SNAPSHOT, VK_SNAPSHOT, VK_RETURN, VK_RIGHT, VK_SCROLL,
    VK_SELECT, VK_SEPARATOR, VK_SHIFT, VK_LSHIFT, VK_RSHIFT, VK_SLEEP, VK_SPACE, VK_MEDIA_STOP, VK_SUBTRACT, VK_TAB,
    VK_UP, VK_VOLUME_DOWN, VK_VOLUME_MUTE, VK_VOLUME_UP, VK_LWIN, VK_LWIN, VK_RWIN, VK_OEM_5, VK_LWIN, VK_MENU,
    VK_LMENU, VK_RMENU
};

optional<Point> f_get_screen_size() {
    return make_optional(Point{GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)});
}

optional<Point> f_get_cursor_position() {
    POINT point;
    if (!GetCursorPos(&point)) return nullopt;
    return make_optional(Point(point.x, point.y));
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
    INPUT input = {.type = INPUT_MOUSE, .mi = {.dwFlags = flags}};
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

bool f_mouse_scroll(unsigned long x, unsigned long y) {
    if (x == 0 && y == 0) return true;
    INPUT inputs[2];
    unsigned int i = 0;

    if (x != 0) inputs[i++] = {.type = INPUT_MOUSE, .mi = {.mouseData = x, .dwFlags = MOUSEEVENTF_HWHEEL}};
    if (y != 0) inputs[i++] = {.type = INPUT_MOUSE, .mi = {.mouseData = y, .dwFlags = MOUSEEVENTF_WHEEL}};

    return SendInput(i, inputs, sizeof(INPUT)) == i;
}

bool f_keys_press(const KeyPressInfo *ch, size_t amount) {
    auto inputs = new INPUT[amount * 8]; // A single key can possibly trigger 7 more

    size_t j = 0;

    for (size_t i = 0; i < amount; i++) {
        switch (auto [down,up, mode, key] = ch[i]; mode) {
            case KeyPressMode::ASCII: {
                SHORT scan = VkKeyScanA(static_cast<char>(key));
                if (scan == -1) continue;
                BYTE vk = LOBYTE(scan);
                BYTE state = HIBYTE(scan);
                if (down) {
                    if (state & 1) inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = VK_SHIFT}};
                    if (state & 2) inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = VK_CONTROL}};
                    if (state & 4) inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = VK_MENU}};
                    inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = vk}};
                }
                if (up) {
                    inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = vk, .dwFlags = KEYEVENTF_KEYUP}};
                    constexpr DWORD uf = KEYEVENTF_KEYUP;
                    if (state & 4) inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = VK_MENU, .dwFlags = uf}};
                    if (state & 2) inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = VK_CONTROL, .dwFlags = uf}};
                    if (state & 1) inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = VK_SHIFT, .dwFlags = uf}};
                }
                break;
            }
            case KeyPressMode::UNICODE: {
                if (down) {
                    inputs[j++] = {
                        .type = INPUT_KEYBOARD,
                        .ki = {.wVk = 0, .wScan = key, .dwFlags = KEYEVENTF_UNICODE}
                    };
                }
                if (up) {
                    inputs[j++] = {
                        .type = INPUT_KEYBOARD,
                        .ki = {.wVk = 0, .wScan = key, .dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP}
                    };
                }
                break;
            }
            case KeyPressMode::SPECIAL: {
                if (key >= size(MODIFIERS)) continue;
                if (down) {
                    inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = MODIFIERS[key]}};
                }
                if (up) {
                    inputs[j++] = {.type = INPUT_KEYBOARD, .ki = {.wVk = MODIFIERS[key], .dwFlags = KEYEVENTF_KEYUP}};
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
