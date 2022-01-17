namespace ClassGen
{

void Float3PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragFloat3(ID.data(), Value.f32, 0.01f);
    ImGui::PopItemWidth();
}

}
