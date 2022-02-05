#pragma once

struct GeneralConfig
{
    using This = GeneralConfig;
    String ExternalTextEditor = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["ExternalTextEditor"] & ExternalTextEditor;
    }

    void Initialize()
    {
    }
};
