namespace ClassGen
{

void Int2PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragInt2(ID.data(), Value.i32, 1);
    ImGui::PopItemWidth();
}

}
