#include "../Views.hpp"

#include "../../Data/Config.hpp"

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

void ShowInExternalTextEditor(const std::filesystem::path &path)
{
    if (!ImGui::MenuItem("Show In External Text Editor"))
    {
        return;
    }

    if (!std::filesystem::is_regular_file(path))
    {
        return;
    }

    auto node = GeneralConfig()["ExternalTextEditor"];
    if(!node.IsDefined())
    {
        return;
    }

    auto editor = node.as<std::string>();
    if(editor.empty())
    {
        return;
    }

    auto executable = boost::process::search_path(editor);
    std::string arg = std::filesystem::path(path).make_preferred().string();
    std::cout << executable << " " << arg << std::endl;
    boost::process::spawn(executable, arg);
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

void ShowDefaultFileOperations(const std::filesystem::path &path)
{
    CopyFullPath(path);
    ShowInExplorer(path);;
    ShowInExternalTextEditor(path);
    OpenTerminalHere(path);
}

}

}
