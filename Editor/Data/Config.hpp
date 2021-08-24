#pragma once

namespace YAML {

template<>
struct convert<std::filesystem::path> {
    static Node encode(const std::filesystem::path& rhs)
    {
        return Node(rhs.generic_string());
    }

    static bool decode(const Node& node, std::filesystem::path& rhs)
    {
        rhs = node.as<std::string>();
        return true;
    }
};

}

inline YAML::Node Config;

inline YAML::Node FileConfig() { return Config["File"]; }
inline YAML::Node RecentFiles() { return FileConfig()["RecentFiles"]; }
inline YAML::Node OpenedFiles() { return FileConfig()["OpenedFiles"]; }

inline YAML::Node OpenedFolders() { return FileConfig()["OpenedFolders"]; }
inline YAML::Node RecentFolders() { return FileConfig()["RecentFolders"]; }

inline YAML::Node PinnedPaths() { return FileConfig()["PinnedPaths"]; }
