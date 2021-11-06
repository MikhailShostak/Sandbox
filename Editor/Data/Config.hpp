#pragma once

struct DataConfig
{
    struct
    {
        std::string ExternalTextEditor;

        template<typename T>
        void Serialize(T &&data)
        {
            data["ExternalTextEditor"] & ExternalTextEditor;
        }
    } General;

    struct
    {
        bool CombineFilesWithSameBasename = true;

        template<typename T>
        void Serialize(T &&data)
        {
            data["CombineFilesWithSameBasename"] & CombineFilesWithSameBasename;
        }
    } FileBrowser;

    struct
    {
        std::vector<std::filesystem::path> RecentFiles;
        std::vector<std::filesystem::path> OpenedFiles;
        std::vector<std::filesystem::path> RecentFolders;
        std::vector<std::filesystem::path> OpenedFolders;
        std::vector<std::filesystem::path> PinnedPaths;

        template<typename T>
        void Serialize(T &&data)
        {
            data["RecentFiles"] & RecentFiles;
            data["OpenedFiles"] & OpenedFiles;
            data["RecentFolders"] & RecentFolders;
            data["OpenedFolders"] & OpenedFolders;
            data["PinnedPaths"] & PinnedPaths;
        }
    } File;

    struct
    {
        std::string ConfigFilename = ".extension.yaml";
        std::string SearchDirectory = "Extensions";

        template<typename T>
        void Serialize(T &&data)
        {
            data["SearchDirectory"] & SearchDirectory;
        }
    } Extensions;

    struct FileType
    {
        std::string Title;
        std::string Editor;
        std::string Extensions;

        template<typename T>
        void Serialize(T &&data)
        {
            data["Title"] & Title;
            data["Editor"] & Editor;
            data["Extensions"] & Extensions;
        }
    };

    std::vector<FileType> FileTypes;


    template<typename T>
    void Serialize(T &&data)
    {
        data["General"] & General;
        data["FileBrowser"] & FileBrowser;
        data["File"] & File;
        data["FileTypes"] & FileTypes;
        data["Extensions"] & Extensions;
    }
};

inline DataConfig Config;
