#pragma once

namespace ECS
{

void ImGuiSystem::OnLoad(EScene& scene)
{

};

void ImGuiSystem::OnUnload(EScene& scene)
{

};

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

void ShowMainMenu()
{

}

void Draw(EScene &scene)
{
    ShowMainMenu();
    /*if (Config.File.OpenedFiles.size() == 0)
    {
        ImGui::SetNextWindowDockID(Workspace);
        ShowWelcomePage();
    }*/

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (ImGui::Begin("Content"))
    {
        auto BasePos = ImGui::GetCursorPos();
        auto images = scene.Registry.view<UIViewComponent, UIImageComponent>();
        images.each([&](auto &view, auto &image) {
            ImGui::SetCursorPos({ BasePos.x + (float)(int32_t)view.GlobalPosition.x, BasePos.y + (float)(int32_t)view.GlobalPosition.y });
            ImGui::Image(ImGui::TexID(image.Texture), { (float)(int32_t)view.Size.x, (float)(int32_t)view.Size.y });
        });

        auto lables = scene.Registry.view<UIViewComponent, UITextComponent>();
        lables.each([&](auto &view, auto &text) {
            ImGui::SetCursorPos({ BasePos.x + (float)(int32_t)view.GlobalPosition.x, BasePos.y + (float)(int32_t)view.GlobalPosition.y });
            ImGui::Text(text.Text.data());
        });
    }
    ImGui::End();
    ImGui::PopStyleVar();
}

void ImGuiSystem::OnUpdate(EScene& scene)
{
    const ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    if (ImGui::Begin("Root", nullptr, RootWindowFlags))
    {
        ImGui::PopStyleVar(2);
        ImGuiID Workspace = ImGui::GetID("Workspace");
        ImGui::DockSpace(Workspace/*, {}, ImGuiDockNodeFlags_AutoHideTabBar*/);
        Draw(scene);
    }
    ImGui::End();
};

}
