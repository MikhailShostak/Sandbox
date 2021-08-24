#include "Views.hpp"

#include "../Data/Workspace.hpp"

inline auto RootWindowFlags =
    //ImGuiWindowFlags_NoFocusOnAppearing |
    //ImGuiWindowFlags_NoBackground |
    ImGuiWindowFlags_MenuBar |
    ImGuiWindowFlags_NoDocking |
    ImGuiWindowFlags_NoTitleBar |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoBringToFrontOnFocus |
    ImGuiWindowFlags_NoNavFocus;

void ShowRootView(const std::function<void()> &callback)
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if(ImGui::Begin("Root", nullptr, RootWindowFlags))
    {
        ImGui::PopStyleVar(2);
        ImGuiID Workspace = ImGui::GetID("Workspace");
        ImGui::DockSpace(Workspace/*, {}, ImGuiDockNodeFlags_AutoHideTabBar*/);
        ShowMainMenu();
        if(OpenedFiles().size() == 0)
        {
            ImGui::SetNextWindowDockID(Workspace);
            ShowWelcomePage();
        }
        callback();
    }
    ImGui::End();
}
