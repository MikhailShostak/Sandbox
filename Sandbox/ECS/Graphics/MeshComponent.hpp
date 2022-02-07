#pragma once

namespace ECS
{
struct MeshComponent
{
    using This = MeshComponent;
    SharedReference<Graphics::Mesh> Mesh;
    SharedReference<Graphics::Material> Material;

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
