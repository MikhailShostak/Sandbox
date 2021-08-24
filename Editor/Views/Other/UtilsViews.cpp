#include "../Views.hpp"

std::filesystem::path RetrieveDirectory(const std::filesystem::path &path) { return std::filesystem::is_directory(path) ? path : path.parent_path(); }

namespace Utils
{

namespace Menu
{

void CopyFullPath(const std::filesystem::path &path)
{
    if (!ImGui::MenuItem("Copy Full Path"))
    {
        return;
    }

    ImGui::SetClipboardText(path.generic_string().data());
}

void ShowInExplorer(const std::filesystem::path &path)
{
    if (!ImGui::MenuItem("Show In Explorer"))
    {
        return;
    }

    std::string command = fmt::format("explorer \"{}\"", (std::filesystem::current_path() / RetrieveDirectory(path)).make_preferred().string());
    std::cout << command << std::endl;
    boost::process::system(command);
}

void OpenTerminalHere(const std::filesystem::path &path)
{
    if (!ImGui::MenuItem("Open Terminal Here"))
    {
        return;
    }

    std::string command = fmt::format("wt -w 0 -d \"{}\"", (std::filesystem::current_path() / RetrieveDirectory(path)).make_preferred().string());
    std::cout << command << std::endl;
    boost::process::system(command);
}

}

}
