#include "PBR/PBRMaterial.hpp"

namespace ECS
{

void GraphicsSystem::OnLoad()
{
    GBuffer.Targets = {
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
    };
    GBuffer.DepthStencil = CreateShared<Graphics::Texture>();

    Transforms.MaxSize = 1;
    Transforms.Instances.resize(Transforms.MaxSize);
    m_GraphicsContext->CreateDrawBatch(Transforms);
}

void GraphicsSystem::OnUnload()
{

}

void GraphicsSystem::OnUpdate()
{
    if (!GBuffer.IsCompiled)
    {
        GBuffer.Resize(m_Resolution);
        m_GraphicsContext->CreateRenderTarget(GBuffer);
    }

    m_GraphicsContext->SetRenderBuffer(GBuffer.GetBuffer());
    m_GraphicsContext->ClearRenderBuffers({ 0.0, 0.0, 0.0, 0.0 });
    m_GraphicsContext->ClearDepthStencilBuffers(1.0f, 0);

    auto &Camera = ECS::g_Registry.get<Graphics::Camera>(CurrentCamera);
    Camera.Resolution = m_Resolution;
    g_CameraConstants->g_ViewProj = Camera.GetView();

    auto view = g_Registry.view<ECS::TransformComponent, MeshComponent>();
    view.each([this](auto &transformComponent, auto &meshComponent)
    {
        auto ModelMatrix = transformComponent.GetMatrix();
        ModelMatrix = mul(Matrix4::scale(transformComponent.Scale), ModelMatrix);
        Transforms.Instances[0] = ModelMatrix;
        m_GraphicsContext->ApplyMaterial(*meshComponent.Material);
        m_GraphicsContext->Upload(Transforms);
        m_GraphicsContext->Draw(*meshComponent.Mesh, Transforms);
    });

    if (ImGui::Begin("G-Buffer"))
    {
        if (GBuffer.IsCompiled)
        {
            ImGui::Image(ImGui::TexID(GBuffer.Targets[0]), { 512, 512 }); ImGui::SameLine(); ImGui::Image(ImGui::TexID(GBuffer.Targets[1]), { 512, 512 });
            ImGui::Image(ImGui::TexID(GBuffer.Targets[2]), { 512, 512 }); ImGui::SameLine(); ImGui::Image(ImGui::TexID(GBuffer.Targets[3]), { 512, 512 });
        }
    }
    ImGui::End();
}

}
