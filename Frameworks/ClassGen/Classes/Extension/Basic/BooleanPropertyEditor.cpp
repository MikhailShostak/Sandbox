namespace ClassGen
{

void BooleanPropertyEditor::Draw()
{
    if (ImGui::Checkbox(ID.data(), &Value))
    {
        Changed();
    }
}

}
