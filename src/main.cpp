#include "main.h"
#include "node_functions.h"

#include <node_api.h>
#include <iostream>

#define NC(env, call, err, ret)                                           \
    do                                                                    \
    {                                                                     \
        napi_status status = (call);                                      \
        if (status != napi_ok)                                            \
        {                                                                 \
            const napi_extended_error_info *error_info = NULL;            \
            napi_get_last_error_info((env), &error_info);                 \
            bool is_pending;                                              \
            napi_is_exception_pending((env), &is_pending);                \
            if (!is_pending)                                              \
            {                                                             \
                const char *message = (error_info->error_message == NULL) \
                                          ? (err)                         \
                                          : error_info->error_message;    \
                napi_throw_error((env), NULL, message);                   \
                return ret;                                              \
            }                                                             \
        }                                                                 \
    } while (0);

char* read_string(napi_env env, napi_value value) {
    size_t length;
    NC(env, napi_get_value_string_utf8(env, value, nullptr, 0, &length), "Couldn't read the length of a string.", NULL);
    char* buffer = new char[length + 1];
    NC(env, napi_get_value_string_utf8(env, value, buffer, length + 1, nullptr),
       "Couldn't read the value of a string.", NULL);
    return buffer;
}

int32_t read_int32(napi_env env, napi_value value) {
    int32_t res;
    NC(env, napi_get_value_int32(env, value, &res), "Couldn't parse the value to int32_t.", 0);
    return res;
}

int64_t read_int64(napi_env env, napi_value value) {
    int64_t res;
    NC(env, napi_get_value_int64(env, value, &res), "Couldn't parse the value to int64_t.", 0);
    return res;
}

bool read_bool(napi_env env, napi_value value) {
    bool res;
    NC(env, napi_get_value_bool(env, value, &res), "Couldn't parse the value to bool.", 0);
    return res;
}

napi_value create_int32(napi_env env, int32_t value) {
    napi_value res;
    NC(env, napi_create_int32(env, value, &res), "Couldn't create an int32 value.", 0);
    return res;
}

napi_value create_int64(napi_env env, int64_t value) {
    napi_value res;
    NC(env, napi_create_int64(env, value, &res), "Couldn't create an int64 value.", 0);
    return res;
}

napi_value create_bool(napi_env env, bool value) {
    napi_value res;
    NC(env, napi_get_boolean(env, value, &res), "Couldn't create a bool value.", 0);
    return res;
}

napi_value create_object(napi_env env) {
    napi_value res;
    NC(env, napi_create_object(env, &res), "Couldn't create an object value.", 0);
    return res;
}

int set_object_key(napi_env env, napi_value obj, const char* name, napi_value value) {
    NC(env, napi_set_named_property(env, obj, name, value), "Couldn't set the key of an object.", 0);
    return 0;
}

int prepare_args(napi_env env, napi_callback_info info, size_t& argc, napi_value* args) {
    NC(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL), "Couldn't parse the arguments.", 0);
    return 0;
}

void add_function_to_object(napi_env env, napi_value object, const char* name, napi_callback cb) {
    napi_value fn;
    napi_create_function(env, nullptr, 0, cb, nullptr, &fn);
    napi_set_named_property(env, object, name, fn);
}

napi_value init(napi_env env, napi_value exports) {
    add_function_to_object(env, exports, "click_left", click_left);
    add_function_to_object(env, exports, "click_right", click_right);
    add_function_to_object(env, exports, "click_middle", click_middle);
    add_function_to_object(env, exports, "get_mouse_pos", get_mouse_pos);
    add_function_to_object(env, exports, "set_mouse_pos", set_mouse_pos);
    add_function_to_object(env, exports, "set_mouse_pos_rel", set_mouse_pos_rel);
    add_function_to_object(env, exports, "get_screen_size", get_screen_size);
    add_function_to_object(env, exports, "set_pause", set_pause);
    add_function_to_object(env, exports, "set_mouse_x", set_mouse_x);
    add_function_to_object(env, exports, "set_mouse_y", set_mouse_y);
    add_function_to_object(env, exports, "mouse_is_left_down", mouse_is_left_down);
    add_function_to_object(env, exports, "mouse_is_right_down", mouse_is_right_down);
    add_function_to_object(env, exports, "mouse_is_middle_down", mouse_is_middle_down);
    add_function_to_object(env, exports, "mouse_left_down", mouse_left_down);
    add_function_to_object(env, exports, "mouse_right_down", mouse_right_down);
    add_function_to_object(env, exports, "mouse_middle_down", mouse_middle_down);
    add_function_to_object(env, exports, "mouse_left_up", mouse_left_up);
    add_function_to_object(env, exports, "mouse_right_up", mouse_right_up);
    add_function_to_object(env, exports, "mouse_middle_up", mouse_middle_up);
    add_function_to_object(env, exports, "is_mouse_swapped", is_mouse_swapped);
    add_function_to_object(env, exports, "mouse_scroll", mouse_scroll);
    add_function_to_object(env, exports, "keys_press", keys_press);

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);
