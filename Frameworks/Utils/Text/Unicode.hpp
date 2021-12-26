#pragma once

#include <utf8.h>
#include <utf8/cpp17.h>

inline std::string ToUTF8(std::u16string_view string) { return utf8::utf16to8(string); }
inline std::string ToUTF8(std::u32string_view string) { return utf8::utf32to8(string); }

inline std::u16string ToUTF16(std::string_view string) { return utf8::utf8to16(string); }
inline std::u16string ToUTF16(std::u32string_view string) { return utf8::utf8to16(ToUTF8(string)); }

inline std::u32string ToUTF32(std::string_view string) { return utf8::utf8to32(string); }
inline std::u32string ToUTF32(std::u16string_view string) { return utf8::utf8to32(ToUTF8(string)); }
