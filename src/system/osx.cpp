#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#include <ApplicationServices/ApplicationServices.h>
#include <iostream>
#include <thread>
#include <vector>

#include "utils.h"
#include "../main.h"

// in progress

optional<Point> f_get_screen_size() {
    CGDirectDisplayID displayID = kCGDirectMainDisplay;
    CGRect bounds = CGDisplayBounds(displayID); // main screen
    return make_optional(Point(static_cast<int>(bounds.size.width), static_cast<int>(bounds.size.height)));
}

optional<Point> f_get_cursor_position() {
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    return make_optional(Point(cursor.x, cursor.y));
}

bool f_set_cursor_position(int x, int y) {
    CGEventRef moveEvent = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved,
        CGPointMake(static_cast<CGFloat>(x), static_cast<CGFloat>(y)),
        kCGEventLeftMouseDown);
    CGEventPost(kCGHIDEventTap, moveEvent);
    CFRelease(moveEvent);
    return true;
}

bool f_is_mouse_left_down() {
    CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
    return (flags & kCGEventLeftMouseDown) != 0;
}

bool f_is_mouse_right_down() {
    CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
    return (flags & kCGEventRightMouseDown) != 0;
}

bool f_is_mouse_middle_down() {
    CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
    return (flags & kCGEventOtherMouseDown) != 0;
}

#define ClickMacro(down, up)                        \
    CGEventRef event = CGEventCreate(NULL);         \
    CGPoint cursor = CGEventGetLocation(event);     \
    CFRelease(event);                               \
    CGEventRef mouseDown = CGEventCreateMouseEvent( \
        NULL, (down),                               \
        cursor,                                     \
        kCGHIDEventTap);                            \
    CGEventRef mouseUp = CGEventCreateMouseEvent(   \
        NULL, (up),                                 \
        cursor,                                     \
        kCGHIDEventTap);                            \
    CGEventPost(kCGHIDEventTap, mouseDown);         \
    CGEventPost(kCGHIDEventTap, mouseUp);           \
    CFRelease(mouseDown);                           \
    CFRelease(mouseUp);                             \
    return true;

bool f_click_left() {
    ClickMacro(kCGEventLeftMouseDown, kCGEventLeftMouseUp);
}

bool f_click_right() {
    ClickMacro(kCGEventRightMouseDown, kCGEventRightMouseUp);
}

bool f_click_middle() {
    ClickMacro(kCGEventOtherMouseDown, kCGEventOtherMouseUp);
}

#define Mouse1Macro(t)                          \
    CGEventRef event = CGEventCreate(NULL);     \
    CGPoint cursor = CGEventGetLocation(event); \
    CFRelease(event);                           \
    CGEventRef cl = CGEventCreateMouseEvent(    \
        NULL, (t),                              \
        cursor,                                 \
        kCGHIDEventTap);                        \
    CGEventPost(kCGHIDEventTap, cl);            \
    CFRelease(cl);                              \
    return true;

bool f_mouse_left_down() {
    Mouse1Macro(kCGEventLeftMouseDown);
}

bool f_mouse_right_down() {
    Mouse1Macro(kCGEventRightMouseDown);
}

bool f_mouse_middle_down() {
    Mouse1Macro(kCGEventOtherMouseDown);
}

bool f_mouse_left_up() {
    Mouse1Macro(kCGEventLeftMouseUp);
}

bool f_mouse_right_up() {
    Mouse1Macro(kCGEventRightMouseUp);
}

bool f_mouse_middle_up() {
    Mouse1Macro(kCGEventOtherMouseUp);
}

bool f_is_mouse_swapped() {
    CFDictionaryRef mousePrefs = CGEventSourceCopyProperties(kCGEventSourceStateHIDSystemState);
    if (mousePrefs != nullptr) {
        CFBooleanRef isSwappedRef = static_cast<CFBooleanRef>(CFDictionaryGetValue(mousePrefs, kIOHIDMouseKeysOnKey));
        if (isSwappedRef != nullptr) {
            bool isSwapped = CFBooleanGetValue(isSwappedRef);
            CFRelease(mousePrefs);
            return isSwapped;
        }
        CFRelease(mousePrefs);
    }
    return false;
}

bool f_mouse_scroll(unsigned long x, unsigned long y) {
    auto scrollXSteps = x;
    auto scrollYSteps = y;
    CGEventRef scrollXEvent = CGEventCreateScrollWheelEvent(
        NULL, kCGScrollEventUnitPixel, 2, scrollXSteps);
    CGEventRef scrollYEvent = CGEventCreateScrollWheelEvent(
        NULL, kCGScrollEventUnitPixel, 1, scrollYSteps);
    CGEventPost(kCGHIDEventTap, scrollXEvent);
    CGEventPost(kCGHIDEventTap, scrollYEvent);
    CFRelease(scrollXEvent);
    CFRelease(scrollYEvent);
    return true;
}

