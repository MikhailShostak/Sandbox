#include "../Views.hpp"

#include "../../Data/Config.hpp"
#include "../../Data/Workspace.hpp"

void ShowWelcomePage()
{
    if(ImGui::Begin("Welcome Page", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoMove))
    {
        ImGui::Text("Recent Folders");
        for(const auto &node : RecentFolders())
        {
            auto path = node.as<std::filesystem::path>();
            if(ImGui::Selectable(path.string().data()))
            {
                OpenFolder(path);
            }
        }

        ImGui::Separator();

        ImGui::Text("Recent Files");
        for(const auto &node : RecentFiles())
        {
            auto path = node.as<std::filesystem::path>();
            if(ImGui::Selectable(path.string().data()))
            {
                OpenFile(path);
            }
        }
    }
    ImGui::End();
}
