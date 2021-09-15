#include "Extensions.hpp"

#include "Config.hpp"

std::string GetExtensionID(const std::string &author, const std::string &title)
{
    return author + "." + title;
}

std::filesystem::path GetExtensionPath(const std::string &id)
{
    return std::filesystem::current_path() / Config.Extensions.SearchDirectory / id;
}

std::filesystem::path GetExtensionPath(const std::string &author, const std::string &title)
{
    return GetExtensionPath(GetExtensionID(author, title));
}

std::filesystem::path GetExtensionConfig(const std::string &id)
{
    return GetExtensionPath(id) / Config.Extensions.ConfigFilename;
}

std::filesystem::path GetExtensionConfig(const std::string &author, const std::string &title)
{
    return GetExtensionConfig(GetExtensionID(author, title));
}

void LoadExtension(const std::filesystem::path &configPath)
{
    Extension ext;
    Serialization::FromFile(configPath, ext);
    ExtensionsCache.insert({configPath.parent_path().generic_string(), std::move(ext)});
}

void ReloadExtensions()
{
    ExtensionsCache.clear();
    if(!std::filesystem::is_directory(Config.Extensions.SearchDirectory))
    {
        return;
    }
    for(const auto &entry: std::filesystem::directory_iterator{Config.Extensions.SearchDirectory})
    {
        std::filesystem::path configPath = entry.path() / Config.Extensions.ConfigFilename;
        if(!std::filesystem::exists(configPath))
        {
            continue;
        }

        LoadExtension(configPath);
    }
}

void CreateExtension(const std::filesystem::path &path)
{
    std::filesystem::create_directories(path.parent_path());

    std::ofstream file(path);
    file.close();
}

