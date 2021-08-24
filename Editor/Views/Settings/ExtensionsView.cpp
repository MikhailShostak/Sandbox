#include "../Views.hpp"

#include "../../Data/Config.hpp"
#include "../../Data/Extensions.hpp"

namespace Settings
{

void ShowExtension(const std::filesystem::path &path, const YAML::Node &extension)
{
    if (
        !extension["Title"].IsDefined() ||
        !extension["Version"].IsDefined() ||
        !extension["Author"].IsDefined() ||
        !extension["Description"].IsDefined() ||
        !extension["Enabled"].IsDefined()
    )
    {
        return;
    }
    std::string id = path.filename().generic_string();

    std::string title = extension["Title"].as<std::string>();
    ImGui::Text(title.data());

    ImGui::SameLine();

    ImGui::Text(id.data());

    ImGui::SameLine();

    std::string version = extension["Version"].as<std::string>();
    ImGui::Text(version.data());

    std::string author = extension["Author"].as<std::string>();
    ImGui::Text(author.data());

    std::string description = extension["Description"].as<std::string>();
    ImGui::Text(description.data());

    bool enabled = extension["Enabled"].as<bool>();
    if(ImGui::Checkbox("Enabled", &enabled))
    {
        //Config["Extensions"] = id;
    }

    ImGui::SameLine();

    if(ImGui::Button("Content"))
    {
        std::string str = fmt::format("explorer \"{}\"", (std::filesystem::current_path() / path).make_preferred().string());
        std::cout << str << std::endl;
        boost::process::system(str);
    }
}

void ShowExtensions()
{
    ImGui::InputText("SearchDirectory", &ExtensionsSearchDirectory);
    ImGui::SameLine();
    if (ImGui::Button("Reload"))
    {
        ReloadExtensions();
    }

    if (ImGui::BeginChild("ExtensionScroll", { 0, -ImGui::GetFrameHeightWithSpacing() * 3 }))
    {
        for(const auto &pair : ExtensionsCache)
        {
            ShowExtension(pair.first, pair.second);
        }
    }
    ImGui::EndChild();

    static std::string ExtensionTitle;
    ImGui::InputText("Title", &ExtensionTitle);
    static std::string ExtensionAuthor;
    ImGui::InputText("Author", &ExtensionAuthor);

    bool CreateRequest = false;
    if(ImGui::Button("Create"))
    {
        CreateRequest = true;
    }

    if (CreateRequest)
    {
        ImGui::OpenPopup("CreateNewExtensionPopup");
        CreateRequest = false;
    }

    if(ImGui::BeginPopupModal("CreateNewExtensionPopup"))
    {
        std::string id = GetExtensionID(ExtensionAuthor, ExtensionTitle);
        auto path = GetExtensionPath(id);
        std::string text = fmt::format("Create new extension ({}) at \"{}\"?", id, path.generic_string());
        ImGui::TextWrapped(text.data());
        if(ImGui::Button("Create"))
        {
            CreateExtension(path / ExtensionConfigFilename);
            ImGui::CloseCurrentPopup();
        }
        if(ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

}
