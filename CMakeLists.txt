cmake_minimum_required(VERSION 3.16)
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

if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED COMPONENTS Xtst)
    target_link_libraries(jsautogui ${X11_LIBRARIES} ${X11_Xtst_LIB})
endif()

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(CARBON_LIBRARY Carbon REQUIRED)
    find_library(COREGRAPHICS_LIBRARY CoreGraphics REQUIRED)
    find_library(APPLICATIONSERVICES_LIBRARY ApplicationServices REQUIRED)
    target_link_libraries(jsautogui
        ${COCOA_LIBRARY}
        ${CARBON_LIBRARY}
        ${COREGRAPHICS_LIBRARY}
        ${APPLICATIONSERVICES_LIBRARY})
endif()

