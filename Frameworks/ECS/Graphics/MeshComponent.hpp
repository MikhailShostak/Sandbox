#pragma once

namespace ECS
{
struct MeshComponent
    : public ECS::EntityComponent
{
    using This = MeshComponent;
    using Super = ECS::EntityComponent;
    SharedReference<Graphics::Mesh> Mesh = {};
    SharedReference<Graphics::Material> Material = {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Mesh"] & Mesh;
        data["Material"] & Material;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
