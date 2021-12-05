#pragma once
#include "String.h"
#include "winuser.h"

class Clipboard
{
public:
    static bool getData(String &text)
    {
        if (!IsClipboardFormatAvailable(CF_TEXT || CF_UNICODETEXT))
        {
            return false;
        }

        if (!OpenClipboard(nullptr))
        {
            return false;
        }

        HGLOBAL handle = GetClipboardData(CF_UNICODETEXT);
        if (handle != nullptr)
        {
            LPTSTR data = static_cast<LPTSTR>(GlobalLock(handle));
            if (data != nullptr)
            {
                text = String((char*)data);
                GlobalUnlock(handle);
                CloseClipboard();
                return true;
            }
        }

        handle = GetClipboardData(CF_TEXT);
        if (handle != nullptr)
        {
            LPTSTR data = static_cast<LPTSTR>(GlobalLock(handle));
            if (data != nullptr)
            {
                text = String((char *)data);
                GlobalUnlock(handle);
                CloseClipboard();
                return true;
            }
        }
        CloseClipboard();

        return false;
    }

    static void setData(const String &text) //TODO: implement substrings
    {
        HWND window = GetActiveWindow();
        if (!OpenClipboard(window))
        {
            return;
        }

        EmptyClipboard();

        size_t memsize = (text.size() + 1) * sizeof(char16_t); //TODO: fix char*
        HGLOBAL handle = GlobalAlloc(GMEM_MOVEABLE, memsize);
        if (handle == nullptr)
        {
            CloseClipboard();
            return;
        }

        LPTSTR data = static_cast<LPTSTR>(GlobalLock(handle));
        memcpy(data, text.data(), memsize);
        GlobalUnlock(handle);
        SetClipboardData(CF_UNICODETEXT, handle);
        SetClipboardData(CF_TEXT, handle);

        CloseClipboard();
    }
};
