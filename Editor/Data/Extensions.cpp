#include "Extensions.hpp"

#include "Config.hpp"

std::string GetExtensionID(const std::string &author, const std::string &title)
{
    return author + "." + title;
}

std::filesystem::path GetExtensionPath(const std::string &id)
{
    return std::filesystem::current_path() / ExtensionsSearchDirectory / id;
}

std::filesystem::path GetExtensionPath(const std::string &author, const std::string &title)
{
    return GetExtensionPath(GetExtensionID(author, title));
}

std::filesystem::path GetExtensionConfig(const std::string &id)
{
    return GetExtensionPath(id) / ExtensionConfigFilename;
}

std::filesystem::path GetExtensionConfig(const std::string &author, const std::string &title)
{
    return GetExtensionConfig(GetExtensionID(author, title));
}

void LoadExtension(const std::filesystem::path &configPath)
{
    YAML::Node config = YAML::LoadFile(configPath.generic_string());
    ExtensionsCache.insert({configPath.parent_path().generic_string(), config});


}

void ReloadExtensions()
{
    ExtensionsCache.clear();
    for(const auto &entry: std::filesystem::directory_iterator{ExtensionsSearchDirectory})
    {
        std::filesystem::path configPath = entry.path() / ExtensionConfigFilename;
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


void ReloadExtensionsFromConfig()
{
    auto node = Config["Extensions"]["SearchDirectory"];
    if(node.IsDefined())
    {
        ExtensionsSearchDirectory = Config["Extensions"]["SearchDirectory"].as<std::string>();
    }
    ReloadExtensions();
}
