namespace ClassGen
{

void FloatPropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    if (ImGui::DragFloat(ID.data(), &Value, 0.01f))
    {
        Changed();
    }
    ImGui::PopItemWidth();
}

}
