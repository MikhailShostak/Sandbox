#pragma once

struct ExtensionsConfig
{
    using This = ExtensionsConfig;
    String ConfigFilename = {};
    String SearchDirectory = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["ConfigFilename"] & ConfigFilename;
        data["SearchDirectory"] & SearchDirectory;
    }

    void Initialize()
    {
    }
};
