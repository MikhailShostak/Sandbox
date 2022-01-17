namespace ClassGen
{

void EnumerationPropertyEditor::Draw()
{
    auto enumInfo = DynamicCast<ClassGen::EnumerationInfo>(FileInfo.Instance);
    if (!enumInfo)
    {
        return;
    }

    if (FileInfo.Type == "Flags")
    {
        Array<String> values = Str::Split(Value, "|");
        size_t i = 0;
        for (auto &value : enumInfo->Values)
        {
            bool checked = ArrayUtils::Contains(values, value);
            if (ImGui::Checkbox(value.data(), &checked))
            {
                if (checked)
                {
                    values.insert(values.begin() + i, value);
                }
                else
                {
                    boost::remove_erase(values, value);
                }
                Value = Str::Join(values, "|");
                Changed();
            }
            if (checked)
            {
                ++i;
            }
        }
    }
    else
    {
        Array<const char*> values = enumInfo->Values | ranges::views::transform([](const auto& v) { return v.data(); }) | ranges::to<Array<const char*>>();
        int currentValue = ArrayUtils::FindFirst(enumInfo->Values, Value);
        auto Combo = [](const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1)
        {
            return ImGui::Combo(label, current_item, items, items_count, popup_max_height_in_items);
        };

        if (ImGui::Combo(ID.data(), &currentValue, values.data(), values.size(), -1))
        {
            Value = enumInfo->Values[currentValue];
            Changed();
        }
    }
}

}
