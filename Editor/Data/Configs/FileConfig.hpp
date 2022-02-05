#pragma once

struct FileConfig
{
    using This = FileConfig;
    Array<System::Path> RecentFiles = {};
    Array<System::Path> RecentFolders = {};
    Array<System::Path> OpenedFiles = {};
    Array<System::Path> OpenedFolders = {};
    Array<System::Path> PinnedPaths = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["RecentFiles"] & RecentFiles;
        data["RecentFolders"] & RecentFolders;
        data["OpenedFiles"] & OpenedFiles;
        data["OpenedFolders"] & OpenedFolders;
        data["PinnedPaths"] & PinnedPaths;
    }

    void Initialize()
    {
    }
};
