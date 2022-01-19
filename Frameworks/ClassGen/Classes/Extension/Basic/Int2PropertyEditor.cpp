namespace ClassGen
{

void Int2PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    if (ImGui::DragInt2(ID.data(), Value.i32, 1))
    {
        Changed();
    }
    ImGui::PopItemWidth();
}

}
