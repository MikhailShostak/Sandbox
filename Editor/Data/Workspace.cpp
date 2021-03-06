#include "Workspace.hpp"

#include "../Editors/Editor.hpp"

std::string GetFileTitle(const std::filesystem::path &path, bool showExtensionOnly)
{
    auto title = (showExtensionOnly ? path.extension() : path.filename()).generic_string();
    auto it = UnsavedFiles.find(path.generic_string());
    if(it != UnsavedFiles.end())
    {
        title.append("*");
    }
    return title + "###" + path.generic_string();
}

bool LoadFile(const std::filesystem::path &path)
{
    if (!std::filesystem::is_regular_file(path))
    {
        return false;
    }

    std::ifstream input(path, std::ios::binary);
    std::string str((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
    input.close();
    FileCache[path.generic_string()] = std::move(str);

    for(auto &editor : Editors)
    {
        editor.second->IndexFile(path);
    }

    return true;
}

bool LoadFolder(const std::filesystem::path &path)
{
    if (!std::filesystem::is_directory(path))
    {
        return false;
    }

    for (auto &entry : std::filesystem::recursive_directory_iterator(path))
    {
        LoadFile(entry.path());
    }

    return true;
}

void ReloadFiles()
{
    FileCache.clear();

    for(const auto &path : g_Config->Data.File.OpenedFiles)
    {
        LoadFile(path);
    }

    for (const auto &path : g_Config->Data.File.OpenedFolders)
    {
        LoadFolder(path);
    }
}

void ReindexFiles()
{
    if (!UnsavedFiles.empty())
    {
        PendingReindex = true;
        return;
    }
    PendingReindex = false;

    for (auto& [Name, Editor] : Editors)
    {
        Editor->ResetIndex();
    }
    ReloadFiles();
}

void OpenFile(const std::filesystem::path &path, bool remember)
{
    if(!std::filesystem::is_regular_file(path))
    {
        return;
    }

    auto it = ranges::find(g_Config->Data.File.OpenedFiles, path);
    if(it != g_Config->Data.File.OpenedFiles.end())
    {
        //TODO: select file
        return;
    }

    if(remember)
    {
        boost::remove_erase(g_Config->Data.File.RecentFiles, path);
        g_Config->Data.File.RecentFiles.push_back(path);
    }
    g_Config->Data.File.OpenedFiles.push_back(path);

    LoadFile(path);
}

void SaveFile(const std::filesystem::path &source, const std::filesystem::path &destination)
{
    auto sourcePathString = source.generic_string();
    bool saved = false;
    auto it = UnsavedFiles.find(sourcePathString);
    if(it != UnsavedFiles.end())
    {
        saved = it->second->SaveFile(source, destination);
        UnsavedFiles.erase(sourcePathString);
    }

    if(!saved) //TODO: Editors should handle this
    {
        std::ofstream output(destination, std::ios::binary);
        output << FileCache[sourcePathString];
        output.close();
    }
}

void SaveFile(const std::filesystem::path &path)
{
    SaveFile(path, path);
}

void CloseFile(const std::filesystem::path &path, bool reindex)
{
    boost::remove_erase(g_Config->Data.File.OpenedFiles, path);
    FileCache.erase(path.generic_string());

    if (reindex)
    {
        ReindexFiles();
    }
}

void CloseFiles(const std::vector<std::filesystem::path> &paths)
{
    std::for_each(paths.begin(), paths.end(), std::bind(&CloseFile, std::placeholders::_1, false));
    ReindexFiles();
}

void CloseAllFiles()
{
    g_Config->Data.File.OpenedFiles.clear();
    FileCache.clear();
    ReindexFiles();
}

void OpenFolder(const std::filesystem::path &path, bool remember)
{
    if(!std::filesystem::is_directory(path))
    {
        return;
    }

    auto it = ranges::find(g_Config->Data.File.OpenedFolders, path);
    if(it != g_Config->Data.File.OpenedFolders.end())
    {
        return;
    }

    if(remember)
    {
        boost::remove_erase(g_Config->Data.File.RecentFolders, path);
        g_Config->Data.File.RecentFolders.push_back(path);
    }

    g_Config->Data.File.OpenedFolders.push_back(path);
    
    LoadFolder(path);
}

void CloseFolder(const std::filesystem::path &path, bool reindex)
{
    boost::remove_erase(g_Config->Data.File.OpenedFolders, path);
    MapUtils::EraseIf(FileCache, [&path](const auto& pair) {
        return boost::starts_with(pair.first, path.generic_string());
    });

    if (reindex)
    {
        ReindexFiles();
    }
}

void CloseFolders(const std::vector<std::filesystem::path> &paths)
{
    std::for_each(paths.begin(), paths.end(), std::bind(&CloseFolder, std::placeholders::_1, false));
    ReindexFiles();
}

void CloseAllFolders()
{
    g_Config->Data.File.OpenedFolders.clear();
    FileCache.clear();
    ReindexFiles();
}

void OpenPath(const std::filesystem::path &path, bool remember)
{
    OpenFile(path, remember);
    OpenFolder(path, remember);
}

void OpenPaths(const std::vector<std::filesystem::path> &paths, bool remember)
{
    for(const auto &p : paths)
    {
        OpenFolder(p, remember);
    }
}

std::string &GetFileContent(const std::filesystem::path &path)
{
    return FileCache[path.generic_string()];
}
