#ifdef __APPLE__
#include <CoreGraphics/CoreGraphics.h>
#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>
#include <iostream>
#include <thread>
#include <vector>

#include "../utils.h"
#include "../main.h"

ScreenPoint f_get_screen_size() {
    CGDirectDisplayID displayID = kCGDirectMainDisplay;
    CGRect bounds = CGDisplayBounds(displayID);
    return ScreenPoint(static_cast<int>(bounds.size.width), static_cast<int>(bounds.size.height));
}

ScreenPoint f_get_cursor_position() {
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    return ScreenPoint(cursor.x, cursor.y);
}

bool f_set_cursor_position(int x, int y) {
    CGEventRef moveEvent = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved,
        CGPointMake(static_cast<CGFloat>(x), static_cast<CGFloat>(y)),
        kCGMouseButtonLeft);
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

#define ClickMacro(down, up, button)                \
    CGEventRef event = CGEventCreate(NULL);         \
    CGPoint cursor = CGEventGetLocation(event);     \
    CFRelease(event);                               \
    CGEventRef mouseDown = CGEventCreateMouseEvent( \
        NULL, (down),                               \
        cursor,                                     \
        (button));                                  \
    CGEventRef mouseUp = CGEventCreateMouseEvent(   \
        NULL, (up),                                 \
        cursor,                                     \
        (button));                                  \
    CGEventPost(kCGHIDEventTap, mouseDown);         \
    CGEventPost(kCGHIDEventTap, mouseUp);           \
    CFRelease(mouseDown);                           \
    CFRelease(mouseUp);                             \
    return true;

bool f_click_left() {
    ClickMacro(kCGEventLeftMouseDown, kCGEventLeftMouseUp, kCGMouseButtonLeft);
}

bool f_click_right() {
    ClickMacro(kCGEventRightMouseDown, kCGEventRightMouseUp, kCGMouseButtonRight);
}

bool f_click_middle() {
    ClickMacro(kCGEventOtherMouseDown, kCGEventOtherMouseUp, kCGMouseButtonCenter);
}

#define Mouse1Macro(t, button)                  \
    CGEventRef event = CGEventCreate(NULL);     \
    CGPoint cursor = CGEventGetLocation(event); \
    CFRelease(event);                           \
    CGEventRef cl = CGEventCreateMouseEvent(    \
        NULL, (t),                              \
        cursor,                                 \
        (button));                              \
    CGEventPost(kCGHIDEventTap, cl);            \
    CFRelease(cl);                              \
    return true;

bool f_mouse_left_down() {
    Mouse1Macro(kCGEventLeftMouseDown, kCGMouseButtonLeft);
}

bool f_mouse_right_down() {
    Mouse1Macro(kCGEventRightMouseDown, kCGMouseButtonRight);
}

bool f_mouse_middle_down() {
    Mouse1Macro(kCGEventOtherMouseDown, kCGMouseButtonCenter);
}

bool f_mouse_left_up() {
    Mouse1Macro(kCGEventLeftMouseUp, kCGMouseButtonLeft);
}

bool f_mouse_right_up() {
    Mouse1Macro(kCGEventRightMouseUp, kCGMouseButtonRight);
}

bool f_mouse_middle_up() {
    Mouse1Macro(kCGEventOtherMouseUp, kCGMouseButtonCenter);
}

bool f_is_mouse_swapped() {
    CFPropertyListRef value = CFPreferencesCopyValue(
        CFSTR("com.apple.mouse.swapLeftRightButton"),
        kCFPreferencesAnyApplication,
        kCFPreferencesCurrentUser,
        kCFPreferencesAnyHost);

    if (value != nullptr) {
        if (CFGetTypeID(value) == CFBooleanGetTypeID()) {
            bool isSwapped = CFBooleanGetValue(static_cast<CFBooleanRef>(value));
            CFRelease(value);
            return isSwapped;
        }
        CFRelease(value);
    }
    return false;
}

