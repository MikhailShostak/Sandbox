#include "Data/Config.hpp"
#include "Data/Extensions.hpp"
#include "Data/Workspace.hpp"
#include "Editors/BinaryEditor.hpp"
#include "Editors/ClassGenEditor.hpp"
#include "Editors/TextEditor.hpp"
#include "Views/Views.hpp"

#include <Class.gen.hpp>

void OnContentUpdate()
{
    ImGuiID Workspace = ImGui::GetID("Workspace");

    std::vector<std::filesystem::path> FilesToClose;
    for (const auto &f : Config.File.OpenedFiles)
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
            auto it1 = ranges::find_if(Config.FileTypes, [&](const auto &v)
            {
                return v.Extensions == ext;
            });
            if (it1 != Config.FileTypes.end())
            {
                EditorName = it1->Editor;
            }

            auto it2 = std::find_if(Editors.begin(), Editors.end(), [&](const auto &v)
            {
                return v.first == EditorName;
            });
            if (it2 == Editors.end())
            {
                continue;
            }

            const std::unique_ptr<Editor> &editor = it2->second;
            editor->RenderFile(f);
        }

        if (!IsOpen)
        {
            FilesToClose.push_back(f);
        }

        ImGui::End();
    }
    CloseFiles(FilesToClose);
}

class EditorApp final : public NativeApplication
{
public:

    std::string ApplicationConfig = "config.yaml";

    bool PreInit() override
    {
        MainWindowTitle = "Editor";
        return true;
    }

    bool Init() override
    {
        if (std::filesystem::exists(ApplicationConfig))
        {
            Serialization::FromFile(ApplicationConfig, Config);
            ReloadExtensions();
            if (!Config.File.OpenedFolders.empty())
            {
                File::DialogWorkingDirectory = Config.File.OpenedFolders[0];
            }
        }

        Editors.insert({"BinaryEditor", std::make_unique<DefaultExtensions::BinaryEditor>() });
        Editors.insert({"TextEditor", std::make_unique<DefaultExtensions::TextEditor>() });
        Editors.insert({"ClassGenEditor", std::make_unique<DefaultExtensions::ClassGenEditor>() });
        
        ClassGen::LoadExtensions();

        ReloadFiles();

        return true;
    }

    void UpdateUI(float dt) override
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
    }

    void Draw() override
    {

    }

    void Terminate() override
    {
        Serialization::ToFile(Config, ApplicationConfig);
    }
};

DEFINE_MAIN_APPLICATION(EditorApp)
