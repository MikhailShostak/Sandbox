#include "Workspace.hpp"

#include "../Editors/Editor.hpp"

std::string GetFileTitle(const std::filesystem::path &path)
{
    auto title = path.filename().generic_string();
    if(UnsavedFiles.contains(path.generic_string()))
    {
        title.append("*");
    }
    return title + "###" + path.generic_string();
}

void RemovePathFromNode(auto &node, const auto &path)
{
    auto it = std::find_if(node.begin(), node.end(), [&](auto v)
    {
        return v.as<std::filesystem::path>() == path;
    });
    if(it != node.end())
    {
        node.remove(std::distance(node.begin(), it));
    }
}

bool LoadFile(const std::filesystem::path &path)
{
    if (!std::filesystem::exists(path))
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

void ReloadFiles()
{
    FileCache.clear();

    for(const auto &node : OpenedFiles())
    {
        LoadFile(node.as<std::string>());
    }
}

void OpenFile(const std::filesystem::path &path, bool remember)
{
    if(!std::filesystem::is_regular_file(path))
    {
        return;
    }

    auto OpenedFilesNode = OpenedFiles();
    auto it = std::find_if(OpenedFilesNode.begin(), OpenedFilesNode.end(), [&](auto v)
    {
        return v.as<std::filesystem::path>() == path;
    });

    if(it != OpenedFilesNode.end())
    {
        //TODO: select file
        return;
    }

    if(remember)
    {
        auto RecentFilesNode = RecentFiles();
        RemovePathFromNode(RecentFilesNode, path);
        RecentFilesNode.push_back(path);
    }
    OpenedFilesNode.push_back(path);

    LoadFile(path);
}

void SaveFile(const std::filesystem::path &source, const std::filesystem::path &destination)
{
    auto sourcePathString = source.generic_string();
    bool saved = false;
    if(UnsavedFiles.contains(sourcePathString))
    {
        saved = UnsavedFiles[sourcePathString]->SaveFile(source, destination);
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
    auto OpenedFilesNode = OpenedFiles();
    RemovePathFromNode(OpenedFilesNode, path);

    FileCache.erase(path.generic_string());
}

void CloseFiles(const std::vector<std::filesystem::path> &paths)
{
    std::for_each(paths.begin(), paths.end(), &CloseFile);
}


void CloseAllFiles()
{
    OpenedFiles() = {};
    FileCache.clear();
}

void OpenFolder(const std::filesystem::path &path, bool remember)
{
    if(!std::filesystem::is_directory(path))
    {
        return;
    }

    auto OpenedFoldersNode = OpenedFolders();
    auto it = std::find_if(OpenedFoldersNode.begin(), OpenedFoldersNode.end(), [&](auto v)
    {
        return v.as<std::filesystem::path>() == path;
    });

    if(it != OpenedFoldersNode.end())
    {
        return;
    }

    if(remember)
    {
        auto RecentFoldersNode = RecentFolders();
        RemovePathFromNode(RecentFoldersNode, path);
        RecentFoldersNode.push_back(path);
    }

    OpenedFoldersNode.push_back(path);
    //TODO
}

void CloseFolder(const std::filesystem::path &path)
{
    auto OpenedFoldersNode = OpenedFolders();
    RemovePathFromNode(OpenedFoldersNode, path);
    //TODO
}

void CloseFolders(const std::vector<std::filesystem::path> &paths)
{
    std::for_each(paths.begin(), paths.end(), &CloseFolder);
}

void CloseAllFolders()
{
    OpenedFolders() = {};
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
