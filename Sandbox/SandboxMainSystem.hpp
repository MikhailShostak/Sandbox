#pragma once

struct SandboxMainSystem
    : public ECS::System
{
    using This = SandboxMainSystem;
    using Super = ECS::System;

    virtual ~SandboxMainSystem() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnLoad(EScene & Scene);

    void Initialize()
    {
        Super::Initialize();
    }
};
