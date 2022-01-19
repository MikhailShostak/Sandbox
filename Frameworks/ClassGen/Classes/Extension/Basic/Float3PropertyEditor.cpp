namespace ClassGen
{

void Float3PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    if (ImGui::DragFloat3(ID.data(), Value.f32, 0.01f))
    {
        Changed();
    }
    ImGui::PopItemWidth();
}

}
