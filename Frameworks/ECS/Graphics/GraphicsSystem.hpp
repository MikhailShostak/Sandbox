#pragma once

namespace ECS
{
struct GraphicsSystem
    : public ECS::System
{
    using This = GraphicsSystem;
    using Super = ECS::System;
    Graphics::DrawBatch<hlslpp::float4x4> Transforms = {};
    Graphics::RenderTarget GBuffer = {};
    ECS::Entity CurrentCamera = {};
    Array<UniqueReference<ECS::PostProcessStep>> PostProcessSteps = {};
    StaticArray<Graphics::RenderTarget, 2> RenderTargets = {};
    size_t CurrentTarget = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["CurrentCamera"] & CurrentCamera;
        data["PostProcessSteps"] & PostProcessSteps;
    }
    virtual void OnLoad(EScene & Scene);
    virtual void OnUnload(EScene & Scene);
    virtual void OnUpdate(EScene & Scene);
    virtual void Render(EScene & Scene);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
