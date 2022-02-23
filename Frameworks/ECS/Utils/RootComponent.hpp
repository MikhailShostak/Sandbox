#pragma once

namespace ECS
{
struct RootComponent
    : public ECS::EntityComponent
{
    using This = RootComponent;
    using Super = ECS::EntityComponent;

    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
