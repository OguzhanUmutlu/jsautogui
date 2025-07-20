#pragma once

#include <node_api.h>

void do_call_pause();

napi_value set_pause(napi_env env, napi_callback_info info);

napi_value get_screen_size(napi_env env, napi_callback_info info);

napi_value set_mouse_pos_rel(napi_env env, napi_callback_info info);

napi_value set_mouse_pos(napi_env env, napi_callback_info info);

napi_value set_mouse_x(napi_env env, napi_callback_info info);

napi_value set_mouse_y(napi_env env, napi_callback_info info);

napi_value get_mouse_pos(napi_env env, napi_callback_info info);

napi_value mouse_is_left_down(napi_env env, napi_callback_info info);

napi_value mouse_is_right_down(napi_env env, napi_callback_info info);

napi_value mouse_is_middle_down(napi_env env, napi_callback_info info);

napi_value click_left(napi_env env, napi_callback_info info);

napi_value click_right(napi_env env, napi_callback_info info);

napi_value click_middle(napi_env env, napi_callback_info info);

napi_value mouse_left_down(napi_env env, napi_callback_info info);

napi_value mouse_right_down(napi_env env, napi_callback_info info);

napi_value mouse_middle_down(napi_env env, napi_callback_info info);

napi_value mouse_left_up(napi_env env, napi_callback_info info);

napi_value mouse_right_up(napi_env env, napi_callback_info info);

napi_value mouse_middle_up(napi_env env, napi_callback_info info);

napi_value is_mouse_swapped(napi_env env, napi_callback_info info);

napi_value mouse_scroll(napi_env env, napi_callback_info info);

napi_value keys_press(napi_env env, napi_callback_info info);
