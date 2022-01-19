namespace ClassGen
{

void IntPropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    if (ImGui::DragInt(ID.data(), &Value, 1))
    {
        Changed();
    }
    ImGui::PopItemWidth();
}

}
