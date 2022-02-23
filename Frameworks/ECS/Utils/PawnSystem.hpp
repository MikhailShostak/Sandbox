#pragma once

namespace ECS
{
struct PawnSystem
    : public ECS::System
{
    using This = PawnSystem;
    using Super = ECS::System;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnUpdate(EScene & Scene);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
