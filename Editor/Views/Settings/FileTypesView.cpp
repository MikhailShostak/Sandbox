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

    if (ImGui::BeginTable("FileTypesTable", 3, DefaultTableFlags))
    {
        ImGui::TableSetupColumn("Title", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Editor", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Extensions", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableHeadersRow();

        for(auto &fileType : Config.FileTypes)
        {
            ImGui::TableNextRow();

            ImGui::TableSetColumnIndex(0);
            auto id = fileType.Title;
            ImGui::Text(fileType.Title.data());

            ImGui::TableSetColumnIndex(1);
            int SelectedItem = static_cast<int>(std::distance(EditorNames.begin(), ranges::find(EditorNames, fileType.Editor)));
            ImGui::PushItemWidth(-1);
            if (ImGui::Combo(("##Editor "+ id).data(), &SelectedItem, EditorNames.data(), static_cast<int>(EditorNames.size())))
            {
                fileType.Editor = std::string(EditorNames[SelectedItem]);
            }
            ImGui::PopItemWidth();

            ImGui::TableSetColumnIndex(2);
            ImGui::Text(fileType.Extensions.data());
        }
        ImGui::EndTable();
    }

    static DataConfig::FileType fileType;
    ImGui::InputText("Title", &fileType.Title);

    static int SelectedItem = 0;
    ImGui::Combo("Editor", &SelectedItem, EditorNames.data(), static_cast<int>(EditorNames.size()));

    ImGui::InputText("Extensions", &fileType.Extensions);

    if (ImGui::Button("Add") && !fileType.Title.empty() && !fileType.Extensions.empty())
    {
        fileType.Editor = EditorNames[SelectedItem];
        Config.FileTypes.push_back(fileType);
    }
}

}
