#pragma once

namespace System
{
struct ExtensionInfo
{
    using This = ExtensionInfo;
    System::Version Version;
    System::PackageIdentifier Identifier;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
