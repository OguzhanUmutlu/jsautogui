{
    "defines": [ "NAPI_VERSION=8" ],
    "targets": [
        {
            "target_name": "jsautogui",
            "sources": [
                "src/system/osx.cpp",
                "src/system/winfn.cpp",
                "src/system/x11fn.cpp",
                "src/node_functions.cpp",
                "src/main.cpp",
                "src/utils.h",
                "src/node_functions.h",
                "src/main.h",
            ],
        }
    ]
}
