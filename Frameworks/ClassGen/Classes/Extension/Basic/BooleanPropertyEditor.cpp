namespace ClassGen
{

void BooleanPropertyEditor::Draw()
{
    ImGui::Checkbox(ID.data(), &Value);
}

}
