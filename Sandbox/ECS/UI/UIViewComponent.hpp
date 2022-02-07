#pragma once

namespace ECS
{
struct UIViewComponent
{
    using This = UIViewComponent;
    hlslpp::int3 Position;
    hlslpp::quaternion Rotation;
    hlslpp::int2 Size;
    UI::SizePolicy HorizontalSizePolicy;
    UI::SizePolicy VerticalSizePolicy;
    hlslpp::int3 GlobalPosition;
    hlslpp::int2 PreferedSize;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Position"] & Position;
        data["Rotation"] & Rotation;
        data["Size"] & Size;
        data["HorizontalSizePolicy"] & HorizontalSizePolicy;
        data["VerticalSizePolicy"] & VerticalSizePolicy;
    }
};
}