bool f_mouse_scroll(long x, long y) {
    auto scrollXSteps = static_cast<int32_t>(x);
    auto scrollYSteps = static_cast<int32_t>(y);
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
    // accept, add, alt, altleft, altright, apps, backspace,
    0, kVK_ANSI_KeypadPlus, kVK_Option, kVK_Option, kVK_RightOption, 0, kVK_Delete,
    // browserback, browserfavorites, browserforward, browserhome,
    0, 0, 0, 0,
    // browserrefresh, browsersearch, browserstop, capslock, clear,
    0, 0, 0, kVK_CapsLock, kVK_ANSI_KeypadClear,
    // convert, ctrl, ctrlleft, ctrlright, decimal, del, delete,
    0, kVK_Control, kVK_Control, kVK_RightControl, kVK_ANSI_KeypadDecimal, kVK_ForwardDelete, kVK_ForwardDelete,
    // divide, down, end, enter, esc, escape, execute, f1, f10,
    kVK_ANSI_KeypadDivide, kVK_DownArrow, kVK_End, kVK_Return, kVK_Escape, kVK_Escape, 0, kVK_F1, kVK_F10,
    // f11, f12, f13, f14, f15, f16, f17, f18, f19, f2, f20,
    kVK_F11, kVK_F12, kVK_F13, kVK_F14, kVK_F15, kVK_F16, kVK_F17, kVK_F18, kVK_F19, kVK_F2, kVK_F20,
    // f21, f22, f23, f24, f3, f4, f5, f6, f7, f8, f9,
    0, 0, 0, 0, kVK_F3, kVK_F4, kVK_F5, kVK_F6, kVK_F7, kVK_F8, kVK_F9,
    // final, hanguel, hangul, hanja, help, home, insert, junja,
    0, 0, 0, 0, kVK_Help, kVK_Home, kVK_Help, 0,
    // kana, kanji, launchapp1, launchapp2, launchmail,
    0, 0, 0, 0, 0,
    // launchmediaselect, left, modechange, multiply, nexttrack,
    0, kVK_LeftArrow, 0, kVK_ANSI_KeypadMultiply, 0,
    // nonconvert, num0, num1, num2, num3, num4, num5, num6,
    0, kVK_ANSI_Keypad0, kVK_ANSI_Keypad1, kVK_ANSI_Keypad2, kVK_ANSI_Keypad3, kVK_ANSI_Keypad4, kVK_ANSI_Keypad5, kVK_ANSI_Keypad6,
    // num7, num8, num9, numlock, pagedown, pageup, pause, pgdn,
    kVK_ANSI_Keypad7, kVK_ANSI_Keypad8, kVK_ANSI_Keypad9, 0, kVK_PageDown, kVK_PageUp, 0, kVK_PageDown,
    // pgup, playpause, prevtrack, print, printscreen, prntscrn,
    kVK_PageUp, 0, 0, 0, 0, 0,
    // prtsc, prtscr, return, right, scrolllock, select, separator,
    0, 0, kVK_Return, kVK_RightArrow, 0, 0, 0,
    // shift, shiftleft, shiftright, sleep, space, stop, subtract, tab,
    kVK_Shift, kVK_Shift, kVK_RightShift, 0, kVK_Space, 0, kVK_ANSI_KeypadMinus, kVK_Tab,
    // up, volumedown, volumemute, volumeup, win, winleft, winright, yen,
    kVK_UpArrow, kVK_VolumeDown, kVK_Mute, kVK_VolumeUp, kVK_Command, kVK_Command, kVK_RightCommand, kVK_JIS_Yen,
    // command, option, optionleft, optionright
    kVK_Command, kVK_Option, kVK_Option, kVK_RightOption
};

static void PostKey(CGKeyCode keycode, bool keyDown) {
    CGEventRef e = CGEventCreateKeyboardEvent(nullptr, keycode, keyDown);
    CGEventPost(kCGHIDEventTap, e);
    CFRelease(e);
}

bool f_keys_press(const KeyPressInfo* ch, size_t amount) {
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
