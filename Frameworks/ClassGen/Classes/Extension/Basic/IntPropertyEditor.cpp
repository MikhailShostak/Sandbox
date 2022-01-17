namespace ClassGen
{

void IntPropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragInt(ID.data(), &Value, 1);
    ImGui::PopItemWidth();
}

}
