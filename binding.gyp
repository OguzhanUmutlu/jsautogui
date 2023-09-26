{
    "targets": [
        {
            "target_name": "jsautogui",
            "sources": [
                "src/functions.cc",
                "src/functions.h",
                "src/main.cc",
                "src/main.h",
                "src/os_include.h"
            ],
            "conditions": [
                [
                    'OS=="linux"',
                    {
                        "sources": [
                            "src/system/x11fn.cc"
                        ]
                    },
                ],
                [
                    'OS=="win"',
                    {
                        "sources": [
                            "src/system/winfn.cc"
                        ]
                    }
                ]
            ]
        }
    ]
}
