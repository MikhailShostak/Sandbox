#include "../Views.hpp"

#include "../../Data/Config.hpp"
#include "../../Data/Extensions.hpp"

namespace Settings
{

void ShowExtension(const std::filesystem::path &path, Extension &extension)
{
    std::string id = path.filename().generic_string();

    ImGui::Text(extension.Title.data());
    ImGui::SameLine();
    ImGui::Text(id.data());
    ImGui::SameLine();
    ImGui::Text(extension.Version.data());

    ImGui::Text(extension.Author.data());

    ImGui::Text(extension.Description.data());

    if (ImGui::Checkbox("Enabled", &extension.Enabled))
    {
        //Config["Extensions"] = id;
    }

    ImGui::SameLine();

    if (ImGui::Button("Content"))
    {
        std::string str = fmt::format("explorer \"{}\"", (std::filesystem::current_path() / path).make_preferred().string());
        std::cout << str << std::endl;
        boost::process::system(str);
    }
}

void ShowExtensions()
{
    ImGui::InputText("SearchDirectory", &Config.Extensions.SearchDirectory);
    ImGui::SameLine();
    if (ImGui::Button("Reload"))
    {
        ReloadExtensions();
    }

    if (ImGui::BeginChild("ExtensionScroll", { 0, -ImGui::GetFrameHeightWithSpacing() * 3 }))
    {
        for(auto &pair : ExtensionsCache)
        {
            ShowExtension(pair.first, pair.second);
        }
    }
    ImGui::EndChild();

    static Extension extension;
    ImGui::InputText("Title", &extension.Title);
    ImGui::InputText("Author", &extension.Author);

    bool CreateRequest = false;
    if (ImGui::Button("Create"))
    {
        CreateRequest = true;
    }

    if (CreateRequest)
    {
        ImGui::OpenPopup("CreateNewExtensionPopup");
        CreateRequest = false;
    }

    ImGui::SetNextWindowSize({400, 100}, ImGuiCond_FirstUseEver);
    if (ImGui::BeginPopupModal("CreateNewExtensionPopup"))
    {
        std::string id = GetExtensionID(extension.Author, extension.Title);
        auto path = GetExtensionPath(id);
        std::string text = fmt::format("Create new extension ({}) at \"{}\"?", id, path.generic_string());
        ImGui::TextWrapped(text.data());
        if (ImGui::Button("Create"))
        {
            CreateExtension(path / Config.Extensions.ConfigFilename);
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

}
