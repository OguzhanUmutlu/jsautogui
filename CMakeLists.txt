cmake_minimum_required(VERSION 3.28)
project(jsautogui)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

add_executable(jsautogui
        src/system/osx.cpp
        src/system/winfn.cpp
        src/system/x11fn.cpp
        src/test.cpp
        src/utils.h)

target_include_directories(jsautogui PRIVATE "C:/Users/HP/AppData/Local/node-gyp/Cache/22.11.0/include/node")
target_include_directories(jsautogui PRIVATE "/home/usr/.nvm/versions/node/v22.7.0/include/node")
