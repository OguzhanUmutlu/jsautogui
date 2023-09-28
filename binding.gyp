{
    "targets": [
        {
            "target_name": "jsautogui",
            "sources": [
                "src/functions.cpp",
                "src/functions.cpp",
                "src/main.cpp",
                "src/main.h",
            ],
            "conditions": [
                ["OS=='win'", {"sources": ["src/system/winfn.cpp"]}],
                [
                    "OS=='mac'",
                    {
                        "sources": ["src/system/osx.cpp"],
                        "libraries": ["-framework CoreGraphics"],
                    },
                ],
                [
                    "OS!='win' and OS!='mac'",
                    {
                        "sources": ["src/system/x11fn.cpp"],
                        "libraries": ["-lX11", "-lXtst"],
                    },
                ],
            ],
        }
    ]
}
