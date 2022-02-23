#pragma once

struct SceneViewport
{
    using This = SceneViewport;
    SharedReference<EScene> ContentScene = {};
    SharedReference<EScene> ViewportScene = {};
    SharedReference<Graphics::Texture> Texture = {};
    Int2 LastSize = {};
    float MSAAFactor = {};
    SceneViewport();

    virtual ~SceneViewport();
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw(const std::function<void()> & Toolbar);
    virtual void Resize(const Int2 & Size);

    void Initialize()
    {
    }
};
