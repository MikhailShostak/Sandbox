namespace ClassGen
{

void Int3PropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::DragInt3(ID.data(), Value.i32, 1);
    ImGui::PopItemWidth();
}

}
