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
