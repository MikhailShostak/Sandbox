#pragma once

#include "SceneViewport.hpp"

namespace ClassGen
{

struct PreviewViewport
{
    SceneViewport Viewport;

    inline static String EditorContentPath = "C:/Assets/EditorContent.fbx";

    SharedReference<Graphics::Texture> Texture;

    bool initislized = false;
    bool rotate = true;

    PreviewViewport();
    ~PreviewViewport();

    void SetMaterial(const SharedReference<Graphics::Material>& Material);
    void SetMesh(const SharedReference<Graphics::Mesh>& Mesh);

    void Load(Graphics::GraphicsContext& context);
    void Render(Graphics::GraphicsContext& context);
    void UpdateCameraRotation();
    void Draw(Graphics::GraphicsContext& context, const std::function<void()>& ToolBar = nullptr);
};

}
