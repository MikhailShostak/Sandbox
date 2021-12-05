#include "ADirectory.h"

inline Array<APathInfo> ADirectory::find(const String &keyword, const String &extension, AFindFilter filter) const
{
    Array<APathInfo> infos;
    auto it = begin();
    ++it;
    ++it;
    for (; it != end(); ++it)
    {
        APath fileName(std::move(*it));
        APathInfo info(_info.path() + fileName);
        if (info.isDirectory() && filter & AFindFilter::Directories)
        {
            if (!(!(filter & AFindFilter::Hidden || info.isVisible()) ||
                (!keyword.empty() && fileName.name().find(keyword) == String::size_type(-1)) ||
                (!extension.empty() && fileName.extension() != extension)))
            {
                infos.push_back(info);
            }
        }
        if (info.isFile() && filter & AFindFilter::Files)
        {
            bool failed = !(filter & AFindFilter::Hidden || info.isVisible());
            failed |= !keyword.empty() && fileName.name().find(keyword) == String::size_type(-1);
            failed |= !extension.empty() && fileName.extension() != extension;
            if (!failed)
            {
                infos.push_back(std::move(info));
            }
        }
    }
    return infos;
}

inline Array<APathInfo> ADirectory::findRecursively(const String &keyword, const String &extension, AFindFilter filter) const
{
    Array<APathInfo> infos;
    auto it = begin();
    ++it;
    ++it;
    for (; it != end(); ++it)
    {
        APath fileName(std::move(*it));
        APathInfo info(_info.path() + fileName);
        if (info.isDirectory())
        {
            if (filter & AFindFilter::Directories)
            {
                bool failed = !((filter & AFindFilter::Hidden) || info.isVisible())
                    || (!keyword.empty() && fileName.name().find(keyword) == String::size_type(-1))
                    || (!extension.empty() && fileName.extension() != extension);
                if (!failed)
                {
                    infos.push_back(info);
                }
            }
            ADirectory directory(std::move(info));
            ArrayUtils::Add(infos, directory.findRecursively(keyword, extension, filter));
        }
        else if (info.isFile() && filter & AFindFilter::Files)
        {
            bool failed = !((filter & AFindFilter::Hidden) || info.isVisible())
                || (!keyword.empty() && fileName.name().find(keyword) == String::size_type(-1))
                || (!extension.empty() && fileName.extension() != extension);
            if (!failed)
            {
                infos.push_back(std::move(info));
            }
        }
    }
    return infos;
}

inline Array<APath> ADirectory::findRelativeRecursively(const String &keyword, const String &extension, AFindFilter filter) const
{
    Array<APath> paths;
    Array<APathInfo> pathInfoList = findRecursively(keyword, extension, filter);
    for (auto &pathInfo : pathInfoList)
    {
        APath::SizeType lenght = info().path().size();

        auto it = pathInfo.path().begin();
        for (APath::SizeType i = 0; i < lenght; ++i)
        {
            ++it;
        }
        APath path = *it;
        ++it;
        while (it != pathInfo.path().end())
        {
            path.append(*it);
            ++it;
        }
        paths.push_back(std::move(path));
    }
    return paths;
}

#if APlatformWindowsDesktop

#ifndef STRING_TO_PTCHAR
#ifdef UNICODE
#define STRING_TO_PTCHAR(string) ((wchar_t *)ToUTF16(string).data())
#else
#define STRING_TO_PTCHAR(string) (string.data())
#endif
#endif

inline ADirectoryIterator::ADirectoryIterator(const ADirectory &directory, unsigned long position):data(), position(position), directory(directory)
{
    if (directory.isExists() && position != (unsigned int)(-1))
    {
        descriptor = FindFirstFile(STRING_TO_PTCHAR((directory.path().toString() + "\\*")), &data);
    }
    else
    {
        position = -1;
    }
}

inline ADirectoryIterator::~ADirectoryIterator()
{
    if (descriptor)
    {
        FindClose(descriptor);
    }
}

inline ADirectoryIterator &ADirectoryIterator::operator ++()
{
    if (FindNextFile(descriptor, &data) != 0)
    {
        name = ToUTF8((const char16_t*)(data.cFileName));
        ++position;
    }
    else
    {
        name.clear();
        position = -1;
    }
    return *this;
}

#else

inline ADirectoryIterator::ADirectoryIterator(const ADirectory &directory, unsigned long position):position(position), directory(directory)
{
    if (directory.isExists() && position != (unsigned int)(-1))
    {
        descriptor = opendir(directory.path().toString().data());
        if (descriptor)
        {
            data = readdir(descriptor);
        }
        else
        {
            position = -1;
        }
    }
    else
    {
        position = -1;
    }
}

inline ADirectoryIterator::~ADirectoryIterator()
{

}

inline ADirectoryIterator &ADirectoryIterator::operator ++()
{
    data = readdir(descriptor);
    if (data)
    {
        name = data->d_name;
        ++position;
    }
    else
    {
        name.clear();
        position = -1;
    }
    return *this;
}

#endif

inline const String &ADirectoryIterator::operator *() const
{
    return name;
}

inline APath ADirectoryIterator::path() const
{
    return directory.path() + name;
}
