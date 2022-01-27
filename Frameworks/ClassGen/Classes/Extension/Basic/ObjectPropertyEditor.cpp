namespace ClassGen
{

void ObjectPropertyEditor::DrawProperties(ClassGen::ClassInfo &classInfo)
{
    for (const auto& p : classInfo.Properties)
    {
        if (!ArrayUtils::Contains(p.Attributes, String("Serialize")))
        {
            continue;
        }

        auto& editor = PropertyEditors[p.Name];
        if (editor == nullptr)
        {
            auto [e] = g_ExtensionLibrary.FindEditor(p.Type);
            editor = std::move(e);
            if (editor)
            {
                editor->Changed = [&]()
                {
                    editor->SerializeProperty(Value[p.Name]);
                    Changed();
                };
                if (auto it = Value.find(p.Name); it != Value.end())
                {
                    editor->DeserializeProperty(it->second);
                }
            }
        }

        if (editor)
        {
            auto propertyId = fmt::format("##{}", fmt::ptr(&editor));
            editor->ID = propertyId;

            //TODO: optimize
            editor->TypeInfo = p.Type;
            editor->FileInfo = FindClassByName(editor->TypeInfo);

            editor->DrawLabel(p.Name);
            if (auto it = Value.find(p.Name); it != Value.end())
            {
                ImGui::SameLine(ImGui::GetColumnWidth(0) - 24);
                if (ImGui::Button(fmt::format("{}{}", ICON_DELETE, propertyId).data()))
                {
                    Value.erase(p.Name);
                    if (editor != nullptr)
                    {
                        editor->Clear();
                    }
                    Changed();
                }
                ImGui::SameLine();
            }
            ImGui::NextColumn();
            editor->Draw();
            ImGui::NextColumn();
        }
    }
}

void ObjectPropertyEditor::DrawLabel(const String &Name)
{
    ImGui::Text(Name.data());
}

void ObjectPropertyEditor::Draw()
{
    if (ImGui::Button(fmt::format("{}##{}", ICON_OPEN_IN_NEW, ID).data()))
    {
        g_ExtensionLibrary.Navigate(FileInfo);
    }
    ImGui::NextColumn();
    ImGui::Indent();
    DrawAllProperties();
    ImGui::Unindent();
    ImGui::NextColumn();
}

void ObjectPropertyEditor::DrawAllProperties()
{
    auto classInfo = DynamicCast<ClassGen::ClassInfo>(FileInfo.Instance);
    if (!classInfo)
    {
        return;
    }

    while (classInfo)
    {
        DrawProperties(*classInfo);
        if (auto baseType = FindClassByName(classInfo->BaseType); baseType.Instance)
        {
            classInfo = DynamicCast<ClassGen::ClassInfo>(baseType.Instance);
        }
        else
        {
            classInfo = nullptr;
        }
    }
}

void ObjectPropertyEditor::Clear()
{
    Super::Clear();
    for (auto &[Name, Editor] : PropertyEditors)
    {
        if(!Editor)
        {
            continue;
        }

        Editor->Clear();
    }
}

}
