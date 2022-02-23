#include "PBR/PBRMaterial.hpp"

static float MSAAFactor = 2;

namespace ECS
{

void GraphicsSystem::OnLoad(EScene &scene)
{
    GBuffer.Targets = {
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
    };
    GBuffer.DepthStencil = CreateShared<Graphics::Texture>();

    GBuffer.Resize(m_Resolution * MSAAFactor);
    m_GraphicsContext->CreateRenderTarget(GBuffer);

    Transforms.MaxSize = 1;
    Transforms.Instances.resize(Transforms.MaxSize);
    m_GraphicsContext->CreateDrawBatch(Transforms);
}

void GraphicsSystem::OnUnload(EScene& scene)
{

}

void GraphicsSystem::OnUpdate(EScene& scene)
{
    if (GBuffer.Targets.empty())
    {
        return;
    }

    m_GraphicsContext->SetRenderBuffer(GBuffer.GetBuffer());
    m_GraphicsContext->ClearRenderBuffers({ 0.0, 0.0, 0.0, 0.0 });
    m_GraphicsContext->ClearDepthStencilBuffers(1.0f, 0);

    Render(scene);
}

void GraphicsSystem::Render(EScene& scene)
{
    if (!CurrentCamera)
    {
        return;
    }

    auto CameraComponent = CurrentCamera.FindComponent<ECS::CameraComponent>();
    if (!CameraComponent)
    {
        return;
    }

    CameraComponent->Camera.Resolution = m_Resolution * MSAAFactor;
    g_CameraConstants->g_ViewProj = CameraComponent->Camera.GetView();

    auto view = scene.Registry.view<ECS::TransformComponent, ECS::MeshComponent>();
    view.each([this](auto& transformComponent, auto& meshComponent)
    {
        if (!meshComponent.Material || !meshComponent.Mesh)
        {
            return;
        }
        auto ModelMatrix = transformComponent.Transform.GetMatrix();
        ModelMatrix = mul(Matrix4::scale(transformComponent.Transform.Scale), ModelMatrix);
        Transforms.Instances[0] = ModelMatrix;
        m_GraphicsContext->ApplyMaterial(*meshComponent.Material);
        m_GraphicsContext->Draw(*meshComponent.Mesh, Transforms);
    });

    auto targets = scene.Registry.view<ECS::MeshComponent, Graphics::RenderTarget>();
    targets.each([this](auto& meshComponent, auto& renderTarget)
    {
        Transforms.Instances[0] = Matrix4::identity();

        m_GraphicsContext->SetRenderBuffer(renderTarget.GetBuffer());
        m_GraphicsContext->ClearRenderBuffers({ 0.0, 0.0, 1.0, 1.0 });
        m_GraphicsContext->ClearDepthStencilBuffers(1.0f, 0);

        m_GraphicsContext->ApplyMaterial(*meshComponent.Material);
        m_GraphicsContext->Draw(*meshComponent.Mesh, Transforms);
    });

    /*if (ImGui::Begin("G-Buffer"))
    {
        if (GBuffer.IsCompiled)
        {
            ImGui::Image(ImGui::TexID(GBuffer.Targets[0]), { 512, 512 }); ImGui::SameLine(); ImGui::Image(ImGui::TexID(GBuffer.Targets[1]), { 512, 512 });
            ImGui::Image(ImGui::TexID(GBuffer.Targets[2]), { 512, 512 }); ImGui::SameLine(); ImGui::Image(ImGui::TexID(GBuffer.Targets[3]), { 512, 512 });
        }
    }
    ImGui::End();*/
}

}
