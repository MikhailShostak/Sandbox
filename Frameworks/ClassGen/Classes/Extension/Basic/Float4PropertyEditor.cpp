namespace ClassGen
{

void Float4PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    if (ImGui::DragFloat4(ID.data(), Value.f32, 0.01f))
    {
        Changed();
    }
    ImGui::PopItemWidth();
}

}
