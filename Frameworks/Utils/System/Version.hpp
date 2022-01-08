#pragma once

#include "Text/StringUtils.hpp"

namespace System
{

struct Version
{
    using This = Version;

    size_t Major = 0;
    size_t Minor = 0;
    size_t Patch = 0;
    String PreRelease;
    String MetaData;

    Version() {}
    Version(const String &Text)
    {
        Array<String> values = Str::Split(Text, "+");
        if (values.size() > 1)
        {
            MetaData = std::move(values[1]);
        }

        values = Str::Split(values[0], "-");
        if (values.size() > 1)
        {
            PreRelease = std::move(values[1]);
        }

        values = Str::Split(values[0], ".");
        if (values.size() > 2)
        {
            Patch = Str::To<size_t>(values[2]);
        }
        if (values.size() > 1)
        {
            Minor = Str::To<size_t>(values[1]);
        }
        Major = Str::To<size_t>(values[0]);
    }
};

}
