namespace ClassGen
{

void Float2PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat2(ID.data(), Value.f32, 0.01f);
    ImGui::PopItemWidth();
}

}
