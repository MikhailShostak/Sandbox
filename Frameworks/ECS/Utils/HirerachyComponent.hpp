#pragma once

namespace ECS
{
struct HirerachyComponent
    : public ECS::EntityComponent
{
    using This = HirerachyComponent;
    using Super = ECS::EntityComponent;
    std::optional<ECS::Entity> Parent = {};
    Array<ECS::Entity> Children = {};

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
