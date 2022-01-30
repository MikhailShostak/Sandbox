#include "Data/Config.hpp"
#include "Data/Extensions.hpp"
#include "Data/Workspace.hpp"
#include "Editors/BinaryEditor.hpp"
#include "Editors/ClassGenEditor.hpp"
#include "Editors/TextEditor.hpp"
#include "Views/Views.hpp"

#include <Class.gen.hpp>

#include "Components/EditorWindow.hpp"

void OnContentUpdate()
{
    ImGuiID Workspace = ImGui::GetID("Workspace");

    std::vector<std::filesystem::path> FilesToClose;
    for (const auto& f : Config.File.OpenedFiles)
    {
        ImGui::SetNextWindowDockID(Workspace, ImGuiCond_Once);
        bool IsOpen = true;
        if (ImGui::Begin(GetFileTitle(f).data(), &IsOpen))
        {
            ImGuiContext& g = *GImGui;
            if (ImGui::IsMouseReleased(1) && (g.CurrentWindow->ID == g.HoveredId || ImGui::IsItemHovered()))
            {
                ImGui::OpenPopup("FileContextMenu");
            }
            if (ImGui::BeginPopup("FileContextMenu"))
            {
                //auto directory = is_directory ? path : path.parent_path();
                if (ImGui::MenuItem("Save"))
                {
                    SaveFile(f);
                }
                if (ImGui::MenuItem("Save As..."))
                {
                    File::DisplaySaveAsDialog = true;
                    File::FileToSave = f;
                }
                ImGui::Separator();
                if (ImGui::MenuItem("Close"))
                {
                    FilesToClose.push_back(f);
                }
                ImGui::Separator();
                Utils::Menu::ShowDefaultFileOperations(f);
                ImGui::EndPopup();
            }

            std::string ext = f.extension().string();
            std::string EditorName = "TextEditor";
            auto it1 = ranges::find_if(Config.FileTypes, [&](const auto& v)
            {
                return v.Extensions == ext;
            });
            if (it1 != Config.FileTypes.end())
            {
                EditorName = it1->Editor;
            }

            auto it2 = std::find_if(Editors.begin(), Editors.end(), [&](const auto& v)
            {
                return v.first == EditorName;
            });
            if (it2 == Editors.end())
            {
                continue;
            }

            const std::unique_ptr<Editor>& editor = it2->second;
            editor->RenderFile(f);
        }

        if (!IsOpen)
        {
            FilesToClose.push_back(f);
        }

        ImGui::End();
    }
    if (!FilesToClose.empty())
    {
        CloseFiles(FilesToClose);
    }
    if (PendingReindex)
    {
        ReindexFiles();
    }
}

std::string ApplicationConfig = "config.yaml";

void LoadIcons()
{
    ImFontConfig config;
    config.MergeMode = true;
    config.GlyphOffset = { 0, 4 };
    static const ImWchar IconsRanges[] = { ICON_MIN_MD, ICON_MAX_MD, 0 };
    ImGui::LoadFont("Fonts/MaterialDesignIcons/MaterialIcons-Regular.ttf", 18_px, &config, IconsRanges);
}

void ApplyStyle()
{
    ImGuiStyle& style = ImGui::GetStyle();

    style.WindowPadding = { 4, 4 };
    style.FramePadding = { 4, 2 };
    style.CellPadding = { 4, 2 };
    style.ItemSpacing = { 4, 2 };
    style.ItemInnerSpacing = { 2, 2 };
    style.TouchExtraPadding = { 0, 0 };
    style.IndentSpacing = 18;
    style.ScrollbarSize = 12;
    style.GrabMinSize = 10;

    style.WindowBorderSize = 1;
    style.ChildBorderSize = 1;
    style.PopupBorderSize = 1;
    style.FrameBorderSize = 0;
    style.TabBorderSize = 0;

    style.WindowRounding = 4;
    style.ChildRounding = 0;
    style.FrameRounding = 2;
    style.PopupRounding = 0;
    style.ScrollbarRounding = 0;
    style.GrabRounding = 0;
    style.LogSliderDeadzone = 4;
    style.TabRounding = 4;

    style.WindowTitleAlign = { 0.5f, 0.5f };
    style.WindowMenuButtonPosition = ImGuiDir_Left;
    style.ColorButtonPosition = ImGuiDir_Right;
    style.ButtonTextAlign = { 0.5f, 0.5f };
    style.SelectableTextAlign = { 0.0f, 0.5f };

    style.DisplaySafeAreaPadding = { 3, 3 };
}

void EditorWindow::CreateUI()
{
    Super::CreateUI();
    LoadIcons();
    ApplyStyle();
}

void EditorWindow::Load(Core::Application& Application)
{
    Super::Load(Application);

    if (std::filesystem::exists(ApplicationConfig))
    {
        Serialization::FromFile(ApplicationConfig, Config);
        ReloadExtensions();
        if (!Config.File.OpenedFolders.empty())
        {
            File::DialogWorkingDirectory = Config.File.OpenedFolders[0];
        }
    }

    Editors.insert({ "BinaryEditor", std::make_unique<DefaultExtensions::BinaryEditor>() });
    Editors.insert({ "TextEditor", std::make_unique<DefaultExtensions::TextEditor>() });
    Editors.insert({ "ClassGenEditor", std::make_unique<DefaultExtensions::ClassGenEditor>() });

    ClassGen::LoadExtensions();
    g_ExtensionLibrary.Navigate = [](const ClassGen::FileInfo& type)
    {
        if (System::IsRegularFile(type.Path))
        {
            OpenFile(type.Path, false);
        }
    };

    ReloadFiles();
}

void EditorWindow::Unload(Core::Application& Application)
{
    Serialization::ToFile(Config, ApplicationConfig);

    Super::Unload(Application);
}

void EditorWindow::Draw()
{
    ShowRootView(&OnContentUpdate);

    File::ProcessDialogs();

    Settings::ShowSettings();
    View::ShowFileBrowser();
    View::ShowConsole();
    if (Debug::DisplayImGuiDemo)
    {
        ImGui::ShowDemoWindow();
    }
    Debug::ShowDebugWindow();
}
