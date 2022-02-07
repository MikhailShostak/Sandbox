#pragma once

namespace ECS
{
struct HirerachyComponent
{
    using This = HirerachyComponent;
    std::optional<ECS::Entity> Parent;
    Array<ECS::Entity> Children;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
