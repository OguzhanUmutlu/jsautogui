#include "main.h"

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
bool f_mouse_scroll(int x, int y);
bool f_press_key(bool is_ascii, int got);
bool f_key_down(bool is_ascii, int got);
bool f_key_up(bool is_ascii, int got);
int f_show_message_box(char *textBuf, char *captionBuf, int flags);
int f_show_prompt();