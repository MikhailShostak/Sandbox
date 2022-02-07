#pragma once

namespace UI
{
struct ImageLayout
    : public UI::Layout
{
    using This = ImageLayout;
    using Super = UI::Layout;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<bool/*Success*/> OnPrePass(const ECS::Entity & Entity);
};
}
