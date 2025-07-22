#pragma once
#include <cstdint>

struct Point {
    bool invalid;
    long x;
    long y;

    constexpr explicit Point(long x = 0, long y = 0, bool invalid = false) : invalid(invalid), x(x), y(y) {
    }
};

enum class KeyPressMode {
    ASCII,
    UNICODE,
    SPECIAL
};

struct KeyPressInfo {
    bool down;
    bool up;
    KeyPressMode mode;
    uint16_t key;
};

Point f_get_screen_size();

Point f_get_cursor_position();

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

bool f_keys_press(const KeyPressInfo *ch, size_t amount);
