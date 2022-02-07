#pragma once

namespace ECS
{
struct LayoutSystem
    : public ECS::System
{
    using This = LayoutSystem;
    using Super = ECS::System;
    Array<UniqueReference<UI::Layout>> Layouts;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void OnUpdate();
};
}
