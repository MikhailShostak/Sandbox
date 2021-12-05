#pragma once

#include <Foundation>

#include <range/v3/action.hpp>

#include <format>
#include <fmt/args.h>
#include <fmt.pch.hpp>

namespace Str
{
	
template<std::size_t N>
ranges::subrange<char const*> CharRange(char const (&sz)[N])
{
	return {&sz[0], &sz[N-1]};
}

template<typename T>
inline T *GetData(T *chars)
{
	return chars;
}

template<typename T>
inline auto GetData(T &&string)
{
	return string.data();
}

template<typename T>
inline const T &ToUTF8(const T &string)
{
	return string;
}

inline std::string ToUTF8(const String &string)
{
	return string;
}

template<typename T>
struct NamedArgs
{
	T &map;
};

template<typename T>
inline NamedArgs<T> Args(T &&map)
{
	return { map };
}

template<typename ...Args>
inline auto Format(Args &&...args)
{
	return fmt::format(std::forward<Args>(args)...);
}

template<typename FormatType, typename MapType, typename ...Args>
inline auto Format(FormatType &&format, NamedArgs<MapType> &named_args, Args &&...args)
{
	fmt::dynamic_format_arg_store<fmt::format_context> store;
	for(const auto &pair : named_args.map)
	{
		auto str = ToUTF8(pair.first);
		auto a = fmt::arg(GetData(str), pair.second);
		store.push_back(a);
	}
	return fmt::vformat(std::forward<FormatType>(format), store, std::forward<Args>(args)...);
}

template<typename FormatType, typename MapType, typename ...Args>
inline auto Format(FormatType &&format, NamedArgs<MapType> &&named_args, Args &&...args)
{
	fmt::dynamic_format_arg_store<fmt::format_context> store;
	for(const auto &pair : named_args.map)
	{
		auto str = ToUTF8(pair.first);
		auto a = fmt::arg(GetData(str), pair.second);
		store.push_back(a);
	}
	return fmt::vformat(std::forward<FormatType>(format), store, std::forward<Args>(args)...);
}

}
