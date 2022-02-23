#pragma once

namespace ECS
{
struct UIViewComponent
    : public ECS::EntityComponent
{
    using This = UIViewComponent;
    using Super = ECS::EntityComponent;
    Int3 Position = {};
    Quaternion Rotation = {};
    Int2 Size = {};
    UI::SizePolicy HorizontalSizePolicy = {};
    UI::SizePolicy VerticalSizePolicy = {};
    Int3 GlobalPosition = {};
    Int2 PreferedSize = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Position"] & Position;
        data["Rotation"] & Rotation;
        data["Size"] & Size;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
