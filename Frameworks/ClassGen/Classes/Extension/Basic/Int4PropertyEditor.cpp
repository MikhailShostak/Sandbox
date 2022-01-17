namespace ClassGen
{

void Int4PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragInt4(ID.data(), Value.i32, 1);
    ImGui::PopItemWidth();
}

}
