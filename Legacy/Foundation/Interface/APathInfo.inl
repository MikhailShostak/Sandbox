#include "APathInfo.h"

#if APlatformWindowsDesktop

#ifndef STRING_TO_PTCHAR
#ifdef UNICODE
#define STRING_TO_PTCHAR(string) ((wchar_t *)ToUTF16(string).data())
#else
#define STRING_TO_PTCHAR(string) (string.data())
#endif
#endif

inline APathInfo APathInfo::getFromRelativePath(const APath &path)
{
    constexpr static int MAX_ENVIRONMENT_VARIABLE_SIZE = 32767;
    char variable[MAX_ENVIRONMENT_VARIABLE_SIZE];
    GetEnvironmentVariableA("PATH", variable, MAX_ENVIRONMENT_VARIABLE_SIZE);

    Array<String> paths;
    boost::split(paths, String(variable), boost::is_any_of(";"));
    for (const String &p : paths)
    {
        APathInfo pathInfo(p + APathSeparator + path);
        if (pathInfo.isExists())
        {
            return pathInfo;
        }
    }

    return APathInfo();
}

inline void APathInfo::update()
{
    exists = GetFileAttributesEx(STRING_TO_PTCHAR(cache), GetFileExInfoStandard, &attributes) != 0;
}

inline bool APathInfo::isVisible() const
{
    if(!isExists())
    {
        return false;
    }
    return !(attributes.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN);
}

inline bool APathInfo::isSymbolicLink() const
{
    if(!isExists())
    {
        return false;
    }
    return (attributes.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT) != 0;
}

inline bool APathInfo::isFile() const
{
    if(!isExists())
    {
        return false;
    }
    return !(attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);;
}

inline bool APathInfo::isDirectory() const
{
    if(!isExists())
    {
        return false;
    }
    return (attributes.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0;
}

inline ATime APathInfo::creationTime() const
{
    if(!isExists())
    {
        return 0;
    }

    ULARGE_INTEGER ull;
    ull.LowPart = attributes.ftCreationTime.dwLowDateTime;
    ull.HighPart = attributes.ftCreationTime.dwHighDateTime;
    return ull.QuadPart / 10000000ULL - 11644473600ULL;
}

inline ATime APathInfo::accessTime() const
{
    if(!isExists())
    {
        return 0;
    }

    ULARGE_INTEGER ull;
    ull.LowPart = attributes.ftLastAccessTime.dwLowDateTime;
    ull.HighPart = attributes.ftLastAccessTime.dwHighDateTime;
    return ull.QuadPart / 10000000ULL - 11644473600ULL;
}

inline ATime APathInfo::modificationTime() const
{
    if(!isExists())
    {
        return 0;
    }

    ULARGE_INTEGER ull;
    ull.LowPart = attributes.ftLastWriteTime.dwLowDateTime;
    ull.HighPart = attributes.ftLastWriteTime.dwHighDateTime;
    return ull.QuadPart / 10000000ULL - 11644473600ULL;
}

#else

#include <unistd.h>

inline void APathInfo::update()
{
    //return ; access(cache.toUtf8().data(), F_OK) != -1;
    exists = lstat(cache.toUtf8().data(), &attributes) == 0;
}

inline bool APathInfo::isVisible() const
{
    return cache.first() == '.';
}

inline bool APathInfo::isSymbolicLink() const
{
    if(!isExists())
    {
        return false;
    }
    return S_ISLNK(attributes.st_mode);
}

inline bool APathInfo::isFile() const
{
    if(!isExists())
    {
        return false;
    }
    return S_ISREG(attributes.st_mode);
}

inline bool APathInfo::isDirectory() const
{
    if(!isExists())
    {
        return false;
    }
    return S_ISDIR(attributes.st_mode);
}

inline ATime APathInfo::creationTime() const
{
    if(!isExists())
    {
        return 0;
    }
    return attributes.st_ctime;
}

inline ATime APathInfo::accessTime() const
{
    if(!isExists())
    {
        return 0;
    }
    return attributes.st_atime;
}

inline ATime APathInfo::modificationTime() const
{
    if(!isExists())
    {
        return 0;
    }
    return attributes.st_mtime;
}

#endif

inline bool APathInfo::make()
{
    if(isExists())
    {
        return false;
    }

    APath fullpath = path().root();
    for(auto name : path())
    {
        fullpath.append(name);
        APathInfo info(fullpath);
        if(!info)
        {
#if APlatformWindowsDesktop
            if(!CreateDirectoryW(LPCWSTR(info.path().toString().data()), nullptr))
#else
            if(mkdir(info.path().toString().toUtf8().data(), S_IRWXU | S_IRWXG | S_IROTH | S_IRWXO) != 0)
#endif
            {
                return false;
            }
        }
    }
    update();
    return true;
}

inline bool APathInfo::copy(const APath &destination) const
{
    APathInfo info(destination);
    return _copy(*this, APathInfo(destination));
}

inline bool APathInfo::copy(APath &&destination) const
{
    return _copy(*this, APathInfo(std::move(destination)));
}

inline bool APathInfo::_copy(const APathInfo &source, const APathInfo &destination) const
{
    if(!source.isExists() || destination.isExists())
    {
        return false;
    };
    String destinationCachedPath = destination.path().toString();
#if APlatformWindowsDesktop
    if(!CopyFileW(LPCWSTR(source.cache.data()), LPCWSTR(destinationCachedPath.data()), false))
#else

#endif
    {
        return false;
    }
    return true;
}

inline bool APathInfo::rename(const APath &destination)
{
    if(destination.isRelative())
    {
        APathInfo destinationPathInfo(path().directory() + destination);
        APathInfo destinationDirectory(destinationPathInfo.path().directory());
        if(!destinationDirectory)
        {
            if(!destinationDirectory.make())
            {
                return false;
            }
        }
        return _rename(*this, std::move(destinationPathInfo));
    }
    else
    {
        return _rename(*this, APathInfo(destination));
    }
}

inline bool APathInfo::rename(APath &&destination)
{
    if(destination.isRelative())
    {
        APathInfo destinationPathInfo(path().directory() + destination);
        APathInfo destinationDirectory(destinationPathInfo.path().directory());
        if(!destinationDirectory)
        {
            if(!destinationDirectory.make())
            {
                return false;
            }
        }
        return _rename(*this, std::move(destinationPathInfo));
    }
    else
    {
        return _rename(*this, APathInfo(std::move(destination)));
    }
}

inline bool APathInfo::_rename(APathInfo &source, APathInfo &&destination)
{
    if(!source.isExists() || destination.isExists())
    {
        return false;
    }

    String destinationCachedPath = destination.path().toString();
#if APlatformWindowsDesktop
    if(!MoveFileW(LPCWSTR(cache.data()), LPCWSTR(destinationCachedPath.data())))
#else
    if(std::rename(path().toString().toUtf8().data(), destinationCachedPath.toUtf8().data()) != 0)
#endif
    {
        return false;
    }

    source._path = std::move(destination.path());
    source.cache = std::move(destinationCachedPath);
    source.update();
    return true;
}

inline bool APathInfo::remove()
{
    if(!isExists())
    {
        return false;
    }
#if APlatformWindowsDesktop
    if(isDirectory())
    {
        return RemoveDirectoryW(LPCWSTR(cache.data())) == TRUE;
    }
    else
    {
        return DeleteFileW(LPCWSTR(cache.data())) == TRUE;
    }
#else
    return std::remove(cache.toUtf8().data()) == 0;
#endif
}
