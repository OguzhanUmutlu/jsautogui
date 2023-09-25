#include <node_api.h>
#include <iostream>
#include "functions.h"

#define NC(env, call, err)                                                \
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
                return NULL;                                              \
            }                                                             \
        }                                                                 \
    } while (0);

struct Point
{
    int x;
    int y;

    Point(int x, int y) : x(x), y(y) {}
};

char *read_string(napi_env env, napi_value value)
{
    size_t length;
    NC(env, napi_get_value_string_utf8(env, value, nullptr, 0, &length), "Couldn't read the length of a string.");
    char *buffer = new char[length + 1];
    NC(env, napi_get_value_string_utf8(env, value, buffer, length + 1, nullptr), "Couldn't read the value of a string.");
    return buffer;
}

int32_t read_int32(napi_env env, napi_value value)
{
    int32_t res;
    NC(env, napi_get_value_int32(env, value, &res), "Couldn't parse the value to int32_t.");
    return res;
}

int64_t read_int64(napi_env env, napi_value value)
{
    int64_t res;
    NC(env, napi_get_value_int64(env, value, &res), "Couldn't parse the value to int64_t.");
    return res;
}

bool read_bool(napi_env env, napi_value value)
{
    bool res;
    NC(env, napi_get_value_bool(env, value, &res), "Couldn't parse the value to bool.");
    return res;
}

napi_value create_int32(napi_env env, int32_t value)
{
    napi_value res;
    NC(env, napi_create_int32(env, value, &res), "Couldn't create an int32 value.");
    return res;
}

napi_value create_int64(napi_env env, int64_t value)
{
    napi_value res;
    NC(env, napi_create_int64(env, value, &res), "Couldn't create an int64 value.");
    return res;
}

napi_value create_bool(napi_env env, bool value)
{
    napi_value res;
    NC(env, napi_get_boolean(env, value, &res), "Couldn't create a bool value.");
    return res;
}

napi_value create_object(napi_env env)
{
    napi_value res;
    NC(env, napi_create_object(env, &res), "Couldn't create an object value.");
    return res;
}

int set_object_key(napi_env env, napi_value obj, const char *name, napi_value value)
{
    NC(env, napi_set_named_property(env, obj, name, value), "Couldn't set the key of an object.");
    return 0;
}

int prepare_args(napi_env env, napi_callback_info info, size_t &argc, napi_value *args)
{
    NC(env, napi_get_cb_info(env, info, &argc, args, NULL, NULL), "Couldn't parse the arguments.");
    return 0;
}

void add_function_to_object(napi_env env, napi_value object, const char *name, napi_callback cb)
{
    napi_value fn;
    napi_create_function(env, nullptr, 0, cb, nullptr, &fn);
    napi_set_named_property(env, object, name, fn);
}

napi_value init(napi_env env, napi_value exports)
{
    napi_value object;

    napi_create_object(env, &object);

    add_function_to_object(env, object, "click_left", click_left);
    add_function_to_object(env, object, "click_right", click_right);
    add_function_to_object(env, object, "click_middle", click_middle);
    add_function_to_object(env, object, "get_mouse_pos", get_mouse_pos);
    add_function_to_object(env, object, "set_mouse_pos", set_mouse_pos);
    add_function_to_object(env, object, "set_mouse_pos_rel", set_mouse_pos_rel);
    add_function_to_object(env, object, "get_screen_size", get_screen_size);
    add_function_to_object(env, object, "set_pause", set_pause);
    add_function_to_object(env, object, "set_mouse_x", set_mouse_x);
    add_function_to_object(env, object, "set_mouse_y", set_mouse_y);
    add_function_to_object(env, object, "mouse_is_left_down", mouse_is_left_down);
    add_function_to_object(env, object, "mouse_is_right_down", mouse_is_right_down);
    add_function_to_object(env, object, "mouse_is_middle_down", mouse_is_middle_down);
    add_function_to_object(env, object, "mouse_left_down", mouse_left_down);
    add_function_to_object(env, object, "mouse_right_down", mouse_right_down);
    add_function_to_object(env, object, "mouse_middle_down", mouse_middle_down);
    add_function_to_object(env, object, "mouse_left_up", mouse_left_up);
    add_function_to_object(env, object, "mouse_right_up", mouse_right_up);
    add_function_to_object(env, object, "mouse_middle_up", mouse_middle_up);
    add_function_to_object(env, object, "is_mouse_swapped", is_mouse_swapped);
    add_function_to_object(env, object, "mouse_scroll", mouse_scroll);
    add_function_to_object(env, object, "press_key", press_key);
    add_function_to_object(env, object, "key_down", key_down);
    add_function_to_object(env, object, "key_up", key_up);
    add_function_to_object(env, object, "show_message_box", show_message_box);
    add_function_to_object(env, object, "show_prompt", show_prompt);

    return object;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init);