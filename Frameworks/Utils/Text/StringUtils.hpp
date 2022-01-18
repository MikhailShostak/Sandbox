#pragma once

#include "Containers/Array.hpp"
#include "Text/String.hpp"

namespace Str
{

inline bool Contains(const String &string, const String &substring)
{
    return boost::contains(string, substring);
}

inline bool Contains(const String &string, const Array<String> &substrings)
{
    for (const auto& substring : substrings)
    {
        if (!Contains(string, substring))
        {
            return false;
        }
    }
    return true;
}

inline size_t ContainsAny(const String &string, const Array<String> &substrings)
{
    for (size_t i = 0; i < substrings.size(); ++i)
    {
        if (Contains(string, substrings[i]))
        {
            return i;
        }
    }
    return ArrayUtils::InvalidIndex;
}

inline String Quote(const String &string)
{
    return "\"" + string + "\"";
}

template<typename ContainerType, typename SeparatorType>
inline auto Join(ContainerType &&strings, SeparatorType &&separator)
{
    return boost::join(std::forward<ContainerType>(strings), std::forward<SeparatorType>(separator));
}

template<typename StringType, typename SeparatorType>
inline auto Split(StringType &&string, SeparatorType &&separators, bool empty = false)
{
    Array<std::remove_cv_t<std::remove_reference_t<StringType>>> strings;
    if(empty)
    {
        boost::split(strings, string, boost::is_any_of(separators));
    }
    else
    {
        boost::split(strings, boost::trim_copy_if(string, boost::is_any_of(separators)), boost::is_any_of(separators));
        boost::remove_erase_if(strings, [](auto& value) { return value.empty(); });
    }
    return strings;
}

template<typename NumberType>
inline NumberType To(std::string_view string)
{
    static_assert(std::is_arithmetic_v<NumberType>);

    NumberType value;
    if constexpr (std::is_same_v<NumberType, bool>)
    {
        static Array<String> tokens = {
            "t", "true", "y", "yes"
        };
        if (boost::find(tokens, boost::to_lower_copy(string)) != tokens.end())
        {
            value = true;
        }
        else
        {
            std::uintmax_t number = 0;
            std::from_chars(string.data(), string.data() + string.size(), number);
            value = static_cast<bool>(number);
        }
    }
    else
    {
        std::from_chars(string.data(), string.data() + string.size(), value);
    }
    return value;
}

template<typename NumberType>
inline String ToString(NumberType number)
{
    static_assert(std::is_arithmetic_v<NumberType>);
    return std::to_string(number);
}

inline String ToLowerCase(const String &string)
{
    String result;
    result.resize(string.size());
    std::transform(string.begin(), string.end(), result.begin(), ::tolower);
    return result;
}

inline String ToFirstLowerCase(const String &string)
{
    String result = string;
    result[0] = std::tolower(string[0]);
    return result;
}

inline String ToUpperCase(const String &string)
{
    String result;
    result.resize(string.size());
    std::transform(string.begin(), string.end(), result.begin(), ::toupper);
    return result;
}

inline String ToFirstUpperCase(const String &string)
{
    String result = string;
    result[0] = std::toupper(string[0]);
    return result;
}

template<typename Functor>
inline String GetNextAvailableName(const String &basename, Functor &&predicate)
{
    if (predicate(basename))
    {
        return basename;
    }

    for (size_t i = 2; i < std::numeric_limits<size_t>::max(); ++i)
    {
        String nextName = basename + Str::ToString(i);
        if (predicate(nextName))
        {
            return nextName;
        }
    }

    return basename + Str::ToString(std::numeric_limits<size_t>::max());
}

template<typename ContainerType, typename Functor>
inline String GetNextAvailableName(const String &name, const ContainerType &container, Functor &&predicate)
{
    return GetNextAvailableName(name, [&](auto &&n) {
        return ranges::find_if(container, [&](auto &&item) {
            return !predicate(item, n);
        }) == container.end();
    });
}

}

/*AString toCapitalizedCase() const
{
    AString string = toLowerCase();
    string[0] = std::toupper(string[0]);
    return string;
}

AString toTitleCase() const
{
    AString string;
    auto it = begin();
    if (it != end())
    {
        string.append(AChar(std::toupper(*it)));
        it++;
    }
    while (it != end())
    {
        if (std::isspace(*it) != 0 || std::ispunct(*it) != 0)
        {
            string.append(AChar(std::tolower(*it)));
            it++;
            if (it != end())
            {
                string.append(AChar(std::toupper(*it)));
            }
            else
            {
                break;
            }
        }
        else
        {
            string.append(AChar(std::tolower(*it)));
        }
        it++;
    }
    return string;
}

AString toCamelCase() const
{
    AString temp = toTitleCase();
    AString string;

    for (auto &symbol : temp)
    {
        if (symbol == ' ' || symbol == '\r' || symbol == '\n')
        {
            continue;
        }

        string.append(symbol);
    }

    return string;
}*/
