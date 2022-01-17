namespace ClassGen
{

void Float4PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat4(ID.data(), Value.f32, 0.01f);
    ImGui::PopItemWidth();
}

}
