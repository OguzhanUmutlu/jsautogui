#pragma once
#include <cstdint>

struct ScreenPoint {
    bool invalid;
    long x;
    long y;

    constexpr explicit ScreenPoint(long x = 0, long y = 0, bool invalid = false) : invalid(invalid), x(x), y(y) {
    }
};

enum class KeyPressMode {
    ASCII,
    UNICODE,
    SPECIAL
};

/*
const modifiers: string[] = [
    "accept", "add", "alt", "altleft", "altright", "apps", "backspace",
    "browserback", "browserfavorites", "browserforward", "browserhome",
    "browserrefresh", "browsersearch", "browserstop", "capslock", "clear",
    "convert", "ctrl", "ctrlleft", "ctrlright", "decimal", "del", "delete",
    "divide", "down", "end", "enter", "esc", "escape", "execute", "f1", "f10",
    "f11", "f12", "f13", "f14", "f15", "f16", "f17", "f18", "f19", "f2", "f20",
    "f21", "f22", "f23", "f24", "f3", "f4", "f5", "f6", "f7", "f8", "f9",
    "final", "hanguel", "hangul", "hanja", "help", "home", "insert", "junja",
    "kana", "kanji", "launchapp1", "launchapp2", "launchmail",
    "launchmediaselect", "left", "modechange", "multiply", "nexttrack",
    "nonconvert", "num0", "num1", "num2", "num3", "num4", "num5", "num6",
    "num7", "num8", "num9", "numlock", "pagedown", "pageup", "pause", "pgdn",
    "pgup", "playpause", "prevtrack", "print", "printscreen", "prntscrn",
    "prtsc", "prtscr", "return", "right", "scrolllock", "select", "separator",
    "shift", "shiftleft", "shiftright", "sleep", "space", "stop", "subtract", "tab",
    "up", "volumedown", "volumemute", "volumeup", "win", "winleft", "winright", "yen",
    "command", "option", "optionleft", "optionright"
] as const;
 */
enum class SpecialKeys {
    ACCEPT, ADD, ALT, ALTLEFT, ALTRIGHT, APPS, BACKSPACE,
    BROWSERBACK, BROWSERFAVORITES, BROWSERFORWARD, BROWSERHOME,
    BROWSERREFRESH, BROWSERSEARCH, BROWSERSTOP, CAPSLOCK, CLEAR,
    CONVERT, CTRL, CTRLLEFT, CTRLRIGHT, DECIMAL, DEL, DELETE,
    DIVIDE, DOWN, END, ENTER, ESC, ESCAPE, EXECUTE, F1, F10,
    F11, F12, F13, F14, F15, F16, F17, F18, F19, F2, F20,
    F21, F22, F23, F24, F3, F4, F5, F6, F7, F8, F9,
    FINAL, HANGUEL, HANGUL, HANJA, HELP, HOME, INSERT, JUNJA,
    KANA, KANJI, LAUNCHAPP1, LAUNCHAPP2, LAUNCHMAIL,
    LAUNCHMEDIASELECT, LEFT, MODECHANGE, MULTIPLY, NEXTTRACK,
    NONCONVERT, NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6,
    NUM7, NUM8, NUM9, NUMLOCK, PAGEDOWN, PAGEUP, PAUSE, PGDN,
    PGUP, PLAYPAUSE, PREVTRACK, PRINT, PRINTSCREEN, PRNTSCRN,
    PRTSC, PRTSCR, RETURN, RIGHT, SCROLLLOCK, SELECT, SEPARATOR,
    SHIFT, SHIFTLEFT, SHIFTRIGHT, SLEEP, SPACE, STOP, SUBTRACT, TAB,
    UP, VOLUMEDOWN, VOLUMEMUTE, VOLUMEUP, WIN, WINLEFT, WINRIGHT, YEN,
    COMMAND, OPTION, OPTIONLEFT, OPTIONRIGHT
};

struct KeyPressInfo {
    bool down;
    bool up;
    KeyPressMode mode;
    uint16_t key;
};

ScreenPoint f_get_screen_size();

ScreenPoint f_get_cursor_position();

bool f_set_cursor_position(int x, int y);

bool f_is_mouse_left_down();

bool f_is_mouse_right_down();

bool f_is_mouse_middle_down();

bool f_click_left();

bool f_click_right();

bool f_click_middle();

bool f_mouse_left_down();

bool f_mouse_right_down();

bool f_mouse_middle_down();

bool f_mouse_left_up();

bool f_mouse_right_up();

bool f_mouse_middle_up();

bool f_is_mouse_swapped();

bool f_mouse_scroll(unsigned long x, unsigned long y);

bool f_keys_press(const KeyPressInfo* ch, std::size_t amount);
