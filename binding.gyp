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
            "conditions": [
                ["OS=='mac'", {
                    "xcode_settings": {
                        "OTHER_CFLAGS": ["-ObjC++"],
                        "OTHER_LDFLAGS": [
                            "-framework CoreGraphics",
                            "-framework ApplicationServices",
                            "-framework Carbon",
                            "-framework Cocoa"
                        ]
                    },
                    "link_settings": {
                        "libraries": [
                            "-framework CoreGraphics",
                            "-framework ApplicationServices",
                            "-framework Carbon",
                            "-framework Cocoa"
                        ]
                    }
                }],
                ["OS=='linux'", {
                    "libraries": [
                        "-lX11",
                        "-lXtst"
                    ]
                }]
            ]
        }
    ]
}
