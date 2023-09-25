#include <node_api.h>
#include <Windows.h>
#include <iostream>
#include <thread>
#include <vector>
#include "../main.h"

#define IDD_CUSTOM_DIALOG 101
#define IDC_EDIT 102

#define INPUT_SEND(input)                             \
    if (SendInput(1, &(input), sizeof(INPUT)) != 1)   \
    {                                                 \
        return false;                                 \
    }

LPCWSTR to_lpcwstr(char *text)
{
    int textLen = strlen(text) + 1;

    int textWLen = MultiByteToWideChar(CP_UTF8, 0, text, textLen, nullptr, 0);

    wchar_t *textW = new wchar_t[textWLen];

    MultiByteToWideChar(CP_UTF8, 0, text, textLen, textW, textWLen);

    return textW; // WARNING: DO NOT FORGET TO delete[] lpcwstr;
}

LPWSTR to_lpwstr(char *buffer)
{
    int len = MultiByteToWideChar(CP_UTF8, 0, buffer, -1, NULL, 0);
    LPWSTR lpwstr = new WCHAR[len];
    MultiByteToWideChar(CP_UTF8, 0, buffer, -1, lpwstr, len);
    return lpwstr; // WARNING: DO NOT FORGET TO delete[] lpwstr;
}

Point f_get_screen_size()
{
    Point p(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    return p;
}

Point f_get_cursor_position()
{
    POINT point;
    if (!GetCursorPos(&point))
    {
        Point p(-1, -1);
        return p;
    }
    Point p(point.x, point.y);
    return p;
}

bool f_set_cursor_position(int x, int y)
{
    return SetCursorPos(x, y);
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
    LPCWSTR textW = to_lpcwstr(textBuf);
    LPCWSTR captionW = to_lpcwstr(captionBuf);

    int res = MessageBoxW(NULL, textW, captionW, flags);

    delete[] textW;
    delete[] captionW;
    return res;
}

INT_PTR CALLBACK CustomMessageBoxProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            char buffer[256];
            LPWSTR lpwstr = to_lpwstr(buffer);
            LPCWSTR lpcwstr = to_lpcwstr(buffer);
            GetDlgItemTextW(hwndDlg, IDC_EDIT, lpwstr, sizeof(buffer));
            MessageBoxW(hwndDlg, lpcwstr, L"User Input", MB_OK | MB_ICONINFORMATION);
            delete[] lpwstr;
            delete[] lpcwstr;
            EndDialog(hwndDlg, 0);
        }
            return TRUE;

        case IDCANCEL:
            EndDialog(hwndDlg, 0);
            return TRUE;
        }
        break;
    }
    return FALSE;
}

int f_show_prompt()
{
    return DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_CUSTOM_DIALOG), NULL, CustomMessageBoxProc);
}