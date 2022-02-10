#include "Classes/Extension/Graphics/PreviewViewport.hpp"

namespace ClassGen
{

void MaterialFileEditor::RenderFile()
{
    PreviewViewport.Load(*g_GraphicsContext);

    auto& info = *DynamicCast<ClassGen::MaterialInfo>(Data.Instance);

    ImGui::Columns(2);

    auto width = ImGui::GetColumnWidth();
    PreviewViewport.Camera.Resolution.x = width - 5;
    if ((int32_t)PreviewViewport.Camera.Resolution.x != (int32_t)PreviewViewport.GBuffer.Targets[0]->Size.x)
    {
        PreviewViewport.GBuffer.Resize(PreviewViewport.Camera.Resolution);
    }

    PreviewViewport.Draw(*g_GraphicsContext, [&]() {
        ImGui::SameLine();
        if (ImGui::Button(ICON_BUILD.data()))
        {
            if (info.MaterialInstance)
            {
                g_GraphicsContext->InvalidateMaterial(*info.MaterialInstance);
                info.MaterialInstance = nullptr;
            }
            this->PreviewViewport.Material = info.Load(*g_GraphicsContext, this->PreviewViewport.GBuffer.GetBuffer());
        }
    });

    ImGui::NextColumn();

    if (ImGui::InputText("Namespace", &info.Namespace))
    {
        MarkFileDirty(Data.Path);
    }

    if (ImGui::CollapsingHeader("Properties##Header", nullptr))
    {
        int32_t i = info.Properties.size();
        if (ImGui::SliderInt("Properties", &i, 0, 64))
        {
            info.Properties.resize(i);
        }
        ImGui::Indent();
        for (size_t i = 0; i < info.Properties.size(); ++i)
        {
            auto& Property = info.Properties[i];
            if (ImGui::InputText(fmt::format("[{}] Name##{}", i, fmt::ptr(&Property)).data(), &Property.Name))
            {
                MarkFileDirty(Data.Path);
            }
            if (ImGui::DragFloat4(fmt::format("[{}] Value##{}", i, fmt::ptr(&Property)).data(), Property.Value.f32, 0.01f))
            {
                info.Update();
                MarkFileDirty(Data.Path);
            }
            if (ImGui::InputText(fmt::format("[{}] Attribute##{}", i, fmt::ptr(&Property)).data(), &Property.Attribute))
            {
                MarkFileDirty(Data.Path);
            }
            if (ImGui::Checkbox(fmt::format("[{}] Use in Vertex Shader##{}", i, fmt::ptr(&Property)).data(), &Property.UseInVertexShader))
            {
                MarkFileDirty(Data.Path);
            }
            if (ImGui::Checkbox(fmt::format("[{}] Use in Pixel Shader##{}", i, fmt::ptr(&Property)).data(), &Property.UseInPixelShader))
            {
                MarkFileDirty(Data.Path);
            }
        }
        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Samplers##Header", nullptr))
    {
        int32_t i = info.Textures.size();
        if (ImGui::SliderInt("Samplers", &i, 0, 8))
        {
            info.Textures.resize(i);
        }
        ImGui::Indent();
        for (size_t i = 0; i < info.Textures.size(); ++i)
        {
            auto& texture = info.Textures[i];
            if (ImGui::InputText(fmt::format("[{}] Sampler Name##{}", i, fmt::ptr(&texture)).data(), &texture.SamplerName))
            {
                MarkFileDirty(Data.Path);
            }
            if (ImGui::InputText(fmt::format("[{}] Texture Name##{}", i, fmt::ptr(&texture)).data(), &texture.TextureName))
            {
                MarkFileDirty(Data.Path);
            }
            if (ImGui::Checkbox(fmt::format("[{}] Use in Vertex Shader##{}", i, fmt::ptr(&texture)).data(), &texture.UseInVertexShader))
            {
                MarkFileDirty(Data.Path);
            }
            if (ImGui::Checkbox(fmt::format("[{}] Use in Pixel Shader##{}", i, fmt::ptr(&texture)).data(), &texture.UseInPixelShader))
            {
                MarkFileDirty(Data.Path);
            }
        }
        ImGui::Unindent();
    }

    if (ImGui::CollapsingHeader("Import", nullptr))
    {
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

        String vsp = info.VertexShader.generic_string();
        if (ImGui::InputText("Vertex Shader", &vsp))
        {
            info.VertexShader = vsp;
            MarkFileDirty(Data.Path);
        }

        String psp = info.PixelShader.generic_string();
        if (ImGui::InputText("Pixel Shader", &psp))
        {
            info.PixelShader = psp;
            MarkFileDirty(Data.Path);
        }
    }
    ImGui::Columns(1);
}

}
