#pragma once

#include <Foundation>

enum class AJSONWriteOption
{
    Comapct,
    Formated
};

enum class AJSONErrorCode : uint8_t
{
    Null = 0,
    EmptyDocument,
    ExtraSymbolsBeforeDocument,
    ExtraSymbolsAfterDocument,
    UnexpectedEnd,
    InvalidToken,
    InvalidKey,
    InvalidValue,
    InvalidArray,
    InvalidObject,
    MissingColon
};

class AJSONError final : public AError
{
public:
    AJSONError():AError() {}
    AJSONError(AJSONErrorCode code, uint64_t line, uint64_t offset):AError(uint64_t(code), String()), l(line), o(offset) {}
    AJSONErrorCode code() const { return AJSONErrorCode(getErrorCode()); }
    //void setCode(const AJSONErrorCode &code) { c = code; }
    uint64_t line() const { return l; }
    void setLine(uint64_t line) { l = line; }
    uint64_t offset() const { return o; }
    void setOffset(uint64_t offset) { o = offset; }
    String message() const;
private:
    uint64_t l = 0;
    uint64_t o = 0;
};

inline String AJSONError::message() const
{
    String base = "JSONError:" + std::to_string(l) + ":" + std::to_string(o) + ": ";
    base.append("\r\n\r\n");

    base.append(" JSON error: ");
    switch(AJSONErrorCode(getErrorCode()))
    {
    case AJSONErrorCode::EmptyDocument:
        return base + "Empty document\r\n";
    case AJSONErrorCode::ExtraSymbolsBeforeDocument:
        return base + "Extra symbols befor document, expected array '[' or object '{' token\r\n";
    case AJSONErrorCode::ExtraSymbolsAfterDocument:
        return base + "Extra symbols after document, expected end of file\r\n";
    case AJSONErrorCode::UnexpectedEnd:
        return base + "Undexpected end of document\r\n";
    case AJSONErrorCode::InvalidToken:
        return base + "Unknown token\r\n";
    case AJSONErrorCode::InvalidKey:
        return base + "Expected string key\r\n";
    case AJSONErrorCode::InvalidValue:
        return base + "Invalid value syntax\r\n";
    case AJSONErrorCode::InvalidArray:
        return base + "Invalid array syntax\r\n";
    case AJSONErrorCode::InvalidObject:
        return base + "Invalid object syntax\r\n";
    case AJSONErrorCode::MissingColon:
        return base + "Invalid token, expected colon\r\n";
    default:
        return "";
    }

    base.append("\r\n\r\n");

    base.append(fmt::format("        At line: {}\r\n", l));
    base.append(fmt::format("      At symbol: {}\r\n", o));

    base.append("\r\n\r\n");
}
