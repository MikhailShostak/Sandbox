namespace ClassGen
{

void InstancePropertyEditor::Draw()
{
    ImGui::PushItemWidth(-24);
    if (ImGui::InputText(ID.data(), &Value.Type))
    {
        Changed();
    }

    Serialization::FromString(Value.Type, ValuesEditor.TypeInfo);
    ValuesEditor.FileInfo = FindClassByName(ValuesEditor.TypeInfo);
    if (ValuesEditor.FileInfo.Type == "Asset")
    {
        ImGui::PopItemWidth();
        ImGui::SameLine();
        if (ImGui::Button(fmt::format("{}##{}", ICON_OPEN_IN_NEW, ID).data()))
        {
            g_ExtensionLibrary.Navigate(ValuesEditor.FileInfo);
        }
        return;
    }
    ValuesEditor.ID = fmt::format("{}", fmt::ptr(&ValuesEditor));
    ValuesEditor.Value = Value.Values;
    ValuesEditor.Changed = [this]()
    {
        Value.Values = ValuesEditor.Value;
        Changed();
    };

    ImGui::PopItemWidth();
    ImGui::SameLine();
    ValuesEditor.Draw();
}

}
