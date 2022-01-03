#pragma once

namespace Graphics
{
struct Mesh
{
    using This = Mesh;
    Array<Vertex> Vertices;
    Array<Face> Faces;
    InplaceStorage<MeshPrivateData, 16, 8> Data;
    Mesh();
    ~Mesh();

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
