#pragma once

namespace ECS
{
struct EmptySystem
    : public ECS::System
{
    using This = EmptySystem;
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
