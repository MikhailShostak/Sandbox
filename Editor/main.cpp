#include "Data/Config.hpp"
#include "Data/Extensions.hpp"
#include "Data/Workspace.hpp"
#include "Editors/BinaryEditor.hpp"
#include "Editors/ClassGenEditor.hpp"
#include "Editors/TextEditor.hpp"
#include "Views/Views.hpp"

void OnContentUpdate()
{
    ImGuiID Workspace = ImGui::GetID("Workspace");

    auto FileTypes = Config["FileTypes"];
    std::vector<std::filesystem::path> FilesToClose;
    for(const auto &node : OpenedFiles())
    {
        ImGui::SetNextWindowDockID(Workspace, ImGuiCond_Once);
        bool IsOpen = true;
        auto f = node.as<std::filesystem::path>();
        if(ImGui::Begin(GetFileTitle(f).data(), &IsOpen))
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
            auto it1 = std::find_if(FileTypes.begin(), FileTypes.end(), [&](const auto &v)
            {
                return v["Extensions"].template as<std::string>() == ext;
            });
            if(it1 != FileTypes.end())
            {
                EditorName = (*it1)["Editor"].as<std::string>();
            }

            auto it2 = std::find_if(Editors.begin(), Editors.end(), [&](const auto &v)
            {
                return v.first == EditorName;
            });
            if(it2 == Editors.end())
            {
                continue;
            }

            const std::unique_ptr<Editor> &editor = it2->second;
            editor->RenderFile(f);
        }

        if(!IsOpen)
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
        if(std::filesystem::exists(ApplicationConfig))
        {
            Config = YAML::LoadFile(ApplicationConfig);
            ReloadExtensionsFromConfig();
            if(OpenedFolders().IsSequence())
            {
                File::DialogWorkingDirectory = OpenedFolders()[0].as<std::filesystem::path>();
            }
        }

        Editors.insert({"BinaryEditor", std::make_unique<DefaultExtensions::BinaryEditor>() });
        Editors.insert({"TextEditor", std::make_unique<DefaultExtensions::TextEditor>() });
        Editors.insert({"ClassGenEditor", std::make_unique<DefaultExtensions::ClassGenEditor>() });

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
        if(Debug::DisplayImGuiDemo)
        {
            ImGui::ShowDemoWindow();
        }
    }

    void Draw() override
    {

    }

    void Terminate() override
    {
        YAML::Emitter out;
        out << Config;
        std::ofstream file;
        file.open(ApplicationConfig, std::ios::binary);
        if(file.is_open())
        {
            file << out.c_str();
        }
    }
};

DEFINE_MAIN_APPLICATION(EditorApp)
