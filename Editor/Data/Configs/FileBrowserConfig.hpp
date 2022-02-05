#pragma once

struct FileBrowserConfig
{
    using This = FileBrowserConfig;
    bool CombineFilesWithSameBasename = {};

    virtual ~FileBrowserConfig() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["CombineFilesWithSameBasename"] & CombineFilesWithSameBasename;
    }

    void Initialize()
    {
    }
};
