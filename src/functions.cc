#include <node_api.h>
#include <thread>
#include <iostream>
#include "os_include.h"

int32_t callPause = 0;

void do_call_pause()
{
    if (callPause > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(callPause / 1000));
    }
}

napi_value set_pause(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    prepare_args(env, info, argc, args);
    callPause = read_int32(env, args[0]);
    return nullptr;
}

napi_value get_screen_size(napi_env env, napi_callback_info info)
{
    do_call_pause();
    napi_value posObject = create_object(env);
    Point size = f_get_screen_size();
    set_object_key(env, posObject, "width", create_int32(env, size.x));
    set_object_key(env, posObject, "height", create_int32(env, size.y));
    return posObject;
}

napi_value set_mouse_pos_rel(napi_env env, napi_callback_info info)
{
    do_call_pause();
    Point cursorPos = f_get_cursor_position();
    if (cursorPos.x == -1)
    {
        return nullptr;
    }
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_set_cursor_position(
                                read_int32(env, args[0]) + cursorPos.x,
                                read_int32(env, args[1]) + cursorPos.y));
}

napi_value set_mouse_pos(napi_env env, napi_callback_info info)
{
    do_call_pause();
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_set_cursor_position(read_int32(env, args[0]), read_int32(env, args[1])));
}

napi_value set_mouse_x(napi_env env, napi_callback_info info)
{
    do_call_pause();
    Point cursorPos = f_get_cursor_position();
    if (cursorPos.x == -1)
    {
        return nullptr;
    }
    size_t argc = 1;
    napi_value args[1];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_set_cursor_position(read_int32(env, args[0]), cursorPos.y));
}

napi_value set_mouse_y(napi_env env, napi_callback_info info)
{
    do_call_pause();
    Point cursorPos = f_get_cursor_position();
    if (cursorPos.x == -1)
    {
        return nullptr;
    }
    size_t argc = 1;
    napi_value args[1];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_set_cursor_position(cursorPos.x, read_int32(env, args[0])));
}

napi_value get_mouse_pos(napi_env env, napi_callback_info info)
{
    do_call_pause();
    Point cursorPos = f_get_cursor_position();
    if (cursorPos.x == -1)
    {
        return nullptr;
    }
    napi_value posObject = create_object(env);
    set_object_key(env, posObject, "x", create_int32(env, cursorPos.x));
    set_object_key(env, posObject, "y", create_int32(env, cursorPos.y));
    return posObject;
}

napi_value mouse_is_left_down(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_is_mouse_left_down());
}

napi_value mouse_is_right_down(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_is_mouse_right_down());
}

napi_value mouse_is_middle_down(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_is_mouse_middle_down());
}

napi_value click_left(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_click_left());
}

napi_value click_right(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_click_right());
}

napi_value click_middle(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_click_middle());
}

napi_value mouse_left_down(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_mouse_left_down());
}

napi_value mouse_right_down(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_mouse_right_down());
}

napi_value mouse_middle_down(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_mouse_middle_down());
}

napi_value mouse_left_up(napi_env env, napi_callback_info info)
{
    do_call_pause();
    f_mouse_left_up();
    return create_bool(env, f_mouse_left_up());
}

napi_value mouse_right_up(napi_env env, napi_callback_info info)
{
    do_call_pause();
    f_mouse_right_up();
    return create_bool(env, f_mouse_right_up());
}

napi_value mouse_middle_up(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_mouse_middle_up());
}

napi_value is_mouse_swapped(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_bool(env, f_is_mouse_swapped());
}

napi_value mouse_scroll(napi_env env, napi_callback_info info)
{
    do_call_pause();
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_mouse_scroll(read_int32(env, args[0]), read_int32(env, args[1])));
}

napi_value press_key(napi_env env, napi_callback_info info)
{
    do_call_pause();
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    bool is_ascii = read_bool(env, args[0]);
    int32_t got = read_int32(env, args[1]);

    return create_bool(env, f_press_key(is_ascii, got));
}

napi_value key_down(napi_env env, napi_callback_info info)
{
    do_call_pause();
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    bool is_ascii = read_bool(env, args[0]);
    int32_t got = read_int32(env, args[1]);

    return create_bool(env, f_key_down(is_ascii, got));
}

napi_value key_up(napi_env env, napi_callback_info info)
{
    do_call_pause();
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    bool is_ascii = read_bool(env, args[0]);
    int32_t got = read_int32(env, args[1]);

    return create_bool(env, f_key_up(is_ascii, got));
}

napi_value show_message_box(napi_env env, napi_callback_info info)
{
    do_call_pause();
    size_t argc = 3;
    napi_value args[3];
    prepare_args(env, info, argc, args);

    char *textBuf = read_string(env, args[0]);
    char *captionBuf = read_string(env, args[1]);
    int64_t flags = read_int32(env, args[2]);

    int res = f_show_message_box(textBuf, captionBuf, flags);

    return create_int32(env, res);
}

napi_value show_prompt(napi_env env, napi_callback_info info)
{
    do_call_pause();
    return create_int32(env, f_show_prompt());
}