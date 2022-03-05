#pragma once

#include <portable-file-dialogs.h>

#include "Text/String.hpp"

namespace System::Notifications
{

inline void Info(const String& Title, const String& Text)
{
    pfd::notify(Title, Text, pfd::icon::info);
}

inline void Warning(const String& Title, const String& Text)
{
    pfd::notify(Title, Text, pfd::icon::info);
}

inline void Error(const String& Title, const String& Text)
{
    pfd::notify(Title, Text, pfd::icon::info);
}

}
