#pragma once

namespace ECS
{
struct ImGuiSystem
    : public ECS::System
{
    using This = ImGuiSystem;
    using Super = ECS::System;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnLoad(EScene & Scene);
    virtual void OnUnload(EScene & Scene);
    virtual void OnUpdate(EScene & Scene);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
