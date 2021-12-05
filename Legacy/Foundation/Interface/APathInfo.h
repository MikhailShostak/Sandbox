#pragma once

#include "APath.h"
#include "ATime.h"

class APathInfo final
{

    APath _path;
    String cache;

#if APlatformWindowsDesktop
    WIN32_FILE_ATTRIBUTE_DATA attributes;
#else
    struct stat attributes;
#endif

    bool exists = false;

    static String absolutePathFromDirectory(const String &path, const String &directory = APath::workingDirectory().toString());

    static time_t modificationTime(const String &path);

public:

    static APathInfo getFromRelativePath(const APath &path);

    APathInfo() {}

    APathInfo(const APathInfo &info) = default;
    APathInfo(APathInfo &&info) = default;

    APathInfo(const char *path) { setPath(APath(path)); }
    APathInfo(const APath &path) { setPath(path); }
    APathInfo(APath &&path) { setPath(std::move(path)); }

    const APath &path() const { return _path; }
    template<typename PathType>
    void setPath(PathType &&path) {
        _path = std::forward<PathType>(path);
        cache = _path.toString();
        update();
    }

    void update();

    String name() const { return path().name(); }
    String baseName() const { return path().baseName(); }
    String extension() const { return path().extension(); }

    bool isExists() const { return exists; }
    bool isVisible() const;
    bool isSymbolicLink() const;
    bool isFile() const;
    bool isDirectory() const;

    ATime creationTime() const;
    ATime accessTime() const;
    ATime modificationTime() const;

    void clear()
    {
        setPath(APath());
    }

    bool make();
    bool remove();

    bool copy(const APath &path) const;
    bool copy(APath &&path) const;
    bool rename(const APath &path);
    bool rename(APath &&destination);

    APathInfo &operator =(const APathInfo &info) = default;
    APathInfo &operator =(APathInfo &&info) = default;

    APathInfo &operator =(const APath &path)
    {
        setPath(path);
        return *this;
    }

    APathInfo &operator =(APath &&path)
    {
        setPath(std::move(path));
        return *this;
    }

    explicit operator bool() const
    {
        return isExists();
    }

private:

    bool _copy(const APathInfo &source, const APathInfo &destination) const;
    bool _rename(APathInfo &source, APathInfo &&destination);

};
