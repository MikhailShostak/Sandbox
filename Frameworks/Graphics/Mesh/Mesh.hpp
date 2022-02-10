#pragma once

namespace Graphics
{
struct Mesh
{
    using This = Mesh;
    Array<Vertex> Vertices = {};
    Array<Face> Faces = {};
    InplaceStorage<MeshPrivateData, 16, 8> Data;
    bool IsCompiled = {};
    Mesh();
    Mesh(Mesh &&other);
    Mesh &operator =(Mesh &&other);

     ~Mesh();
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
}
