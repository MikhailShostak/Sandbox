#pragma once

inline void CreatePreviewScene(EScene& instance)
{
    String Scene =
        R"(
Entities:
  - Name: Sky
    Components:
      - Type: ECS.TransformComponent
      - Type: ECS.MeshComponent
        Values:
          Mesh:
            Type: SkyMesh
          Material:
            Type: SkyMaterial
  - Name: PreviewMesh
    Components:
      - Type: ECS.TransformComponent
      - Type: ECS.MeshComponent
        Values:
          Mesh:
            Type: SphereMesh
          Material:
            Type: UVMaterial
)";
    Serialization::FromString<EScene>(Scene, instance);
};

#include <Utils/AssetLoader.hpp>
#include <PBR/PBRMaterial.hpp>
#include "MaterialGlobalConstants.hpp"

namespace ClassGen
{

SharedReference<Graphics::Material> CreateSimplePostEffect(
    Graphics::GraphicsContext& context,
    const SharedReference<Graphics::Texture>& baseColorTexture,
    const SharedReference<Graphics::Texture>& emission)
{
    auto MaterialInstance = CreateShared<Graphics::Material>();

    {
        Graphics::TextureSampler sampler;
        sampler.Name = "g_BaseColor";
        sampler.Texture = baseColorTexture;
        sampler.Flags = Graphics::ShaderFlags::UseInPixelShader;
        MaterialInstance->TextureSamplers.push_back(std::move(sampler));
    }
    {
        Graphics::TextureSampler sampler;
        sampler.Name = "g_Emission";
        sampler.Texture = emission;
        sampler.Flags = Graphics::ShaderFlags::UseInPixelShader;
        MaterialInstance->TextureSamplers.push_back(std::move(sampler));
    }
    MaterialInstance->Settings.DepthTestEnabled = false;
    MaterialInstance->Settings.DepthWriteEnabled = false;
    MaterialInstance->Settings.StencilEnabled = false;
    MaterialInstance->Settings.Cullback = false;

    MaterialInstance->VertexShader.InputLayout = CreateShared<VSInput>();
    MaterialInstance->VertexShader.OutputLayout = CreateShared<PSInput>();
    MaterialInstance->PixelShader.InputLayout = MaterialInstance->VertexShader.OutputLayout;
    MaterialInstance->PixelShader.OutputLayout = CreateShared<PSOutput>();

    MaterialInstance->VertexShader.SourceCode = R"(
    void main(in VSInput In, out PSInput Out)
    {
        float4x4 InstanceTransform = transpose(MatrixFromRows(In.MtrxRow0, In.MtrxRow1, In.MtrxRow2, In.MtrxRow3));
        Out.Pos = mul(InstanceTransform, float4(In.Pos.xyz, 1.0));
        Out.UV  = In.UV.xy;
    }
    )";

    MaterialInstance->PixelShader.SourceCode = R"(
    void main(in PSInput In, out PSOutput Out)
    {
        float Pi = 6.28318530718; // Pi*2
        float Directions = 32.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
        float Quality = 8.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
        float Radius = 0.05;
    
        float4 c = g_Emission.Sample(g_Emission_sampler, In.UV);
    
        // Blur calculations
        for(float d = 0.0; d < Pi; d += Pi / Directions)
        {
		    for(float i = 1.0 / Quality; i <= 1.0; i += 1.0 / Quality)
            {
                float2 uv = In.UV + float2(cos(d), sin(d)) * Radius.xx * i;
			    c.rgb += g_Emission.Sample(g_Emission_sampler, uv).r * g_BaseColor.Sample(g_BaseColor_sampler, uv).rgb;		
            }
        }
    
        // Output to screen
        c /= Quality * Directions - 15.0;

        Out.BaseColor = g_BaseColor.Sample(g_BaseColor_sampler, In.UV) + c;
    }
    )";

    return MaterialInstance;
}

PreviewViewport::PreviewViewport()
{
    CreatePreviewScene(*Viewport.ContentScene);
}

PreviewViewport::~PreviewViewport()
{
    g_DrawRequests.erase(this);
}

SharedReference<Graphics::Mesh> PostEffectMesh;
SharedReference<Graphics::Material> PostEffectMaterial;
Graphics::RenderTarget PostEffectBuffer;

