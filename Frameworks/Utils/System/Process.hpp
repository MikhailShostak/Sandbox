#pragma once

#pragma once

//#include <winsock2.h>
//#include <windows.h>
#include <boost/process.hpp>

namespace System
{

using Environment = boost::process::environment;

template<typename ...Args>
inline auto GetCurrentEnvironment()
{
    return boost::this_process::environment();
}

template<typename ...Args>
inline auto SearchPath(Args &&...args)
{
    return boost::process::search_path(std::forward<Args>(args)...);
}

template<typename ...Args>
inline auto Run(Args &&...args)
{
    return boost::process::child(std::forward<Args>(args)...);
}

}
