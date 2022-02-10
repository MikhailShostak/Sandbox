#include "../Views.hpp"

#include "../../Data/Workspace.hpp"

void ShowWelcomePage()
{
    if(ImGui::Begin("Welcome Page", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("Pinned Paths");
        for(const auto &path : g_Config->Data.File.PinnedPaths)
        {
            auto absolutePath = std::filesystem::absolute(path);
            if(ImGui::Selectable(absolutePath.string().data()))
            {
                OpenPath(absolutePath);
            }
        }

        ImGui::Separator();

        ImGui::Text("Recent Folders");
        for(const auto &path : g_Config->Data.File.RecentFolders)
        {
            auto absolutePath = std::filesystem::absolute(path);
            if(ImGui::Selectable(absolutePath.string().data()))
            {
                OpenFolder(absolutePath);
            }
        }

        ImGui::Separator();

        ImGui::Text("Recent Files");
        for(const auto &path : g_Config->Data.File.RecentFiles)
        {
            auto absolutePath = std::filesystem::absolute(path);
            if(ImGui::Selectable(absolutePath.string().data()))
            {
                OpenFile(absolutePath);
            }
        }
    }
    ImGui::End();
}
