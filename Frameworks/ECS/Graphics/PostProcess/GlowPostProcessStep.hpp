#pragma once

namespace ECS
{
struct GlowPostProcessStep
    : public ECS::PostProcessStep
{
    using This = GlowPostProcessStep;
    using Super = ECS::PostProcessStep;

    virtual ~GlowPostProcessStep() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Render(EScene & Scene, const Graphics::RenderBuffer & RenderBuffer);

    void Initialize()
    {
        Super::Initialize();
        {
            String data =
R"(
Type: GlowMaterial
)";
            Serialization::FromString(data, Material);
        }
    }
};
}
