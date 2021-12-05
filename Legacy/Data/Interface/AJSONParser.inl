#pragma once

#include "AJSONParser.h"

inline void AJSONParser::skipWhiteSpaces()
{
    while(!atEnd())
    {
        switch(take())
        {
        case '\n':
            ++line;
            offset = 0;
            break;
        case '\r': case '\t': case ' ':
            ++offset;
            break;
        default:
            back();
            return;
        }
    }
}

inline AJSONValue AJSONParser::parse()
{
    skipWhiteSpaces();

    switch(take())
    {
    case '{':
        if(parseObject())
            return value;
        else
            break;
        return value;
    case '[':
        if(parseArray())
            return value;
        else
            break;
    default:
        if(!atEnd())
            e = AJSONErrorCode::EmptyDocument;
        else
            e = AJSONErrorCode::ExtraSymbolsBeforeDocument;
        break;
    }
    return AJSONValue();
}

inline bool AJSONParser::parseNumber()
{
    string.clear();
    if(peek() == '-')
    {
        string.push_back(take());
    }
    switch(peek())
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        string.push_back(take());
        break;
    default:
        e = AJSONErrorCode::InvalidToken;
        return false;
    }

    while(!atEnd())
    {
        switch(peek())
        {
        case '.':
            if(hasDot)
            {
                e = AJSONErrorCode::InvalidToken;
                return false;
            }
        case 'e': case 'E':
            string.push_back(take());
            switch(peek())
            {
            case '-': case '+':
                string.push_back(take());
                break;
            default:
                break;
            }
            break;
        case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
            string.push_back(take());
            break;
        default:
            value = std::stod(string);
            return true;
        }
    }
    e = AJSONErrorCode::UnexpectedEnd;
    return false;
}

inline bool AJSONParser::parseString()
{
    string.clear();
    while(!atEnd())
    {
        switch(peek())
        {
        case '\\':
        {
            next();
            switch(peek())
            {
            case 'b':
                next();
                string.push_back('\b');
                break;
            case 'f':
                next();
                string.push_back('\f');
                break;
            case 'n':
                next();
                string.push_back('\n');
                break;
            case 'r':
                next();
                string.push_back('\r');
                break;
            case 't':
                next();
                string.push_back('\t');
                break;
            case 'u':
                next();
                string.append("\\u");
                break;
            default:
                string.push_back(take());
                break;
            }
            break;
        }
        case '"':
            next();
            value = string;
            return true;
        default:
            string.push_back(take());
        }
    }
    e = AJSONErrorCode::UnexpectedEnd;
    return false;
}

inline bool AJSONParser::parseObject()
{
    object.clear();
    objects.push_back(object);
    skipWhiteSpaces();
    if(peek() == '}')
    {
        next();
        value = objects.back();
        objects.pop_back();
        return true;
    }
    String key;
    while(!atEnd())
    {
        if(take() == '"')
        {
            if(parseString())
                key = string;
            else
                return false;
        }
        else
        {
            e = AJSONErrorCode::InvalidKey;
            return false;
        }
        skipWhiteSpaces();
        if(take() != ':')
        {
            e = AJSONErrorCode::MissingColon;
            return false;
        }
        if(parseValue())
        {
            objects.back().insert(key, value);
        }
        else
            return false;
        skipWhiteSpaces();
        switch(take())
        {
        case ',':
            skipWhiteSpaces();
            continue;
        case '}':
            value = objects.back();
            objects.pop_back();
            return true;
        default:
            e = AJSONErrorCode::InvalidToken;
            return false;
        }
    }
    e = AJSONErrorCode::UnexpectedEnd;
    return false;
}

inline bool AJSONParser::parseArray()
{
    array.clear();
    arrays.push_back(array);
    skipWhiteSpaces();
    if(peek() == ']')
    {
        next();
        value = arrays.back();
        arrays.pop_back();
        return true;
    }
    while(!atEnd())
    {
        if(parseValue())
        {
            arrays.back().push_back(value);
        }
        else
            return false;
        skipWhiteSpaces();
        switch(take())
        {
        case ',':
            skipWhiteSpaces();
            continue;
        case ']':
            value = arrays.back();
            arrays.pop_back();
            return true;
        default:
            e = AJSONErrorCode::InvalidToken;
            return false;
        }
    }
    e = AJSONErrorCode::UnexpectedEnd;
    return false;
}

inline bool AJSONParser::parseTrueLiteral()
{
    if(take() == 't' && take() == 'r' && take() == 'u' && take() == 'e')
    {
        value = true;
        return true;
    }
    e = AJSONErrorCode::InvalidToken;
    return false;
}

inline bool AJSONParser::parseFalseLiteral()
{
    if(take() == 'f' && take() == 'a' && take() == 'l' && take() == 's' && take() == 'e')
    {
        value = false;
        return true;
    }
    e = AJSONErrorCode::InvalidToken;
    return false;
}

inline bool AJSONParser::parseNullLiteral()
{
    if(take() == 'n' && take() == 'u' && take() == 'l' && take() == 'l')
    {
        value = nullptr;
        return true;
    }
    e = AJSONErrorCode::InvalidToken;
    return false;
}

inline bool AJSONParser::parseValue()
{
    value.clear();
    skipWhiteSpaces();
    switch(peek())
    {
    case '{':
        next();
        return parseObject();
    case '[':
        next();
        return parseArray();
    case '"':
        next();
        return parseString();
    case '-': case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
        return parseNumber();
    case 't':
        return parseTrueLiteral();
    case 'f':
        return parseFalseLiteral();
    case 'n':
        return parseNullLiteral();
    default:
        e = AJSONErrorCode::InvalidToken;
        return false;
    }
}
