#pragma once

#include "System/Domain.hpp"
#include "Text/StringUtils.hpp"

namespace System
{

struct PackageIdentifier
{
    using This = PackageIdentifier;

    System::Domain Domain;
    String Name;

    PackageIdentifier() {}
    PackageIdentifier(const String &Package)
    {
        Array<String> labels = Str::Split(Package, ".");
        if (labels.size() > 2)
        {
            Name = std::move(labels.back());
            labels.resize(labels.size() - 1);
            Domain.Labels = labels | ranges::views::reverse | ranges::to_vector;
        }
    }
};

}
