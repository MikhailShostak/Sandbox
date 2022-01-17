namespace ClassGen
{

void PathPropertyEditor::Draw()
{
    constexpr int ButtonSize = 24;
    
    ImGui::PushItemWidth(-ButtonSize - ImGui::GetStyle().ItemInnerSpacing.x - 1);
    String string = Value.generic_string();
    if (ImGui::InputText(ID.data(), &string))
    {
        Value = string;
    }
    ImGui::PopItemWidth();
    ImGui::SameLine();
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().ItemInnerSpacing.x - ImGui::GetStyle().ItemSpacing.x);
    ImGui::Button("...", { ButtonSize, 0 });
}

}
