#include <node_api.h>
#include <thread>
#include <iostream>
#include "main.h"
#include "utils.h"

int32_t callPause = 0;

void do_call_pause() {
    if (callPause > 0) {
        this_thread::sleep_for(chrono::milliseconds(callPause / 1000));
    }
}

napi_value set_pause(napi_env env, napi_callback_info info) {
    size_t argc = 1;
    napi_value args[1];
    prepare_args(env, info, argc, args);
    callPause = read_int32(env, args[0]);
    return nullptr;
}

napi_value get_screen_size(napi_env env, napi_callback_info info) {
    do_call_pause();
    napi_value posObject = create_object(env);
    auto size = f_get_screen_size();
    if (size.has_value()) return nullptr;
    set_object_key(env, posObject, "width", create_int32(env, size.value().x));
    set_object_key(env, posObject, "height", create_int32(env, size.value().y));
    return posObject;
}

napi_value set_mouse_pos_rel(napi_env env, napi_callback_info info) {
    do_call_pause();
    auto cursorPos = f_get_cursor_position();
    if (!cursorPos.has_value()) return nullptr;
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_set_cursor_position(
                           read_int32(env, args[0]) + cursorPos.value().x,
                           read_int32(env, args[1]) + cursorPos.value().y));
}

napi_value set_mouse_pos(napi_env env, napi_callback_info info) {
    do_call_pause();
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_set_cursor_position(read_int32(env, args[0]), read_int32(env, args[1])));
}

napi_value set_mouse_x(napi_env env, napi_callback_info info) {
    do_call_pause();
    auto cursorPos = f_get_cursor_position();
    if (!cursorPos.has_value()) return nullptr;
    size_t argc = 1;
    napi_value args[1];
    prepare_args(env, info, argc, args);
    return create_bool(env, f_set_cursor_position(read_int32(env, args[0]), cursorPos.value().y));
}

napi_value set_mouse_y(napi_env env, napi_callback_info info) {
    do_call_pause();
    auto cursorPos = f_get_cursor_position();
    if (!cursorPos.has_value()) return nullptr;
    size_t argc = 1;
    napi_value args[1];
    prepare_args(env, info, argc, args);
    return create_bool(env, f_set_cursor_position(cursorPos.value().x, read_int32(env, args[0])));
}

napi_value get_mouse_pos(napi_env env, napi_callback_info info) {
    do_call_pause();
    auto cursorPos = f_get_cursor_position();
    if (!cursorPos.has_value()) return nullptr;
    napi_value posObject = create_object(env);
    set_object_key(env, posObject, "x", create_int32(env, cursorPos.value().x));
    set_object_key(env, posObject, "y", create_int32(env, cursorPos.value().y));
    return posObject;
}

napi_value mouse_is_left_down(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_is_mouse_left_down());
}

napi_value mouse_is_right_down(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_is_mouse_right_down());
}

napi_value mouse_is_middle_down(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_is_mouse_middle_down());
}

napi_value click_left(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_click_left());
}

napi_value click_right(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_click_right());
}

napi_value click_middle(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_click_middle());
}

napi_value mouse_left_down(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_mouse_left_down());
}

napi_value mouse_right_down(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_mouse_right_down());
}

napi_value mouse_middle_down(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_mouse_middle_down());
}

napi_value mouse_left_up(napi_env env, napi_callback_info info) {
    do_call_pause();
    f_mouse_left_up();
    return create_bool(env, f_mouse_left_up());
}

napi_value mouse_right_up(napi_env env, napi_callback_info info) {
    do_call_pause();
    f_mouse_right_up();
    return create_bool(env, f_mouse_right_up());
}

napi_value mouse_middle_up(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_mouse_middle_up());
}

napi_value is_mouse_swapped(napi_env env, napi_callback_info info) {
    do_call_pause();
    return create_bool(env, f_is_mouse_swapped());
}

napi_value mouse_scroll(napi_env env, napi_callback_info info) {
    do_call_pause();
    size_t argc = 2;
    napi_value args[2];
    prepare_args(env, info, argc, args);

    return create_bool(env, f_mouse_scroll(read_int32(env, args[0]), read_int32(env, args[1])));
}

napi_value keys_press(napi_env env, napi_callback_info info) {
    do_call_pause();
    size_t argc;
    napi_value args[1];
    napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);

    auto array = args[0];
    bool is_typedarray;
    napi_is_typedarray(env, array, &is_typedarray);
    if (!is_typedarray) {
        napi_throw_type_error(env, nullptr, "Expected a UInt32Array");
        return nullptr;
    }

    napi_typedarray_type type;
    size_t length;
    void *data;
    napi_value arraybuffer;
    size_t byte_offset;

    napi_get_typedarray_info(env, array, &type, &length, &data, &arraybuffer, &byte_offset);

    if (type != napi_uint32_array) {
        napi_throw_type_error(env, nullptr, "Expected a UInt32Array");
        return nullptr;
    }

    auto presses = new KeyPressInfo[length];

    auto uint32_data = static_cast<uint32_t *>(data);
    for (size_t i = 0; i < length; ++i) {
        auto u = uint32_data[i];
        presses[i] = {
            .down = (u & (1 << 20)) != 0,
            .up = (u & (1 << 19)) != 0,
            .mode = static_cast<KeyPressMode>((u >> 16) & 3),
            .key = static_cast<uint16_t>(u & 0xFFFF)
        };
    }

    return create_bool(env, f_keys_press(presses, length));
}
