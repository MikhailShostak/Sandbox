#pragma once

namespace UI
{
struct TextLayout
    : public UI::Layout
{
    using This = TextLayout;
    using Super = UI::Layout;

    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual std::tuple<bool/*Success*/> OnPrePass(const ECS::Entity & Entity);
};
}
