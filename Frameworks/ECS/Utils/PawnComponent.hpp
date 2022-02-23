#pragma once

namespace ECS
{
struct PawnComponent
    : public ECS::EntityComponent
{
    using This = PawnComponent;
    using Super = ECS::EntityComponent;
    float Mobility = {};
    float Speed = {};
    bool RelativeInput = {};
    Float3 InputVector = {};
    Quaternion Rotation = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Mobility"] & Mobility;
        data["Speed"] & Speed;
        data["RelativeInput"] & RelativeInput;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
