
namespace ClassGen
{

void MeshFileEditor::RenderFile()
{
    auto& info = *std::dynamic_pointer_cast<ClassGen::MeshInfo>(Data.Instance);

    if (ImGui::InputText("Namespace", &info.Namespace))
    {
        MarkFileDirty(Data.Path);
    }

    String s = info.Path.generic_string();
    if (ImGui::InputText("Path", &s))
    {
        info.Path = s;
        MarkFileDirty(Data.Path);
        if (!System::IsRegularFile(info.Path))
        {
            //Texture = nullptr;
            return;
        }
    }

    if (LastPath != info.Path)
    {
        LastPath = info.Path;
    }
}

}
