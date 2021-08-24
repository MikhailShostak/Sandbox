#pragma once

inline std::string ExtensionConfigFilename = ".extension.yaml";
inline std::string ExtensionsSearchDirectory = "Extensions";
inline std::map<std::string, YAML::Node> ExtensionsCache;

std::string GetExtensionID(const std::string &author, const std::string &title);
std::filesystem::path GetExtensionPath(const std::string &id);
std::filesystem::path GetExtensionPath(const std::string &author, const std::string &title);
std::filesystem::path GetExtensionConfig(const std::string &id);
std::filesystem::path GetExtensionConfig(const std::string &author, const std::string &title);
void LoadExtension(const std::filesystem::path &configPath);
void ReloadExtensions();
void CreateExtension(const std::filesystem::path &path);
void ReloadExtensionsFromConfig();
