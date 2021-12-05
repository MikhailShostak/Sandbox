#pragma once

#include <fstream>

#include "String.h"
#include "APath.h"

enum class AFileOpenMode
{
    Append			= std::ios_base::app,
    AtEnd			= std::ios_base::ate,
    Binary			= std::ios_base::binary,
    Read			= std::ios_base::in,
    Write			= std::ios_base::out,
    Truncate		= std::ios_base::trunc,
    ReadWrite		= AFileOpenMode::Read | AFileOpenMode::Write,
    ReadBinary		= AFileOpenMode::Read | AFileOpenMode::Binary,
    WriteBinary		= AFileOpenMode::Write | AFileOpenMode::Binary,
    ReadWriteBinary	= AFileOpenMode::ReadWrite | AFileOpenMode::Binary
};

enum class AFileSeekDirection
{
    Begin   = std::ios_base::beg,
    Current = std::ios_base::cur,
    End     = std::ios_base::end
};

class AFile final
{

    mutable std::fstream d;
    APath _path;
    String cachedPath;

public:
    using PositionType = std::fstream::pos_type;
    using OffsetType = std::fstream::off_type;
    using Seek = std::ios_base::seekdir;
    using SizeType = std::streamsize;

    static bool isExists(const String &path) { return std::ifstream(path).good(); }

    AFile() {}
    AFile(const APath &path);
    AFile(APath &&path);
    AFile(const APath &path, AFileOpenMode mode);
    AFile(APath &&path, AFileOpenMode mode);
    ~AFile();

    const APath &path() const;
    void setPath(const APath &path);
    void setPath(APath &&path);

    bool open(AFileOpenMode mode);
    bool open(const APath &path, AFileOpenMode mode);
    bool open(APath &&path, AFileOpenMode mode);
    void close() { d.flush(); d.close(); }

    bool isOpen() const { return d.is_open(); }
    bool isGood() const { return d.good(); }
    bool isBad() const { return d.bad(); }
    bool isFail() const { return d.fail(); }

    bool atBegin() const { return d.tellg() == PositionType(0); }
    bool atEnd() const { d.ignore(); if (d.eof()) { return true; } d.unget(); return false; }

    std::fstream &stream() { return d; }
    const std::fstream &stream() const { return d; }

    uint8_t peek() { return d.peek(); }
    uint8_t take() { return d.get(); }

    Array<uint8_t> read(SizeType size);
    Array<uint8_t> readLine();
    Array<uint8_t> readAll();

    void back() { d.unget(); }

    void skip() { d.ignore(); }
    void skip(SizeType size) { d.ignore(size); }

    void write(const char *buffer, SizeType size) { d.write(buffer, size); }
    void write(const int8_t *buffer, SizeType size) { d.write(reinterpret_cast<const char*>(buffer), size); }
    void write(const uint8_t *buffer, SizeType size) { d.write(reinterpret_cast<const char*>(buffer), size); }
    void write(const Array<uint8_t> &array) { d.write((char*)array.data(), array.size()); }

    PositionType readPosition() const { return d.tellg(); }
    AFile &setReadPosition(PositionType position) { d.seekg(position); return *this; }
    AFile &setReadPosition(AFileSeekDirection direction, OffsetType offset) { d.seekg(offset, (Seek)direction); return *this; }

    PositionType readSize() const {
        PositionType position = d.tellg();
        d.seekg(0, std::ios::end);
        PositionType size = d.tellg();
        d.seekg(position, std::ios::beg);
        return size;
    }

    PositionType writePosition() const { return d.tellp(); }
    AFile &setWritePosition(PositionType position) { d.seekp(position); return *this; }
    AFile &setWritePosition(AFileSeekDirection direction, OffsetType offset) { d.seekp(offset, (Seek)direction); return *this; }

    PositionType writeSize() const {
        PositionType position = d.tellp();
        d.seekp(0, std::ios::end);
        PositionType size = d.tellp();
        d.seekp(position, std::ios::beg);
        return size;
    }

    template<typename Type>
    AFile &operator >>(Type &value)
    {
        d >> value;
        return *this;
    }

    template<typename Type>
    AFile &operator <<(const Type &value)
    {
        d << value;
        return *this;
    }

    inline AFile &operator <<(const char *string)
    {
        d << string;
        return *this;
    }

};

template<>
inline AFile &AFile::operator >>(AFile &file)
{
    char byte;
    d >> byte;
    file.d << byte;
    return *this;
}

template<>
inline AFile &AFile::operator <<(const String &string)
{
    d << string;
    return *this;
}

template<>
inline AFile &AFile::operator <<(const AFile &file)
{
    char byte;
    file.d >> byte;
    d << byte;
    return *this;
}

inline AFile::AFile(const APath &path)
{
    setPath(path);
}

inline AFile::AFile(APath &&path)
{
    setPath(std::move(path));
}

inline AFile::AFile(const APath &path, AFileOpenMode mode)
{
    open(path, mode);
}

inline AFile::AFile(APath &&path, AFileOpenMode mode)
{
    open(std::move(path), mode);
}

inline AFile::~AFile()
{
    if(isOpen())
    {
        close();
    }
}

inline const APath &AFile::path() const
{
    return _path;
}

inline void AFile::setPath(const APath &path)
{
    if(isOpen())
    {
        close();
    }
    _path = path;
    cachedPath = _path.toString();
}

inline void AFile::setPath(APath &&path)
{
    if(isOpen())
    {
        close();
    }
    _path = std::move(path);
    cachedPath = _path.toString();
}

inline bool AFile::open(const APath &path, AFileOpenMode mode)
{
    setPath(path);
    return open(mode);
}

inline bool AFile::open(APath &&path, AFileOpenMode mode)
{
    setPath(std::move(path));
    return open(mode);
}

inline bool AFile::open(AFileOpenMode mode)
{
    if(isOpen())
    {
        close();
    }
    d.open(cachedPath, std::ios_base::openmode(mode));
    return isOpen();
}

inline Array<uint8_t> AFile::read(SizeType size)
{
    Array<uint8_t> array;
    array.resize(size);
    d.read((char*)array.data(), size);
    return array;
}

inline Array<uint8_t> AFile::readLine()
{
    std::string string;
    std::getline(d, string);
    return Array<uint8_t>(string.begin(), string.end());
}

inline Array<uint8_t> AFile::readAll()
{
    PositionType position = d.tellg();
    d.seekg(0, d.end);
    PositionType size = d.tellg() - position;
    d.seekg(position, d.beg);
    Array<uint8_t> array;
    array.resize(size);
    d.read((char*)array.data(), size);
    return array;
}

inline AFileOpenMode operator |(AFileOpenMode lmode, AFileOpenMode rmode)
{
    return AFileOpenMode(uint8_t(lmode) | uint8_t(rmode));
}

inline bool operator &(AFileOpenMode lmode, AFileOpenMode rmode)
{
    return uint8_t(lmode) & uint8_t(rmode);
}

