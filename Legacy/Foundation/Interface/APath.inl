#pragma once

#include <sys/stat.h>

#include "APath.h"

#if APlatformWindowsDesktop
#   ifndef NOMINMAX
#       define NOMINMAX
#   endif
#   include <windows.h>
#else
#   if APlatformApple
#       include <unistd.h>
#       include <libproc.h>
#   endif
#endif

inline String APath::allocApplicationModule()
{
#if APlatformApple
    char buffer[PROC_PIDPATHINFO_MAXSIZE];
    proc_pidpath(getpid(), buffer, sizeof(buffer));
    return buffer;
#elif APlatformWindowsDesktop
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    return buffer;
#endif
}

inline APath APath::applicationPath()
{
    static APath path = allocApplicationModule();
    return path;
}

inline APath APath::applicationDirectory()
{
    static APath path = applicationPath().directory();
    return path;
}

#if APlatformWindowsDesktop
#include "Userenv.h"
#include "Processthreadsapi.h"
inline APath APath::getUserDirectory()
{
    char buffer[MAX_PATH] = { 0 };
    DWORD bufferSize = MAX_PATH;
    GetUserProfileDirectoryA(GetCurrentProcessToken(), reinterpret_cast<LPSTR>(buffer), &bufferSize);
    return String(buffer);
}
#endif

inline APath APath::workingDirectory()
{
#if APlatformWindowsDesktop
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, reinterpret_cast<LPSTR>(buffer));
    return String(buffer);
#else
    char buffer[PATH_MAX];
    getcwd(buffer, PATH_MAX);
    return String(buffer);
#endif
}

inline bool APath::changeWorkingDirectory(const String &path)
{
#if APlatformWindowsDesktop
    return SetCurrentDirectoryA(LPSTR(path.data())) == TRUE;
#else
    return chdir(path.toUtf8().data()) == 0;
#endif
}

/*inline void APath::changeDirectory(const String &path)
{
    String absolute = absolutePath(path);
    if(isExists(absolute) && isDirectory(absolute))
    {
        d->directory = absolute;
    }
}*/

/*inline String APath::absolutePathFromDirectory(const APath &base)
{
    if(isAbsolute())
        return path;

    String absolute = base;
    String::SizeType left = 0;
    String::SizeType right = 0;

    while(true)
    {
        right = path.indexOf(pathSeparator, left);
        String dir = path.mid(left, right - left);

        if(dir.size() == 2 && dir[0] == '.' && dir[1] == '.')
        {
            String::SizeType cut = lastSeparator(absolute);
            if(cut == String::SizeType(-1) || cut == 0)
                absolute.clear();
            else
                absolute = absolute.mid(0, cut);
        }
        else if(!(dir.size() == 1 && dir[0] == '.'))
            absolute.append(pathSeparator + dir);

        if(right == String::SizeType(-1))
            break;

        left = right + 1;
    }

    if(absolute.size() == 0)
#if APlatformWindowsDesktop
        return "C:\\";
#else
        return '/';
#endif
    else
        return absolute;
}*/

inline APath::APath(const char *path)
{
    if(path)
    {
        setPath(path);
    }
    else
    {
        clear();
    }
}


inline APath::APath(const String &path)
{
    if(!path.empty())
    {
        setPath(std::move(path));
    }
    else
    {
        clear();
    }
}


inline APath::APath(String &&path)
{
    if(!path.empty())
    {
        setPath(std::move(path));
    }
    else
    {
        clear();
    }
}

inline const Array<String> &APath::source() const
{
    return _source;
}

inline String APath::toString() const
{
    if(_root == 0)
    {
        return boost::join(_source, String(1, APathSeparator));
    }
    else
    {
#if APlatformWindowsDesktop
        return String(1, _root) + String(":\\") + boost::join(_source, String(1, APathSeparator));
#else
        return APathSeparator + boost::join(_source, String(1, APathSeparator));
#endif
    }
}

inline String APath::toUnixPathString() const
{
    if(_root == 0)
    {
        return boost::join(_source, String(1, '/'));
    }
    else
    {
#if APlatformWindowsDesktop
        return String(1, _root) + ":/" + boost::join(_source, String(1, '/'));
#else
        return APathSeparator + boost::join(_source, String(1, '/'));
#endif
    }
}

