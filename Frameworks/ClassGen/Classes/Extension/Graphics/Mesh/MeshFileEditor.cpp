#include <Utils/AssetLoader.hpp>
#include <PBR/PBRMaterial.hpp>

namespace ClassGen
{

struct PreviewViewport
{
    Graphics::AssetLoader Loader;
    SharedReference<Graphics::Mesh> Mesh;
    SharedReference<Graphics::Material> Material;

    Graphics::RenderTarget GBuffer;
    Graphics::DrawBatch<Matrix4> Transforms;
    Graphics::Camera Camera;

    SharedReference<Graphics::Texture> Texture;

    bool initislized = false;

    PreviewViewport()
    {
        Transforms.Instances.resize(1);
        Transforms.MaxSize = 1;

        Camera.Resolution = { 512, 512 };
    }

    void LoadContent(Graphics::GraphicsContext& context, const System::Path &path)
    {
        Mesh.reset();
        Material.reset();

        Loader.Clear();
        auto [buffer] = GBuffer.GetBuffer();
        Loader.Load(context, buffer, path);
        if (Loader.Meshes.size() > 0)
        {
            Mesh = Loader.Meshes[0].first;
            Material = Loader.Meshes[0].second;
        }
    }

    void Load(Graphics::GraphicsContext& context)
    {
        if (initislized)
        {
            return;
        }

        initislized = true;

        //g_Placeholder = Graphics::LoadTexture("C:/Assets/Meshes/uv.jpg");


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

        auto [buffer] = GBuffer.GetBuffer();
        g_DrawRequests.insert({ this, [&](auto& context) { Render(context); } });
    }

    void Render(Graphics::GraphicsContext& context)
    {
        const auto& [buffer] = GBuffer.GetBuffer();
        context.SetRenderBuffer(buffer);
        context.ClearRenderBuffers({ 0.0, 0.0, 0.0, 0.0 });
        context.ClearDepthStencilBuffers(1.0f, 0);

        auto [ViewProjectMatrix] = Camera.GetView();
        g_CameraConstants->g_ViewProj = ViewProjectMatrix;

        Transforms.Instances[0] = Matrix4::identity();

        if (Mesh && Material)
        {
            context.ApplyMaterial(*Material);
            context.Upload(Transforms);
            context.Draw(*Mesh, Transforms);
        }
    }

    void Draw(Graphics::GraphicsContext& context)
    {
        ImGui::SliderFloat3("Position", Camera.Transform.Position.f32, -100, 100);
        static Float3 rotation;
        static float angle = 0;
        ImGui::SliderFloat3("Rotation Axis", rotation.f32, -1, 1);
        ImGui::SliderFloat("Rotation Angle", &angle, -360, 360);
        Camera.Transform.Rotation = hlslpp::axisangle(hlslpp::normalize(rotation), angle * (3.14 / 180));
        //ImGui::SliderFloat3("Camera Rotation", g_Camera.Transform.Rotation.f32, 0, 360);
        ImGui::InputFloat("Near Plane", &Camera.NearPlane);
        ImGui::InputFloat("Far Plane", &Camera.FarPlane);
        ImGui::InputFloat("FOV", &Camera.FieldOfView);
        if (ImGui::SliderInt2("Resolution", Camera.Resolution.i32, 1, 2048))
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

        auto& texture = GBuffer.Targets[0];
        ImGui::Image(ImGui::TexID(texture), { (float)texture->Size.x, (float)texture->Size.y });
    }

};

PreviewViewport preview;

void MeshFileEditor::RenderFile()
{
    preview.Load(*g_GraphicsContext);

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

        preview.LoadContent(*g_GraphicsContext, info.Path);
    }

    preview.Draw(*g_GraphicsContext);
}

}
