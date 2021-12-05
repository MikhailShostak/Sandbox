#pragma once

#include <Foundation.pch.hpp>
#include <Graphics>

#ifndef NOMINMAX
#  define NOMINMAX
#endif
#include <windows.h>

#include "Core/ACommonEvents.h"

extern HINSTANCE applicationInstance;
extern HINSTANCE applicationPrevInstance;
extern LPSTR arguments;
extern int consoleVisible;

#ifdef UNICODE
#define STRING_TO_PTCHAR(string) ((wchar_t *)ToUTF16(string).data())
#else
#define STRING_TO_PTCHAR(string) (string.data())
#endif
