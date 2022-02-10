#pragma once

namespace Graphics
{
struct Transform
{
    using This = Transform;
    Float3 Position = {};
    Float3 Rotation = {};
    Float3 Scale = {};
    Transform();

    template<typename T>
    void Serialize(T &&data)
    {
        data["Position"] & Position;
        data["Rotation"] & Rotation;
        data["Scale"] & Scale;
    }
    virtual Matrix4/*Transform*/ GetMatrix();
    virtual Matrix4/*Transform*/ GetInverseMatrix();

    void Initialize()
    {
    }
};
}
