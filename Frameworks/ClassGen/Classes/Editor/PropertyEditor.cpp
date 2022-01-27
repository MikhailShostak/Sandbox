namespace ClassGen
{

void PropertyEditor::SerializeProperty(Serialization::Data& Data) {}
void PropertyEditor::DeserializeProperty(const Serialization::Data& Data) {}
void PropertyEditor::Draw() {}
void PropertyEditor::DrawLabel(const String& Name) { ImGui::Text(Name.data()); }
void PropertyEditor::Clear() {}

}
