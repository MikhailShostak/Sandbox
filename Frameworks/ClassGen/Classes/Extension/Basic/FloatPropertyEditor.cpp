namespace ClassGen
{

void FloatPropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat(ID.data(), &Value, 0.01f);
    ImGui::PopItemWidth();
}

}
