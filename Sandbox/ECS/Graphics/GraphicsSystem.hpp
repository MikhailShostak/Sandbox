#pragma once

namespace ECS
{
struct GraphicsSystem
    : public ECS::System
{
    using This = GraphicsSystem;
    using Super = ECS::System;
    Graphics::DrawBatch<hlslpp::float4x4> Transforms;
    Graphics::RenderTarget GBuffer;
    ECS::Entity CurrentCamera;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnLoad();
    virtual void OnUnload();
    virtual void OnUpdate();
};
}
