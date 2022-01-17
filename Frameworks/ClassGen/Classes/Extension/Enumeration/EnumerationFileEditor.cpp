namespace ClassGen
{
void EnumerationFileEditor::RenderFile()
{
    auto enumInfo = DynamicCast<ClassGen::EnumerationInfo>(Data.Instance);
    if (ImGui::Button(fmt::format("{}##AddEnumValue", ICON_ADD).data()))
    {
        enumInfo->Values.push_back("");
        MarkFileDirty(Path);
    }
    ImGui::SameLine();
    if (ImGui::Button(fmt::format("{}##ClearEnumValues", ICON_DELETE).data()))
    {
        enumInfo->Values.clear();
        MarkFileDirty(Path);
    }
    if (ImGui::InputText(fmt::format("Namespace").data(), &enumInfo->Namespace))
    {
        MarkFileDirty(Path);
    }

    size_t i = 0;
    size_t itemToDelete = -1;
    for (auto &value : enumInfo->Values)
    {
        if (ImGui::InputText(fmt::format("##{}", fmt::ptr(&value)).data(), &value))
        {
            MarkFileDirty(Path);
        }
        ImGui::SameLine();
        if (ImGui::Button(fmt::format("{}##DeleteEnumValue{}", ICON_DELETE, fmt::ptr(&value)).data()))
        {
            itemToDelete = i;
            MarkFileDirty(Path);
        }
        ++i;
    }

    if (itemToDelete != -1)
    {
        enumInfo->Values.erase(enumInfo->Values.begin() + itemToDelete);
    }
}
}
