namespace ClassGen
{

void ColorPropertyEditor::Draw()
{
    ImGui::PushItemWidth(-1);
    ImGui::ColorEdit4(ID.data(), Value.f32, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_AlphaPreviewHalf);
    ImGui::PopItemWidth();
}

}
