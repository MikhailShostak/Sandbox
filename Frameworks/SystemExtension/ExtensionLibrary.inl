#pragma once

namespace System
{

template<typename InterfaceType>
inline void ExtensionLibrary<InterfaceType>::Load()
{
    constexpr const char *PathPrefix =
#if BOOST_OS_WINDOWS
        nullptr;
#else
        "lib";
#endif
    constexpr const char *PathExtension =
#if BOOST_OS_WINDOWS
        ".dll";
#elif BOOST_OS_MACOS || BOOST_OS_IOS
        ".dylib";
#else
        ".so";
#endif
    for (const auto &entry : System::DirectoryIterator(Root))
    {
        String filename = entry.path().filename().string();
        if ((!PathPrefix || boost::starts_with(filename, PathPrefix)) && boost::ends_with(filename, PathExtension))
        {
            System::Extension<InterfaceType> e;
            e.Load(entry.path());
            Extensions.push_back(std::move(e));
        }
    }
}

template<typename InterfaceType>
inline void ExtensionLibrary<InterfaceType>::Unload()
{

}

}