static const CGKeyCode MODIFIERS[] = {
    0, // placeholder
    kVK_ANSI_Equal, // ↗
    kVK_Option,
    kVK_Option,
    kVK_RightOption,
    0, // placeholder
    kVK_Delete,
    0, // placeholder
    kVK_F20,
    kVK_F21,
    kVK_F22,
    kVK_F23,
    kVK_F24,
    kVK_F15, // placeholder
    kVK_CapsLock,
    kVK_Clear,
    kVK_JIS_Yen, // best fit
    kVK_Control,
    kVK_Control,
    kVK_RightControl,
    kVK_ANSI_Period,
    kVK_ForwardDelete,
    kVK_ForwardDelete,
    kVK_ANSI_Slash,
    kVK_DownArrow,
    kVK_End,
    kVK_Return,
    kVK_Escape,
    kVK_Escape,
    0, // placeholder
    kVK_F1,
    kVK_F10,
    kVK_F11,
    kVK_F12,
    kVK_F13,
    kVK_F14,
    kVK_F15,
    kVK_F16,
    kVK_F17,
    kVK_F18,
    kVK_F19,
    kVK_F2,
    kVK_F20,
    kVK_F21,
    kVK_F22,
    kVK_F23,
    kVK_F24,
    kVK_F3,
    kVK_F4,
    kVK_F5,
    kVK_F6,
    kVK_F7,
    kVK_F8,
    kVK_F9,
    0, // placeholder
    kVK_JIS_Kana, // best fit
    kVK_JIS_Kana,
    kVK_JIS_Eisu,
    kVK_Help,
    kVK_Home,
    kVK_Help, // mac has no Insert—reuse Help
    0, // placeholder
    kVK_JIS_Kana,
    kVK_JIS_Eisu,
    kVK_F14,
    kVK_F15,
    kVK_F16,
    kVK_F17,
    kVK_LeftArrow,
    kVK_ModeSwitch,
    kVK_ANSI_Asterisk,
    kVK_F18,
    kVK_JIS_Yen,
    kVK_ANSI_0,
    kVK_ANSI_1,
    kVK_ANSI_2,
    kVK_ANSI_3,
    kVK_ANSI_4,
    kVK_ANSI_5,
    kVK_ANSI_6,
    kVK_ANSI_7,
    kVK_ANSI_8,
    kVK_ANSI_9,
    kVK_NumLock,
    kVK_PageDown,
    kVK_PageUp,
    kVK_Pause,
    kVK_PageDown,
    kVK_PageUp,
    kVK_Play,
    kVK_Previous,
    kVK_PrintScreen,
    kVK_PrintScreen,
    kVK_PrintScreen,
    kVK_PrintScreen,
    kVK_PrintScreen,
    kVK_Return,
    kVK_RightArrow,
    kVK_ScrollLock,
    kVK_ANSI_5, // best fit
    kVK_ANSI_Minus, // best fit
    kVK_Shift,
    kVK_Shift,
    kVK_RightShift,
    kVK_Power,
    kVK_Space,
    kVK_Stop,
    kVK_ANSI_Minus,
    kVK_Tab,
    kVK_UpArrow,
    kVK_VolumeDown,
    kVK_VolumeMute,
    kVK_VolumeUp,
    kVK_Command,
    kVK_Command,
    kVK_RightCommand,
    kVK_JIS_Yen,
    kVK_Command,
    kVK_Option,
    kVK_Option,
    kVK_RightOption
};

static void PostKey(CGKeyCode keycode, bool keyDown) {
    CGEventRef e = CGEventCreateKeyboardEvent(nullptr, keycode, keyDown);
    CGEventPost(kCGHIDEventTap, e);
    CFRelease(e);
}

bool f_keys_press(const KeyPressInfo *ch, size_t amount) {
    for (size_t i = 0; i < amount; i++) {
        auto [down, up, mode, key] = ch[i];
        switch (mode) {
            case KeyPressMode::ASCII: {
                if (down) {
                    CGEventRef e = CGEventCreateKeyboardEvent(nullptr, 0, true);
                    UniChar c = static_cast<char>(key);
                    CGEventKeyboardSetUnicodeString(e, 1, &c);
                    CGEventPost(kCGHIDEventTap, e);
                    CFRelease(e);
                }
                if (up) {
                    CGEventRef e = CGEventCreateKeyboardEvent(nullptr, 0, false);
                    UniChar c = static_cast<char>(key);
                    CGEventKeyboardSetUnicodeString(e, 1, &c);
                    CGEventPost(kCGHIDEventTap, e);
                    CFRelease(e);
                }
                break;
            }
            case KeyPressMode::UNICODE: {
                if (down) {
                    CGEventRef e = CGEventCreateKeyboardEvent(nullptr, 0, true);
                    UniChar u = key;
                    CGEventKeyboardSetUnicodeString(e, 1, &u);
                    CGEventPost(kCGHIDEventTap, e);
                    CFRelease(e);
                }
                if (up) {
                    CGEventRef e = CGEventCreateKeyboardEvent(nullptr, 0, false);
                    UniChar u = key;
                    CGEventKeyboardSetUnicodeString(e, 1, &u);
                    CGEventPost(kCGHIDEventTap, e);
                    CFRelease(e);
                }
                break;
            }
            case KeyPressMode::SPECIAL: {
                if (key >= sizeof(MODIFIERS) / sizeof(*MODIFIERS))
                    continue;
                CGKeyCode vk = MODIFIERS[key];
                if (down) PostKey(vk, true);
                if (up) PostKey(vk, false);
                break;
            }
        }
    }
    return true;
}

#endif
