#pragma once

#include <Foundation>

#include "AJSONObject.h"
#include "AJSONValue.h"
#include "AJSONError.h"

class AJSONParser
{
public:
    bool hasError() const { return e != AJSONErrorCode::Null; }
    AJSONErrorCode error() const { return e; }
    uint64_t errorLine() const { return line; }
    uint64_t errorOffset() const { return offset; }
    AJSONValue parse();
    virtual bool atBegin() const = 0;
    virtual bool atEnd() const = 0;
    virtual char take() = 0;
    virtual char peek() = 0;
    virtual void next() = 0;
    virtual void back() = 0;

private:

    uint64_t line = 0;
    uint64_t offset = 0;

    Stack<AJSONObject> objects;
    Stack<AJSONArray> arrays;

    String key;
    String string;
    bool hasDot = false;

    AJSONObject object;
    AJSONArray array;

    AJSONValue value;

    AJSONErrorCode e = AJSONErrorCode::Null;

    void skipWhiteSpaces();
    bool parseNumber();
    bool parseString();
    bool parseObject();
    bool parseArray();
    bool parseValue();
    bool parseTrueLiteral();
    bool parseFalseLiteral();
    bool parseNullLiteral();
};

#include "AJSONParser.inl"

class AJSONStringParser : public AJSONParser
{
public:
    AJSONStringParser(const String &data): data(data) {}
    bool hasSymbol() const { return position < data.size(); }
    bool atBegin() const { return position == 0; }
    bool atEnd() const { return position == data.size(); }
    char peek() { return data[position]; }
    char take() { ++position; return data[position - 1]; }
    void next() { ++position; }
    void back() { --position; }
private:
    const String &data;
    String::size_type position = 0;
};

class AJSONFileParser : public AJSONParser
{
public:
    template<typename PathType>
    AJSONFileParser(PathType &&path): file() { file.open(std::forward<PathType>(path), AFileOpenMode::ReadBinary); }
    ~AJSONFileParser() { if(file.isOpen()) file.close(); }
    bool hasSymbol() const { return !file.atEnd(); }
    bool atBegin() const { return file.atBegin(); }
    bool atEnd() const { return file.atEnd(); }
    char peek() { return file.peek(); }
    char take() { return file.take(); }
    void next() { file.skip(); }
    void back() { file.back(); }
private:
    AFile file;
};
