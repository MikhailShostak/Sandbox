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
    virtual bool/*Success*/ OnPrePass(ECS::Entity & Entity);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