void PreviewViewport::Load(Graphics::GraphicsContext& context)
{
    if (initislized)
    {
        return;
    }

    initislized = true;

    g_WhitePlaceholder = Graphics::CreateTexture(Color{ 1, 1, 1, 1 });//Graphics::LoadTexture("C:/Assets/Meshes/white.png");
    g_BlackPlaceholder = Graphics::CreateTexture(Color{ 0, 0, 0, 0 });//Graphics::LoadTexture("C:/Assets/Meshes/black.png");
    g_NormalPlaceholder = Graphics::CreateTexture(Color{ 0.5, 0.5, 1, 1 });//Graphics::LoadTexture("C:/Assets/Meshes/normal.png");

    //context.CreateDrawBatch(Transforms);

    /*PostEffectBuffer.Targets = {
        CreateShared<Graphics::Texture>(),
    };
    PostEffectBuffer.DepthStencil = CreateShared<Graphics::Texture>();
    PostEffectBuffer.Resize(Camera.Resolution);
    context.CreateRenderTarget(PostEffectBuffer);

    auto buffer = GBuffer.GetBuffer();
    g_DrawRequests.insert({ this, [&](auto& context) { Render(context); } });

    PostEffectMesh = AssetStorage::Load<Graphics::Mesh>("Z-PlainMesh");
    PostEffectMaterial = CreateSimplePostEffect(*g_GraphicsContext, GBuffer.Targets[0], GBuffer.Targets[3]);*/
}

void PreviewViewport::Render(Graphics::GraphicsContext& context)
{
    g_GlobalConstants->g_Time = std::chrono::duration_cast<DateTime::SecondRatio>(DateTime::HighResolution::Clock::now().time_since_epoch()).count();

    /*context.SetRenderBuffer(PostEffectBuffer.GetBuffer());
    context.ClearRenderBuffers({ 0.0, 0.0, 0.0, 0.0 });
    context.ClearDepthStencilBuffers(1.0f, 0);
    if (PostEffectMesh && PostEffectMaterial)
    {
        Transforms.Instances[0] = Matrix4::identity();
        context.ApplyMaterial(*PostEffectMaterial);
        context.Draw(*PostEffectMesh, Transforms);
    }*/
}

void PreviewViewport::SetMaterial(const SharedReference<Graphics::Material>& Material)
{
    auto meshComponent = ECS::FindPersistentComponent<ECS::MeshComponent>(*Viewport.ContentScene, "PreviewMesh");
    meshComponent->Material = Material;
}

void PreviewViewport::SetMesh(const SharedReference<Graphics::Mesh>& Mesh)
{
    auto meshComponent = ECS::FindPersistentComponent<ECS::MeshComponent>(*Viewport.ContentScene, "PreviewMesh");
    meshComponent->Mesh = Mesh;
}

void PreviewViewport::Draw(Graphics::GraphicsContext& context, const std::function<void()>& ToolBar)
{
    Viewport.Draw([&]()
    {
        if (ImGui::Button(ICON_VIDEOCAM.data()))
        {
            ImGui::OpenPopup("CameraContextMenu");
        }
        if (ImGui::BeginPopup("CameraContextMenu"))
        {
            auto [CameraComponent] = ECS::FindPersistentComponents<ECS::CameraComponent>(*Viewport.ViewportScene, "Camera");
            ImGui::DragFloat("Near Plane", &CameraComponent->Camera.NearPlane, 0.01f, 0.001f, 10000);
            ImGui::DragFloat("Far Plane", &CameraComponent->Camera.FarPlane, 0.01f, 0.001f, 10000);
            ImGui::DragFloat("FOV", &CameraComponent->Camera.FieldOfView, 0.1f, 1, 180);
            ImGui::EndPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button(ICON_360_ROTATION.data()))
        {
            rotate = !rotate;
        }

        if (rotate)
        {
            auto TransformComponent = ECS::FindPersistentComponent<ECS::TransformComponent>(*Viewport.ContentScene, "PreviewMesh");
            TransformComponent->Transform.Rotation.z += 0.1f;
        }

        ImGui::SameLine();

        if (ImGui::Button(ICON_PANORAMA1.data()))
        {
            auto MeshComponent = ECS::FindPersistentComponent<ECS::MeshComponent>(*Viewport.ContentScene, "Sky");
            MeshComponent->Visible = !MeshComponent->Visible;
        }

        ImGui::SameLine();

        if (ImGui::Button(ICON_MODEL.data()))
        {
            ImGui::OpenPopup("PreviewMeshContextMenu");
        }
        if (ImGui::BeginPopup("PreviewMeshContextMenu"))
        {
            static String AvaiableMeshes[] = {
                "Cone",
                "Cube",
                "Cylinder",
                "Sphere",
                "Icosphere",
                "Suzanne",
                "Torus",
                "X-Plane",
                "Y-Plane",
                "Z-Plane",
            };

            for (const auto& mesh : AvaiableMeshes)
            {
                if (ImGui::Selectable(mesh.data()))
                {
                    SetMesh(Graphics::AssetLoader::LoadMesh(EditorContentPath, mesh));
                }
            }
            ImGui::EndPopup();
        }

        if (ToolBar)
        {
            ToolBar();
        }
    });
}

}
