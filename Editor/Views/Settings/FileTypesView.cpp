#include "../Views.hpp"

#include "../../Data/Config.hpp"
#include "../../Editors/Editor.hpp"

namespace Settings
{

void ShowFileTypes()
{
    std::vector<const char *> EditorNames;
    for(const auto &v : Editors)
    {
        EditorNames.push_back(v.first.data());
    }

    auto FileTypes = Config["FileTypes"];
    if (ImGui::BeginTable("FileTypesTable", 3, DefaultTableFlags))
    {
        ImGui::TableSetupColumn("Title", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Editor", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Extensions", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();

        for(auto node : FileTypes)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            auto id = node["Title"].as<std::string>();
            ImGui::Text(node["Title"].as<std::string>().data());

            ImGui::TableSetColumnIndex(1);
            auto editor = node["Editor"].as<std::string>();

            int SelectedItem = static_cast<int>(std::distance(EditorNames.begin(), std::find(EditorNames.begin(), EditorNames.end(), editor)));
            ImGui::PushItemWidth(-1);
            if (ImGui::Combo(("##Editor "+ id).data(), &SelectedItem, EditorNames.data(), static_cast<int>(EditorNames.size())))
            {
                node["Editor"] = std::string(EditorNames[SelectedItem]);
            }
            ImGui::PopItemWidth();

            ImGui::TableSetColumnIndex(2);
            ImGui::Text(node["Extensions"].as<std::string>().data());
        }
        ImGui::EndTable();
    }

    static std::string title;
    ImGui::InputText("Title", &title);

    static int SelectedItem = 0;
    ImGui::Combo("Editor", &SelectedItem, EditorNames.data(), static_cast<int>(EditorNames.size()));

    static std::string extensions;
    ImGui::InputText("Extensions", &extensions);

    if (ImGui::Button("Add") && !title.empty() && !extensions.empty())
    {
        YAML::Node fileType;
        fileType["Title"] = title;
        fileType["Editor"] = EditorNames[SelectedItem];
        fileType["Extensions"] = extensions;
        FileTypes.push_back(fileType);
    }
}

}
