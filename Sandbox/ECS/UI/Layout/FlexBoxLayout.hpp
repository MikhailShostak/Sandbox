#pragma once

namespace UI
{
struct FlexBoxLayout
    : public UI::Layout
{
    using This = FlexBoxLayout;
    using Super = UI::Layout;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<bool/*Success*/> OnPrePass(const ECS::Entity & Entity);
    virtual std::tuple<bool/*Success*/> OnLayout(const ECS::Entity & Entity);
};
}
