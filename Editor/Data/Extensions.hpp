#pragma once

struct Extension
{
    std::string Title;
    std::string Version;
    std::string Author;
    std::string Description;
    bool Enabled = false;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Title"] & Title;
        data["Version"] & Version;
        data["Author"] & Author;
        data["Description"] & Description;
        data["Enabled"] & Enabled;
    }
};

inline std::map<std::string, Extension> ExtensionsCache;

std::string GetExtensionID(const std::string &author, const std::string &title);
std::filesystem::path GetExtensionPath(const std::string &id);
std::filesystem::path GetExtensionPath(const std::string &author, const std::string &title);
std::filesystem::path GetExtensionConfig(const std::string &id);
std::filesystem::path GetExtensionConfig(const std::string &author, const std::string &title);
void LoadExtension(const std::filesystem::path &configPath);
void ReloadExtensions();
void CreateExtension(const std::filesystem::path &path);
