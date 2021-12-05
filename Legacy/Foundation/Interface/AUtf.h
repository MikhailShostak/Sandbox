#pragma once

#include <iterator>

#include <utf8.h>

inline std::u16string encodeFromUtf8ToUtf16(const std::string &string)
{
    std::u16string result;
    utf8::utf8to16(string.begin(), string.end(), back_inserter(result));
    return result;
}

inline std::u32string encodeFromUtf8ToUtf32(const std::string &string)
{
    std::u32string result;
    utf8::utf8to32(string.begin(), string.end(), back_inserter(result));
    return result;
}

inline std::string encodeFromUtf16ToUtf8(const std::u16string &string)
{
    std::string result;
    utf8::utf16to8(string.begin(), string.end(), back_inserter(result));
    return result;
}

inline std::string encodeFromUtf32ToUtf8(const std::u32string &string)
{
    std::string result;
    utf8::utf32to8(string.begin(), string.end(), back_inserter(result));
    return result;
}

inline std::u16string encodeFromUtf32ToUtf16(const std::u32string &string)
{
    return encodeFromUtf8ToUtf16(encodeFromUtf32ToUtf8(string));
}

inline std::u32string encodeFromUtf16ToUtf32(const std::u16string &string)
{
    return encodeFromUtf8ToUtf32(encodeFromUtf16ToUtf8(string));
}