inline void APath::setPath(const String &path)
{
    if(path == "..")
    {
        _source.push_back(path);
        return;
    }

    Math::Templates::Range<String::size_type> range;

#if APlatformWindowsDesktop
    if(path.size() > 2 && (('a' <= path[0] && path[0] <= 'z') || ('A' <= path[0] && path[0] <= 'Z')) && path[1] == ':' && (path[2] == '/' || path[2] == '\\'))
    {
        _root = toupper(path[0]);
        range.lowest = 3;
    } else if(path.size() > 0 && path[0] == '/') {
        _root = 'C';
        range.lowest = 1;
    }
#else
    if(path.size() > 0 && path[0] == APathSeparator)
    {
        _root = APathSeparator;
        range.lowest = 1;
    }
#endif
    else
    {
        _root = 0;
    }

    while(range.lowest < path.size())
    {
        for(SizeType i = range.lowest; i < path.size(); ++i)
        {
            range.highest = i;
            if(path[i] == '/' || path[i] == '\\')
            {
                break;
            }
        }
        if(range.highest == path.size() - 1 && !(path[range.highest] == '/' || path[range.highest] == '\\'))
        {
            range.highest = path.size();
        }
        String name = path.substr(range.lowest, range.getLength());
        if(!name.empty() && name != ".")
        {
            if(name == ".." && _source.size() > 0 && _source.back() != "..")
            {
                _source.pop_back();
            }
            else
            {
                _source.push_back(std::move(name));
            }
        }
        range.lowest = range.highest + 1;
    }
}

inline String APath::name() const
{
    if(source().empty())
        return String();

    return source().back();
}

inline String APath::baseName() const
{
    if(source().empty())
        return String();

    return source().back().substr(0, source().back().find_last_of('.'));
}

inline String APath::extension() const
{
    if(source().empty())
        return String();

    String::size_type lastDot = source().back().find_last_of('.');

    if(lastDot == String::size_type(-1))
    {
        return String();
    }

    return source().back().substr(lastDot + 1);
}

inline void APath::setExtension(const String &extension)
{
    if(source().empty())
        return;

    SizeType index = source().back().find_last_of('.');
    if(index == InvalidSize)
    {
        _source.back().append(".");
        _source.back().append(extension);
    }
    else
    {
        _source.back() = source().back().substr(0, index + 1) + extension;
    }
}

inline bool APath::isAbsolute() const
{
    return _root != 0;
}

inline bool APath::isRelative() const
{
    return _root == 0;
}

inline bool APath::isRoot() const
{
    return isAbsolute() && _source.size() == 0;
}

inline void APath::append(const APath &path)
{
    AAssert(&path != this, "Path couldn't append self");

    for(auto name : path._source)
    {
        if(name == "..")
        {
            up();
        }
        else
        {
            _source.push_back(name);
        }
    }
}

inline void APath::up()
{
    if(isRoot())
        return;

    if(source().empty())
    {
        _source.push_back("..");
        return;
    }

    auto it = end();
    it--;

    if(*it == "..")
    {
        _source.push_back(*it);
    }
    else
    {
        _source.pop_back();
    }
}

inline void APath::upTo(const Iterator &iterator)
{
    auto it = iterator;
    it++;
    _source.erase(it, _source.end());
}

inline void APath::upToRoot()
{
    _source.clear();
}

inline void APath::clear()
{
#if APlatformWindowsDesktop
    _root = 'C';
#else
    _root = '/';
#endif
    _source.clear();
}

inline APath APath::directory() const
{
    if(source().empty())
        return APath("..");

    auto end = _source.end();
    end--;

    APath path(_root);
    if(*end == "..")
    {
        path._source = _source;
        path._source.push_back("..");
    }
    else
    {
        for(auto it = _source.begin(); it != end; it++)
            path._source.push_back(*it);
    }
    return path;
}

inline APath APath::root() const
{
    return APath(_root);
}

inline APath APath::resolveWithDirectory(const APath &directory) const
{
    if(isRoot())
    {
        return directory;
    }

    if(isAbsolute())
    {
        return *this;
    }

    return directory + *this;
}

inline APath APath::resolveWithExtension(const String &extension) const
{
    APath path = *this;
    path.setExtension(extension);
    return path;
}

namespace std
{
    template<>
    struct hash<APath>
    {
        size_t operator()(const APath &path) const { return std::hash<String>()(path.toString()); }
    };
}

inline std::ostream &operator <<(std::ostream &stream, const APath &path)
{
    return stream << path.toString();
}
