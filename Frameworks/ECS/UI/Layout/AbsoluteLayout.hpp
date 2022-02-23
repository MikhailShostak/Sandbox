#pragma once

namespace UI
{
struct AbsoluteLayout
    : public UI::Layout
{
    using This = AbsoluteLayout;
    using Super = UI::Layout;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual bool/*Success*/ OnLayout(ECS::Entity & Entity);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
