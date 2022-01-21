
namespace UI
{

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

void ViewWindowComponent::Draw()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (ImGui::Begin(fmt::format("Root{}", fmt::ptr(this)).data(), nullptr, RootWindowFlags))
    {
        ImGui::PopStyleVar(2);
        ImGuiID Workspace = ImGui::GetID(fmt::format("Workspace{}", fmt::ptr(this)).data());
        ImGui::DockSpace(Workspace/*, {}, ImGuiDockNodeFlags_AutoHideTabBar*/);
        for (auto& view : Views)
        {
            view->Draw();
        }
    }
    ImGui::End();
}

}
