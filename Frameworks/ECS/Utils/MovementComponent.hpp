#pragma once

namespace ECS
{
struct MovementComponent
    : public ECS::EntityComponent
{
    using This = MovementComponent;
    using Super = ECS::EntityComponent;
    Float3 Acceleration = {};
    Float3 Velocity = {};
    float Mass = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Acceleration"] & Acceleration;
        data["Velocity"] & Velocity;
        data["Mass"] & Mass;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
