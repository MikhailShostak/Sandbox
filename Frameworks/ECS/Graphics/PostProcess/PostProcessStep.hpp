#pragma once

namespace ECS
{
struct PostProcessStep
{
    using This = PostProcessStep;
    SharedReference<Graphics::Material> Material = {};

    virtual ~PostProcessStep() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Material"] & Material;
    }
    virtual void Render(EScene & Scene, const Graphics::RenderBuffer & RenderBuffer);

    void Initialize()
    {
    }
};
}
