#include "Classes/Extension/Graphics/PreviewViewport.hpp"

namespace ClassGen
{

void MeshFileEditor::RenderFile()
{
    PreviewViewport.Load(*g_GraphicsContext);

    auto& info = *DynamicCast<ClassGen::MeshInfo>(Data.Instance);

    if (ImGui::InputText("Namespace", &info.Namespace))
    {
        MarkFileDirty(Data.Path);
    }

    String s = info.Path.generic_string();
    if (ImGui::InputText("Path", &s))
    {
        info.Path = s;
        MarkFileDirty(Data.Path);
    }

    if (ImGui::InputText("Name", &info.Name))
    {
        MarkFileDirty(Data.Path);
    }

    if (ImGui::InputText("Material", &info.Material))
    {
        MarkFileDirty(Data.Path);
    }

    auto p = info.Path / info.Name;
    if (LastPath != p)
    {
        LastPath = p;

        if (System::IsRegularFile(info.Path) && !info.Name.empty() && !info.Material.empty())
        {
            info.MeshInstance = nullptr;
            PreviewViewport.Mesh = info.Load(*g_GraphicsContext, PreviewViewport.GBuffer.GetBuffer());
            PreviewViewport.Material = info.MaterialInstance;
        }
    }

    PreviewViewport.Draw(*g_GraphicsContext);
}

}
