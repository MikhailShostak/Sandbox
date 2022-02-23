#pragma once

#include <Utils/AssetLoader.hpp>
#include <PBR/PBRMaterial.hpp>
#include "MaterialGlobalConstants.hpp"

namespace ClassGen
{


PreviewViewport::PreviewViewport()
{
    Transforms.Instances.resize(1);
    Transforms.Instances[0] = Matrix4::identity();
    Transforms.MaxSize = 1;

    Camera.Transform.Position = { 0, 3, 1 };
    Camera.Transform.Rotation.x = 20;
    Camera.Resolution = { 512, 512 };
    Camera.FarPlane = 200;
}

PreviewViewport::~PreviewViewport()
{
    g_DrawRequests.erase(this);
}

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

    context.CreateDrawBatch(Transforms);

    GBuffer.Targets = {
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
        CreateShared<Graphics::Texture>(),
    };
    GBuffer.DepthStencil = CreateShared<Graphics::Texture>();

    GBuffer.Resize(Camera.Resolution);
    context.CreateRenderTarget(GBuffer);

    auto buffer = GBuffer.GetBuffer();
    g_DrawRequests.insert({ this, [&](auto& context) { Render(context); } });

    Mesh = Graphics::AssetLoader::LoadMesh(EditorContentPath, MeshName);

    auto UVFileInfo = FindClassByName("UVMaterial");
    auto UVMaterialInfo = DynamicCast<ClassGen::MaterialInfo>(UVFileInfo.Instance);
    if (UVMaterialInfo)
    {
        Material = UVMaterialInfo->Load(*g_GraphicsContext, buffer);
    }

    auto SkyFileInfo = FindClassByName("SkyMesh");
    auto SkyMeshInfo = DynamicCast<ClassGen::MeshInfo>(SkyFileInfo.Instance);
    if (SkyMeshInfo)
    {
        SkyMesh = SkyMeshInfo->Load(*g_GraphicsContext, buffer);
        SkyMaterial = SkyMeshInfo->MaterialInstance;
    }
}

void PreviewViewport::Render(Graphics::GraphicsContext& context)
{
    context.SetRenderBuffer(GBuffer.GetBuffer());
    context.ClearRenderBuffers({ 0.0, 0.0, 0.0, 0.0 });
    context.ClearDepthStencilBuffers(1.0f, 0);

    g_CameraConstants->g_ViewProj = Camera.GetView();

    if (sky && SkyMesh && SkyMaterial)
    {
        context.ApplyMaterial(*SkyMaterial);
        context.Upload(Transforms);
        context.Draw(*SkyMesh, Transforms);
    }

    if (Mesh && Material)
    {
        g_GlobalConstants->g_Time =
            std::chrono::duration_cast<DateTime::SecondRatio>(DateTime::HighResolution::Clock::now().time_since_epoch()).count();
            //-std::chrono::duration_cast<DateTime::Seconds>(DateTime::HighResolution::Clock::now().time_since_epoch()).count();

        context.ApplyMaterial(*Material);
        context.Draw(*Mesh, Transforms);
    }
}

void PreviewViewport::Draw(Graphics::GraphicsContext& context, const std::function<void()>& ToolBar)
{
    auto& texture = GBuffer.Targets[0];
    ImVec2 size{ (float)texture->Size.x, (float)texture->Size.y };
    ImVec2 padding = ImVec2(2, 2);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, padding);
    if (ImGui::BeginChild("PreviewViewport", size + padding * 2, true))
    {
        ImGui::Image(ImGui::TexID(texture), size);

        ImGui::SetCursorPos(ImGui::GetCursorPos() - ImVec2{ 0, size.y } + ImVec2(4, 4));

        if (ImGui::Button(ICON_VIDEOCAM.data()))
        {
            ImGui::OpenPopup("CameraContextMenu");
        }
        if (ImGui::BeginPopup("CameraContextMenu"))
        {
            ImGui::DragFloat3("Position", Camera.Transform.Position.f32, 0.01f, -100, 100);
            ImGui::DragFloat3("Rotation", Camera.Transform.Rotation.f32, 1.0f, -180, 180);
            //ImGui::SliderFloat3("Camera Rotation", g_Camera.Transform.Rotation.f32, 0, 360);
            ImGui::DragFloat("Near Plane", &Camera.NearPlane, 0.01f, 0.001f, 10000);
            ImGui::DragFloat("Far Plane", &Camera.FarPlane, 0.01f, 0.001f, 10000);
            ImGui::DragFloat("FOV", &Camera.FieldOfView, 0.1f, 1, 180);
            if (ImGui::DragInt2("Resolution", Camera.Resolution.i32, 1.0f, 1, 2048))
            {
                GBuffer.Targets = {
                    CreateShared<Graphics::Texture>(),
                    CreateShared<Graphics::Texture>(),
                    CreateShared<Graphics::Texture>(),
                    CreateShared<Graphics::Texture>(),
                };
                GBuffer.DepthStencil = CreateShared<Graphics::Texture>();
                GBuffer.Resize(Camera.Resolution);
                context.CreateRenderTarget(GBuffer);
            }
            ImGui::EndPopup();
        }

        ImGui::SameLine();

        if (ImGui::Button(ICON_360_ROTATION.data()))
        {
            rotate = !rotate;
        }

        if (rotate)
        {
            rotationAngle += 0.1f;
            Transforms.Instances[0] = Matrix4(hlslpp::axisangle(hlslpp::normalize(Float3(0, 0, 1)), rotationAngle * (3.14 / 180)));
        }

        ImGui::SameLine();

        if (ImGui::Button(ICON_PANORAMA1.data()))
        {
            sky = !sky;
        }

        ImGui::SameLine();

        if (ImGui::Button(ICON_MODEL.data()))
        {
            ImGui::OpenPopup("PreviewMeshContextMenu");
        }
        if (ImGui::BeginPopup("PreviewMeshContextMenu"))
        {
            auto SetPreviewMesh = [this](const String& name)
            {
                MeshName = name;
                Mesh = Graphics::AssetLoader::LoadMesh(EditorContentPath, MeshName);
            };

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
                    SetPreviewMesh(mesh);
                }
            }
            ImGui::EndPopup();
        }

        if (ToolBar)
        {
            ToolBar();
        }
    }
    ImGui::EndChild();
    ImGui::PopStyleVar();
}

}
