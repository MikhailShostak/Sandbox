#pragma once

#include <iostream>
#include <cstdarg>
#include <stdexcept>

#if ADebugBuild
#define BOOST_STACKTRACE_USE_ADDR2LINE
#endif
#include <boost/stacktrace.hpp>

#include "APlatform.h"

#if APlatformWindowsDesktop
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>
#endif

inline bool isBreakAvailable()
{
    return APlatformWindowsDesktop && IsDebuggerPresent();
}

inline bool triggerBreak()
{
    if (isBreakAvailable())
    {
        __debugbreak();
        return true;
    }
    else
    {
        return false;
    }
}

inline void __assert_function(bool expression, const char *file, const char *function, int line, const char *format, ...)
{
    if (!expression)
    {
        std::cout << "\r\n\r\nAssertion failure: ";

        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);

        std::cout << fmt::format("\r\n\r\n    {} at {}:{}\r\n\r\n\r\n", function, file, line);

        const auto &stack = boost::stacktrace::stacktrace();
        std::cout << fmt::format("{}\r\n", boost::stacktrace::detail::to_string(&stack.as_vector()[0], stack.size()));
        
        triggerBreak();
    }
}

#define AHasAsserts !AReleaseBuild

#if AHasAsserts
#define AAssert(expression, message, ...) __assert_function(bool(expression), __FILE__, AFunctionSignature, __LINE__, message, ##__VA_ARGS__)
#else
#define AAssert(expression, message, ...)
#endif
