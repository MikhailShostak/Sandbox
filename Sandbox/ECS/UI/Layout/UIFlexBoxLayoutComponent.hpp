#pragma once

namespace ECS
{
struct UIFlexBoxLayoutComponent
{
    using This = UIFlexBoxLayoutComponent;
    hlslpp::int2 StartPadding;
    hlslpp::int2 EndPadding;
    int32_t Spacing;
    UI::Direction Direction;

    template<typename T>
    void Serialize(T &&data)
    {
        data["StartPadding"] & StartPadding;
        data["EndPadding"] & EndPadding;
        data["Spacing"] & Spacing;
        data["Direction"] & Direction;
    }
};
}
