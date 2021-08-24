#include "Views.hpp"

#include "../Data/Workspace.hpp"

std::filesystem::path PathToOpen;
void ShowPathList(const auto &list) {
    for(const auto &node : list)
    {
        auto f = node.as<std::filesystem::path>();
        if(ImGui::MenuItem(f.generic_string().data()))
        {
            PathToOpen = f;
        }
    }
}

void ShowPathListMenu(const char *title, const auto &list) {
    if (ImGui::BeginMenu(title, list.size() > 0))
    {
        ShowPathList(list);
        ImGui::EndMenu();
    }
}

void ShowMainMenu()
{
    if(ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ImGui::MenuItem("New...", nullptr, &File::DisplayNewDialog);
            ImGui::Separator();
            ImGui::MenuItem("Open File...", nullptr, &File::DisplayOpenFileDialog);
            ImGui::MenuItem("Open Folder...", nullptr, &File::DisplayOpenFolderDialog);
            auto recentFiles = RecentFiles();
            auto recentFolders = RecentFolders();
            if (ImGui::BeginMenu("Open Recent", recentFiles.size() > 0 || recentFolders.size() > 0))
            {
                if(recentFolders.size() > 0)
                {
                    ImGui::Text("Folders");
                    ShowPathList(recentFolders);
                }
                if(recentFiles.size() > 0 && recentFolders.size() > 0)
                {
                    ImGui::Separator();
                }
                if(recentFiles.size() > 0)
                {
                    ImGui::Text("Files");
                    ShowPathList(recentFiles);
                }
                ImGui::EndMenu();
            }
            ShowPathListMenu("Open Pinned", PinnedPaths());
            if(!PathToOpen.empty())
            {
                OpenPath(PathToOpen);
                PathToOpen.clear();
            }
            ImGui::Separator();
            ImGui::MenuItem("Save");
            ImGui::MenuItem("Save As...", nullptr, &File::DisplaySaveAsDialog);
            ImGui::MenuItem("Save All");
            ImGui::MenuItem("Close");
            ImGui::Separator();
            ImGui::MenuItem("Settings...", nullptr, &Settings::DisplaySettings);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            ImGui::MenuItem("File Browser", nullptr, &View::DisplayFileBrowser);
            ImGui::MenuItem("Output", nullptr, &View::DisplayConsole);
            ImGui::Separator();
            if (ImGui::BeginMenu("Debug"))
            {
                ImGui::MenuItem("ImGui Demo", nullptr, &Debug::DisplayImGuiDemo);
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}
