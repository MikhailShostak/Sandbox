#pragma once

#include "APathInfo.h"

#if APlatformUnix
#include <dirent.h>
#endif

class ADirectory;

class ADirectoryIterator
{
    friend class ADirectory;

#if APlatformWindowsDesktop
    HANDLE descriptor = nullptr;
    WIN32_FIND_DATA data;
    unsigned long position = -1;
#else
    DIR *descriptor = nullptr;
    struct dirent *data = nullptr;
    unsigned long position = -1;
#endif

    const ADirectory &directory;
    String name;

    ADirectoryIterator(const ADirectory &directory, unsigned long position);

public:

    ~ADirectoryIterator();

    ADirectoryIterator &operator ++();

    bool operator ==(const ADirectoryIterator &iterator) const { return &directory == &iterator.directory && position == iterator.position; }
    bool operator !=(const ADirectoryIterator &iterator) const { return !(*this == iterator); }

    const String &operator *() const;

    APath path() const;

};

enum class AFindFilter
{
    Files = 0x1,
    Directories = 0x2,
    Hidden = 0x4,
    AllFiles = AFindFilter::Files | AFindFilter::Hidden,
    AllDirectories = AFindFilter::Directories | AFindFilter::Hidden,
    All = AFindFilter::Files | AFindFilter::Directories | AFindFilter::Hidden,
};

inline AFindFilter operator |(AFindFilter lmode, AFindFilter rmode)
{
    return AFindFilter(uint8_t(lmode) | uint8_t(rmode));
}

inline bool operator &(AFindFilter lmode, AFindFilter rmode)
{
    return uint8_t(lmode) & uint8_t(rmode);
}

class ADirectory
{

    APathInfo _info;

public:

    static const ADirectory &EmptyDirectory()
    {
        static ADirectory emptyDirectory;
        return emptyDirectory;
    }

    ADirectory() {}

    ADirectory(const ADirectory &) = default;
    ADirectory(ADirectory &&) = default;

    template<typename PathType>
    ADirectory(PathType &&path): _info(std::forward<PathType>(path))
    {
        if (!_info.isDirectory())
            _info.clear();
    }

    ADirectoryIterator begin() const { return ADirectoryIterator(*this, 0); }
    ADirectoryIterator end() const { return ADirectoryIterator(*this, -1); }

    Array<APathInfo> find(AFindFilter filter) const { return find(String(), String(), filter); }
    Array<APathInfo> find(const String &extension, AFindFilter filter) const { return find(String(), extension, filter); }
    Array<APathInfo> find(const String &keyword = String(), const String &extension = String(), AFindFilter filter = AFindFilter::All) const;

    Array<APathInfo> findRecursively(AFindFilter filter) const { return findRecursively(String(), String(), filter); }
    Array<APathInfo> findRecursively(const String &extension, AFindFilter filter) const { return findRecursively(String(), extension, filter); }
    Array<APathInfo> findRecursively(const String &keyword = String(), const String &extension = String(), AFindFilter filter = AFindFilter::All) const;

    Array<APath> findRelativeRecursively(AFindFilter filter) const { return findRelativeRecursively(String(), String(), filter); }
    Array<APath> findRelativeRecursively(const String &extension, AFindFilter filter) const { return findRelativeRecursively(String(), extension, filter); }
    Array<APath> findRelativeRecursively(const String &keyword = String(), const String &extension = String(), AFindFilter filter = AFindFilter::All) const;

    const APathInfo &info() const { return _info; }
    const APath &path() const { return info().path(); }

    bool isExists() const { return info().isExists(); }
    bool isVisible() const { return info().isVisible(); }

    ATime creationTime() const { return info().creationTime(); }
    ATime accessTime() const { return info().accessTime(); }
    ATime modificationTime() const { return info().modificationTime(); }

    ADirectory &operator =(const ADirectory &) = default;
    ADirectory &operator =(ADirectory &&) = default;

    explicit operator bool() const
    {
        return bool(info());
    }

};

class DirectoryEnumerator
{
public:
    const ADirectory &directory;

    DirectoryEnumerator(const ADirectory &directory):directory(directory) {}

    ADirectoryIterator begin() const
    {
        ADirectoryIterator it = directory.begin();
        ++it;
        ++it;
        return it;
    }

    ADirectoryIterator end() const
    {
        return directory.end();
    }
};
