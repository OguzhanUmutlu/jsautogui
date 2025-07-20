#pragma once
#include <optional>
#include <vector>

using namespace std;

#include <node_api.h>

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
