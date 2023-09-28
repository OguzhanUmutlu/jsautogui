#include <CoreGraphics/CoreGraphics.h>
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
    // Create a mouse event
    CGEventRef moveEvent = CGEventCreateMouseEvent(
        NULL, kCGEventMouseMoved,
        CGPointMake(static_cast<CGFloat>(x), static_cast<CGFloat>(y)),
        kCGEventLeftMouseDown
    );

    // Post the event to set the cursor position
    CGEventPost(kCGHIDEventTap, moveEvent);
    
    // Release the event
    CFRelease(moveEvent);
}

bool f_is_mouse_left_down()
{
    return GetAsyncKeyState(VK_LBUTTON) & 0x8000;
}

bool f_is_mouse_right_down()
{
    return GetAsyncKeyState(VK_RBUTTON) & 0x8000;
}

bool f_is_mouse_middle_down()
{
    return GetAsyncKeyState(VK_MBUTTON) & 0x8000;
}

bool f_click_left()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN + MOUSEEVENTF_LEFTUP;
    INPUT_SEND(input);
    return true;
}

bool f_click_right()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN + MOUSEEVENTF_RIGHTUP;
    INPUT_SEND(input);
    return true;
}

bool f_click_middle()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN + MOUSEEVENTF_MIDDLEUP;
    INPUT_SEND(input);
    return true;
}

bool f_mouse_left_down()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    INPUT_SEND(input);
    return true;
}

bool f_mouse_right_down()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    INPUT_SEND(input);
    return true;
}

bool f_mouse_middle_down()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
    INPUT_SEND(input);
    return true;
}

bool f_mouse_left_up()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    INPUT_SEND(input);
    return true;
}

bool f_mouse_right_up()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    INPUT_SEND(input);
    return true;
}

bool f_mouse_middle_up()
{
    INPUT input;
    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
    INPUT_SEND(input);
    return true;
}

bool f_is_mouse_swapped()
{
    return GetSystemMetrics(23) != 0;
}

bool f_mouse_scroll(int x, int y)
{
    INPUT input;
    input.type = INPUT_MOUSE;

    if (x != 0)
    {
        input.mi.mouseData = x;
        input.mi.dwFlags = MOUSEEVENTF_HWHEEL;
        INPUT_SEND(input);
    }

    if (y != 0)
    {
        input.mi.mouseData = y;
        input.mi.dwFlags = MOUSEEVENTF_WHEEL;
        INPUT_SEND(input);
    }

    if (x != 0 || y != 0)
    {
        input.mi.dwFlags = 0;
        INPUT_SEND(input);
    }
    return true;
}

bool f_press_key(bool is_ascii, int got)
{
    if (is_ascii)
    {
        got = VkKeyScanA(static_cast<CHAR>(got));
    }

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = got;
    input.ki.dwFlags = 0;
    INPUT_SEND(input);

    input.ki.dwFlags = KEYEVENTF_KEYUP;
    INPUT_SEND(input);
    return true;
}

bool f_key_down(bool is_ascii, int got)
{
    if (is_ascii)
    {
        got = VkKeyScanA(static_cast<CHAR>(got));
    }

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = got;
    input.ki.dwFlags = 0;
    INPUT_SEND(input);
    return true;
}

bool f_key_up(bool is_ascii, int got)
{
    if (is_ascii)
    {
        got = VkKeyScanA(static_cast<CHAR>(got));
    }

    INPUT input;
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = got;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    INPUT_SEND(input);
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