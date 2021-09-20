#include "Workspace.hpp"

#include "../Editors/Editor.hpp"

std::string GetFileTitle(const std::filesystem::path &path)
{
    auto title = path.filename().generic_string();
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
    if (!std::filesystem::is_regular_file(path))
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

    for(const auto &path : Config.File.OpenedFiles)
    {
        LoadFile(path);
    }

    for (const auto &path : Config.File.OpenedFolders)
    {
        LoadFolder(path);
    }
}

void OpenFile(const std::filesystem::path &path, bool remember)
{
    if(!std::filesystem::is_regular_file(path))
    {
        return;
    }

    auto it = ranges::find(Config.File.OpenedFiles, path);
    if(it != Config.File.OpenedFiles.end())
    {
        //TODO: select file
        return;
    }

    if(remember)
    {
        boost::remove_erase(Config.File.RecentFiles, path);
        Config.File.RecentFiles.push_back(path);
    }
    Config.File.OpenedFiles.push_back(path);

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

void CloseFile(const std::filesystem::path &path)
{
    boost::remove_erase(Config.File.OpenedFiles, path);
    FileCache.erase(path.generic_string());
}

void CloseFiles(const std::vector<std::filesystem::path> &paths)
{
    std::for_each(paths.begin(), paths.end(), &CloseFile);
}


void CloseAllFiles()
{
    Config.File.OpenedFiles.clear();
    FileCache.clear();
}

void OpenFolder(const std::filesystem::path &path, bool remember)
{
    if(!std::filesystem::is_directory(path))
    {
        return;
    }

    auto it = ranges::find(Config.File.OpenedFolders, path);
    if(it != Config.File.OpenedFolders.end())
    {
        return;
    }

    if(remember)
    {
        boost::remove_erase(Config.File.RecentFolders, path);
        Config.File.RecentFolders.push_back(path);
    }

    Config.File.OpenedFolders.push_back(path);
    
    LoadFolder(path);
}

void CloseFolder(const std::filesystem::path &path)
{
    boost::remove_erase(Config.File.OpenedFolders, path);
    //TODO
}

void CloseFolders(const std::vector<std::filesystem::path> &paths)
{
    std::for_each(paths.begin(), paths.end(), &CloseFolder);
}

void CloseAllFolders()
{
    Config.File.OpenedFolders.clear();
    //TODO
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
