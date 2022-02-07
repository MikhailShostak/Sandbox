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
    virtual std::tuple<bool/*Success*/> OnLayout(const ECS::Entity & Entity);
};
}
