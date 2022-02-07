#pragma once

namespace ECS
{
struct TransformComponent
    : public Graphics::Transform
{
    using This = TransformComponent;
    using Super = Graphics::Transform;
    hlslpp::float3 Scale;
    TransformComponent();

    template<typename T>
    void Serialize(T &&data)
    {
        data["Scale"] & Scale;
    }
};
}
