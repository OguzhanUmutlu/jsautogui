#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>
#include <cstdio>
#include <thread>
#include <vector>
#include "../main.h"

#define GetDisplay(ret)                       \
    Display *display = XOpenDisplay(nullptr); \
    if (display == nullptr)                   \
    {                                         \
        return (ret);                         \
    }

Point f_get_screen_size()
{
    Display *display = XOpenDisplay(nullptr);
    if (!display)
    {
        return Point(-1, -1);
    }
    int screen_num = DefaultScreen(display);

    XCloseDisplay(display);
    return Point(DisplayWidth(display, screen_num), DisplayHeight(display, screen_num));
}

Point f_get_cursor_position()
{
    Display *display = XOpenDisplay(nullptr);
    if (!display)
    {
        return Point(-1, -1);
    }
    Window rootWindow = DefaultRootWindow(display);
    XEvent event;
    XQueryPointer(display, rootWindow, &event.xbutton.root, &event.xbutton.window,
                  &event.xbutton.x_root, &event.xbutton.y_root,
                  &event.xbutton.x, &event.xbutton.y, &event.xbutton.state);
    XFlush(display);
    XCloseDisplay(display);
    return Point(event.xbutton.x_root, event.xbutton.y_root);
}

bool f_set_cursor_position(int x, int y)
{
    Display *display = XOpenDisplay(NULL);
    if (!display)
    {
        return false;
    }
    XWarpPointer(display, None, DefaultRootWindow(display), 0, 0, 0, 0, x, y);
    XFlush(display);
    XCloseDisplay(display);
    return true;
}

#define IsDownMacro(check)                                                                                                          \
    GetDisplay(false);                                                                                                              \
    Window root = DefaultRootWindow(display);                                                                                       \
    XEvent event;                                                                                                                   \
    XGrabPointer(display, root, False, ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime); \
    XMaskEvent(display, ButtonPressMask, &event);                                                                                   \
    if (event.type == ButtonPress && (check))                                                                                       \
    {                                                                                                                               \
        XUngrabPointer(display, CurrentTime);                                                                                       \
        XCloseDisplay(display);                                                                                                     \
        return true;                                                                                                                \
    }                                                                                                                               \
    XUngrabPointer(display, CurrentTime);                                                                                           \
    XCloseDisplay(display);                                                                                                         \
    return false;

bool f_is_mouse_left_down()
{
    IsDownMacro(event.xbutton.button == Button1);
}

bool f_is_mouse_right_down()
{
    IsDownMacro(event.xbutton.button == Button3);
}

bool f_is_mouse_middle_down()
{
    IsDownMacro(event.xbutton.button == Button2);
}

#define ClickMacro(btn)                                       \
    GetDisplay(false);                                        \
    XTestFakeButtonEvent(display, (btn), True, CurrentTime);  \
    XFlush(display);                                          \
    usleep(10000); /* Required for linux */                   \
    XTestFakeButtonEvent(display, (btn), False, CurrentTime); \
    XFlush(display);                                          \
    XCloseDisplay(display);                                   \
    return true;

bool f_click_left()
{
    ClickMacro(Button1);
}

bool f_click_right()
{
    ClickMacro(Button3);
}

bool f_click_middle()
{
    ClickMacro(Button2);
}

#define DownUpMacro(btn, type)                                 \
    GetDisplay(false);                                         \
    XTestFakeButtonEvent(display, (btn), (type), CurrentTime); \
    XFlush(display);                                           \
    XCloseDisplay(display);                                    \
    return true;

bool f_mouse_left_down()
{
    DownUpMacro(Button1, True);
}

bool f_mouse_right_down()
{
    DownUpMacro(Button3, True);
}

bool f_mouse_middle_down()
{
    DownUpMacro(Button2, True);
}

bool f_mouse_left_up()
{
    DownUpMacro(Button1, False);
}

bool f_mouse_right_up()
{
    DownUpMacro(Button3, False);
}

bool f_mouse_middle_up()
{
    DownUpMacro(Button2, False);
}

bool f_is_mouse_swapped()
{
    return true; // TODO: It really depends on so many things.
}

bool f_mouse_scroll(int x, int y)
{
    GetDisplay(false);
    // TODO: horizontal scrolling
    for (int i = 0; i < y; ++i)
    {
        XTestFakeButtonEvent(display, Button4, True, CurrentTime);
        XFlush(display);
        usleep(10000);
        XTestFakeButtonEvent(display, Button4, False, CurrentTime);
        XFlush(display);
    }
    XCloseDisplay(display);
    return true;
}

bool f_press_key(bool is_ascii, int got)
{
    GetDisplay(false);
    KeyCode keyCode = is_ascii ? XKeysymToKeycode(display, got) : got;
    XTestFakeKeyEvent(display, keyCode, True, CurrentTime);
    XFlush(display);
    XTestFakeKeyEvent(display, keyCode, False, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
    return true;
}

bool f_key_down(bool is_ascii, int got)
{
    GetDisplay(false);
    KeyCode keyCode = is_ascii ? XKeysymToKeycode(display, got) : got;
    XTestFakeKeyEvent(display, keyCode, True, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
    return true;
}

bool f_key_up(bool is_ascii, int got)
{
    GetDisplay(false);
    KeyCode keyCode = is_ascii ? XKeysymToKeycode(display, got) : got;
    XTestFakeKeyEvent(display, keyCode, False, CurrentTime);
    XFlush(display);
    XCloseDisplay(display);
    return true;
}

int f_show_message_box(char *textBuf, char *captionBuf, int flags)
{
    return 0; // ?
}

int f_show_prompt()
{
    return 0; // ?
}