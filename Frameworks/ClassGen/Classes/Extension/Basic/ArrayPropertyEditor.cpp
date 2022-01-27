namespace ClassGen
{

Serialization::Data ArrayPropertyEditor::CreateDefaultData()
{
    auto& ItemTypeInfo = TypeInfo.Parameters.front();

    Serialization::Data DefaultData;
    auto [editor] = g_ExtensionLibrary.FindEditor(ItemTypeInfo);
    if (!editor)
    {
        return DefaultData;
    }
    editor->Serialize(DefaultData);
    return DefaultData;
};

void ArrayPropertyEditor::RebuildEditors()
{
    auto& ItemTypeInfo = TypeInfo.Parameters.front();

    PropertyEditors.clear();
    PropertyEditors.reserve(Value.size());
    for (auto& data : Value)
    {
        auto [editor] = g_ExtensionLibrary.FindEditor(ItemTypeInfo);
        if (!editor)
        {
            return;
        }

        auto propertyId = fmt::format("##PropertyValue{}", fmt::ptr(&data));
        editor->ID = propertyId;
        //TODO: optimize
        editor->TypeInfo = ItemTypeInfo;
        editor->FileInfo = FindClassByName(editor->TypeInfo);

        editor->Deserialize(data);

        auto editorPtr = editor.get();
        editor->Changed = [&, editorPtr]()
        {
            editorPtr->Serialize(data);
            Changed();
        };

        PropertyEditors.push_back(std::move(editor));
    }
};

void ArrayPropertyEditor::Draw()
{
    if (TypeInfo.Parameters.empty())
    {
        return;
    }

    ImGui::PushItemWidth(-1);
    if (ImGui::Button(fmt::format("{}##{}", ICON_ADD, fmt::ptr(&Value)).data()))
    {
        Value.push_back(CreateDefaultData());
        Changed();
    }
    ImGui::PopItemWidth();

    if (PropertyEditors.size() != Value.size())
    {
        RebuildEditors();
    }

    ImGui::Indent();
    size_t itemToRemove = ArrayUtils::InvalidIndex;
    for (size_t i = 0; i < PropertyEditors.size(); ++i)
    {
        auto& editor = PropertyEditors[i];

        ImGui::NextColumn();
        ImGui::Text(fmt::format("{}", i).data());
        ImGui::SameLine();
        if (ImGui::Button(fmt::format("{}##{}", ICON_DELETE, fmt::ptr(&editor)).data()))
        {
            itemToRemove = i;
        }
        ImGui::NextColumn();
        if (editor)
        {
            editor->Draw();
        }
    }
    if (itemToRemove != ArrayUtils::InvalidIndex)
    {
        auto it = Value.begin();
        std::advance(it, itemToRemove);
        Value.erase(it);
        Changed();
    }
    ImGui::Unindent();
}

}
