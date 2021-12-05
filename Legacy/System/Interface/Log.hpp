#pragma once

#include "Str.hpp"

#include <chrono>

namespace Log
{

template<typename FormatType, typename ...Args>
inline void Print(FormatType &&format, Args &&...args)
{
	auto now = std::chrono::system_clock::now();
	fmt::print(Str::Format("[{:%Y-%m-%d %H:%M:%S}.{}] {}{}", now, std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() % 1000, format, "\r\n"), std::forward<Args>(args)...);

	/*std::cout << Str::Format("[{:%Y-%m-%d %H:%M:%S}.{}] {}\r\n",
		now,
		std::chrono::time_point_cast<std::chrono::milliseconds>(now).time_since_epoch().count() % 1000,
		Str::Format(format, std::forward<Args>(args)...)
	);*/
}

template<typename FormatType, typename MapType, typename ...Args>
inline void Print(FormatType &&format, Str::NamedArgs<MapType> &&map, Args &&...args)
{
	Print(Str::Format(std::forward<FormatType>(format), std::forward<Str::NamedArgs<MapType>>(map), std::forward<Args>(args)...));
}

}
