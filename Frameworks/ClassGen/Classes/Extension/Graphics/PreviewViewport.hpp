#pragma once

namespace ClassGen
{

struct PreviewViewport
{
    inline static String EditorContentPath = "C:/Assets/EditorContent.fbx";
    String MeshName = "Sphere";

    SharedReference<Graphics::Mesh> SkyMesh;
    SharedReference<Graphics::Material> SkyMaterial;

    SharedReference<Graphics::Mesh> Mesh;
    SharedReference<Graphics::Material> Material;

    Graphics::RenderTarget GBuffer;
    Graphics::DrawBatch<Matrix4> Transforms;
    Graphics::Camera Camera;

    SharedReference<Graphics::Texture> Texture;

    bool initislized = false;

    bool sky = true;
    bool rotate = true;
    float rotationAngle = 0;

    Float3 CameraRotation{ 1, 0, 0 };
    float CameraRotationAngle = 90;

    PreviewViewport();
    ~PreviewViewport();
    void Load(Graphics::GraphicsContext& context);
    void Render(Graphics::GraphicsContext& context);
    void UpdateCameraRotation();
    void Draw(Graphics::GraphicsContext& context, const std::function<void()>& ToolBar = nullptr);
};

}
