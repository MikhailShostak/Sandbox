namespace ClassGen
{

void Float2PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    if (ImGui::DragFloat2(ID.data(), Value.f32, 0.01f))
    {
        Changed();
    }
    ImGui::PopItemWidth();
}

}
