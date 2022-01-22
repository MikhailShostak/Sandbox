namespace ClassGen
{

void PropertyEditor::Serialize(Serialization::Data& Data) {}
void PropertyEditor::Deserialize(const Serialization::Data& Data) {}
void PropertyEditor::Draw() {}
void PropertyEditor::DrawLabel(const String& Name) { ImGui::Text(Name.data()); }
void PropertyEditor::Clear() {}

}
