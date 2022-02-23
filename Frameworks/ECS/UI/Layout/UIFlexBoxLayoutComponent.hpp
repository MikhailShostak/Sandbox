#pragma once

namespace ECS
{
struct UIFlexBoxLayoutComponent
    : public ECS::EntityComponent
{
    using This = UIFlexBoxLayoutComponent;
    using Super = ECS::EntityComponent;
    Int2 StartPadding = {};
    Int2 EndPadding = {};
    int32_t Spacing = {};
    UI::Direction Direction = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["StartPadding"] & StartPadding;
        data["EndPadding"] & EndPadding;
        data["Spacing"] & Spacing;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
