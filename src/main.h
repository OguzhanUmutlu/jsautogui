#include <node_api.h>

#define NC(env, call, err)
struct Point
{
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};
char *read_string(napi_env env, napi_value value);
int32_t read_int32(napi_env env, napi_value value);
int64_t read_int64(napi_env env, napi_value value);
bool read_bool(napi_env env, napi_value value);
napi_value create_int32(napi_env env, int32_t value);
napi_value create_int64(napi_env env, int64_t value);
napi_value create_bool(napi_env env, bool value);
napi_value create_object(napi_env env);
int set_object_key(napi_env env, napi_value obj, const char *name, napi_value value);
int prepare_args(napi_env env, napi_callback_info info, size_t &argc, napi_value *args);
napi_value init(napi_env env, napi_value exports);



// OS Dependent Functions
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