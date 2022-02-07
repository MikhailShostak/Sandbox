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
    virtual void OnLoad();
    virtual void OnUnload();
    virtual void OnUpdate();
};
}
