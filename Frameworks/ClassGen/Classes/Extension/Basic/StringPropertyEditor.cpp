namespace ClassGen
{

void StringPropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    if (ImGui::InputText(ID.data(), &Value))
    {
        Changed();
    }
    ImGui::PopItemWidth();
}

}
