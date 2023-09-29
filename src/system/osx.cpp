#include <CoreGraphics/CoreGraphics.h>
#include <ApplicationServices/ApplicationServices.h>
#include <iostream>
#include <thread>
#include <vector>
#include "../main.h"

// in progress

Point f_get_screen_size()
{
    CGDirectDisplayID displayID = kCGDirectMainDisplay;
    CGRect bounds = CGDisplayBounds(displayID); // main screen
    return Point(static_cast<int>(bounds.size.width), static_cast<int>(bounds.size.height));
}

Point f_get_cursor_position()
{
    CGEventRef event = CGEventCreate(NULL);
    CGPoint cursor = CGEventGetLocation(event);
    CFRelease(event);
    return Point(cursor.x, cursor.y);
}

bool f_set_cursor_position(int x, int y)
{
    CGEventRef moveEvent = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved,
        CGPointMake(static_cast<CGFloat>(x), static_cast<CGFloat>(y)),
        kCGEventLeftMouseDown);
    CGEventPost(kCGHIDEventTap, moveEvent);
    CFRelease(moveEvent);
}

bool f_is_mouse_left_down()
{
    CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
    return (flags & kCGEventLeftMouseDown) != 0;
}

bool f_is_mouse_right_down()
{
    CGEventFlags flags = CGEventSourceFlagsState(kCGEventSourceStateHIDSystemState);
    return (flags & kCGEventRightMouseDown) != 0;
}

bool f_is_mouse_middle_down()
{
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

bool f_click_left()
{
    ClickMacro(kCGEventLeftMouseDown, kCGEventLeftMouseUp);
}

bool f_click_right()
{
    ClickMacro(kCGEventRightMouseDown, kCGEventRightMouseUp);
}

bool f_click_middle()
{
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

bool f_mouse_left_down()
{
    Mouse1Macro(kCGEventLeftMouseDown);
}

bool f_mouse_right_down()
{
    Mouse1Macro(kCGEventRightMouseDown);
}

bool f_mouse_middle_down()
{
    Mouse1Macro(kCGEventOtherMouseDown);
}

bool f_mouse_left_up()
{
    Mouse1Macro(kCGEventLeftMouseUp);
}

bool f_mouse_right_up()
{
    Mouse1Macro(kCGEventRightMouseUp);
}

bool f_mouse_middle_up()
{
    Mouse1Macro(kCGEventOtherMouseUp);
}

bool f_is_mouse_swapped()
{
    CFDictionaryRef mousePrefs = CGEventSourceCopyProperties(kCGEventSourceStateHIDSystemState);
    if (mousePrefs != nullptr)
    {
        CFBooleanRef isSwappedRef = static_cast<CFBooleanRef>(CFDictionaryGetValue(mousePrefs, kIOHIDMouseKeysOnKey));
        if (isSwappedRef != nullptr)
        {
            bool isSwapped = CFBooleanGetValue(isSwappedRef);
            CFRelease(mousePrefs);
            return isSwapped;
        }
        CFRelease(mousePrefs);
    }
    return false;
}

bool f_mouse_scroll(int x, int y)
{
    int scrollXSteps = x;
    int scrollYSteps = y;
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

bool f_press_key(bool is_ascii, int got)
{
    CGEventSourceRef eventSource = kCGEventSourceStateHIDSystemState;
    CGEventRef keyDownEvent = CGEventCreateKeyboardEvent(eventSource, (CGKeyCode)0, true);
    CGEventKeyboardSetUnicodeString(keyDownEvent, 1, &got);
    CGEventPost(kCGHIDEventTap, keyDownEvent);
    CFRelease(keyDownEvent);

    CGEventRef keyUpEvent = CGEventCreateKeyboardEvent(eventSource, (CGKeyCode)0, false);
    CGEventKeyboardSetUnicodeString(keyUpEvent, 1, &got);
    CGEventPost(kCGHIDEventTap, keyUpEvent);
    CFRelease(keyUpEvent);
    return true;
}

bool f_key_down(bool is_ascii, int got)
{
    CGEventSourceRef eventSource = kCGEventSourceStateHIDSystemState;
    CGEventRef keyDownEvent = CGEventCreateKeyboardEvent(eventSource, (CGKeyCode)0, true);
    CGEventKeyboardSetUnicodeString(keyDownEvent, 1, &got);
    CGEventPost(kCGHIDEventTap, keyDownEvent);
    CFRelease(keyDownEvent);
}

bool f_key_up(bool is_ascii, int got)
{
    CGEventSourceRef eventSource = kCGHIDEventSourceStateHIDSystemState;
    CGEventRef keyUpEvent = CGEventCreateKeyboardEvent(eventSource, (CGKeyCode)0, false);
    CGEventKeyboardSetUnicodeString(keyUpEvent, 1, &got);
    CGEventPost(kCGHIDEventTap, keyUpEvent);
    CFRelease(keyUpEvent);
    return true;
}

int f_show_message_box(char *textBuf, char *captionBuf, int flags)
{
    return 0;
}

int f_show_prompt()
{
    return 0;
}