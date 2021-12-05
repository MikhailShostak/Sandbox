#pragma once

#include "String.h"
#include "ADelegate.h"

class APath
{

    char _root = 0;
    Array<String> _source;

    static String allocApplicationModule();

    explicit APath(char root):_root(root) {}

public:

    static APath applicationPath();
    static APath applicationDirectory();
    static APath getUserDirectory();
    static APath workingDirectory();
    static bool changeWorkingDirectory(const String &path);

    static APath RootPath()
    {
        static APath rootPath;
        return rootPath;
    }

    using SizeType = Array<String>::size_type;

    using Iterator = Array<String>::iterator;
    using ConstIterator = Array<String>::const_iterator;
    using ReverseIterator = Array<String>::reverse_iterator;
    using ConstReverseIterator = Array<String>::const_reverse_iterator;

    constexpr static SizeType InvalidSize = -1;

    APath() { clear(); }
    APath(const char *path);
    APath(const String &path);
    APath(String &&path);

    Iterator begin() { return _source.begin(); }
    ConstIterator begin() const { return _source.begin(); }
    Iterator end() { return _source.end(); }
    ConstIterator end() const { return _source.end(); }

    ReverseIterator rbegin() { return _source.rbegin(); }
    ConstReverseIterator rbegin() const { return _source.rbegin(); }
    ReverseIterator rend() { return _source.rend(); }
    ConstReverseIterator rend() const { return _source.rend(); }

    String getObjectDescription() const
    {
        return toString();
    }

    const Array<String> &source() const;

    void setPath(const String &path);

    SizeType size() const { return source().size(); }

    String name() const;
    String baseName() const;
    String extension() const;
    void setExtension(const String &extension);

    bool isAbsolute() const;
    bool isRelative() const;
    bool isRoot() const;

    void append(const APath &path);
    void up();
    void upTo(const Iterator &iterator);
    void upToRoot();

    void clear();

    APath directory() const;
    APath root() const;

    APath resolveWithDirectory(const APath &directory) const;
    APath resolveWithExtension(const String &extension) const;

    String toString() const;
    String toUnixPathString() const;

    APath &operator +=(const APath &path) { append(path); return *this; }
    APath &operator /=(const APath &path) { append(path); return *this; }

    operator String() const { return toString(); }

private:

    String::size_type lastSeparator() const;

};

inline APath operator +(const APath &lpath, const APath &rpath)
{
    APath path(lpath);
    path.append(rpath);
    return path;
}

inline APath operator +(const char *lpath, const APath &rpath)
{
    return APath(lpath) + rpath;
}

inline APath operator +(const APath &lpath, const char *rpath)
{
    return lpath + APath(rpath);
}

inline APath operator +(const String &lpath, const APath &rpath)
{
    return APath(lpath) + rpath;
}

inline APath operator +(const APath &lpath, const String &rpath)
{
    return lpath + APath(rpath);
}

/*template<typename StringType>
inline APath operator +(StringType &&lpath, const APath &rpath)
{
    APath path(std::forward<StringType>(lpath));
    path.append(rpath);
    return path;
}

template<typename StringType>
inline APath operator +(const APath &lpath, StringType &&rpath)
{
    APath path(lpath);
    path.append(std::forward<StringType>(rpath));
    return path;
}*/

inline APath operator /(const APath &lpath, const APath &rpath)
{
    return lpath + rpath;
}

/*template<typename StringType>
inline APath operator /(StringType &&lpath, const APath &rpath)
{
    return std::forward<StringType>(lpath) + rpath;
}

template<typename StringType>
inline APath operator /(const APath &lpath, StringType &&rpath)
{
    return lpath + std::forward<StringType>(rpath);
}*/

inline bool operator <(const APath &lpath, const APath &rpath)
{
    auto lit = lpath.begin();
    auto rit = rpath.begin();
    for(; lit != lpath.end() && rit != rpath.end(); ++lit, ++rit)
    {
        if(*lit < *rit)
        {
            return true;
        }
    }
    return false;
}

inline bool operator <=(const APath &lpath, const APath &rpath)
{
    auto lit = lpath.begin();
    auto rit = rpath.begin();
    for(; lit != lpath.end() && rit != rpath.end(); ++lit, ++rit)
    {
        if(*lit <= *rit)
        {
            return true;
        }
    }
    return false;
}

inline bool operator >(const APath &lpath, const APath &rpath)
{
    auto lit = lpath.begin();
    auto rit = rpath.begin();
    for(; lit != lpath.end() && rit != rpath.end(); ++lit, ++rit)
    {
        if(*lit > *rit)
        {
            return true;
        }
    }
    return false;
}

inline bool operator >=(const APath &lpath, const APath &rpath)
{
    auto lit = lpath.begin();
    auto rit = rpath.begin();
    for(; lit != lpath.end() && rit != rpath.end(); ++lit, ++rit)
    {
        if(*lit >= *rit)
        {
            return true;
        }
    }
    return false;
}

inline bool operator ==(const APath &lpath, const APath &rpath)
{
    auto lit = lpath.begin();
    auto rit = rpath.begin();
    if(lpath.size() != rpath.size())
    {
        return false;
    }
    for(; lit != lpath.end() && rit != rpath.end(); ++lit, ++rit)
    {
        if(*lit != *rit)
        {
            return false;
        }
    }
    return lit == lpath.end() && rit == rpath.end();
}

inline bool operator !=(const APath &lpath, const APath &rpath)
{
    auto lit = lpath.begin();
    auto rit = rpath.begin();
    if(lpath.size() != rpath.size())
    {
        return true;
    }
    for(; lit != lpath.end() && rit != rpath.end(); ++lit, ++rit)
    {
        if(*lit == *rit)
        {
            return false;
        }
    }
    return lit != lpath.end() || rit != rpath.end();
}

#include "APlatform.h"

#if APlatformWindowsDesktop
constexpr char APathSeparator = '\\';
#else
constexpr char APathSeparator = '/';
#endif
