#pragma once

struct EditorConfig
{
    using This = EditorConfig;
    GeneralConfig General = {};
    FileBrowserConfig FileBrowser = {};
    FileConfig File = {};
    ExtensionsConfig Extensions = {};
    Array<FileType> FileTypes = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["General"] & General;
        data["FileBrowser"] & FileBrowser;
        data["File"] & File;
        data["Extensions"] & Extensions;
        data["FileTypes"] & FileTypes;
    }

    void Initialize()
    {
    }
};
