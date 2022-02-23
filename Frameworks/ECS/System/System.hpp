#pragma once

namespace ECS
{
struct System
{
    using This = System;
    Graphics::GraphicsContext* m_GraphicsContext = {};
    Int2 m_Resolution = {};

    virtual ~System() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnLoad(EScene & Scene);
    virtual void OnUnload(EScene & Scene);
    virtual void OnUpdate(EScene & Scene);

    void Initialize()
    {
    }
};
}
