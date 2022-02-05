#pragma once

struct FileType
{
    using This = FileType;
    String Title = {};
    String Editor = {};
    String Extensions = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Title"] & Title;
        data["Editor"] & Editor;
        data["Extensions"] & Extensions;
    }

    void Initialize()
    {
    }
};
