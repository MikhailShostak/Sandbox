namespace ClassGen
{

void StringPropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::InputText(ID.data(), &Value);
    ImGui::PopItemWidth();
}

}
