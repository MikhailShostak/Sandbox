#pragma once

namespace Graphics
{
struct Camera
{
    using This = Camera;
    Graphics::Transform Transform = {};
    Int2 Resolution = {};
    float NearPlane = {};
    float FarPlane = {};
    float FieldOfView = {};
    Camera();

    template<typename T>
    void Serialize(T &&data)
    {
        data["Transform"] & Transform;
        data["Resolution"] & Resolution;
        data["NearPlane"] & NearPlane;
        data["FarPlane"] & FarPlane;
        data["FieldOfView"] & FieldOfView;
    }
    virtual Matrix4/*Projection*/ GetOrthographicProjection();
    virtual Matrix4/*Projection*/ GetPerspectiveProjection();
    virtual Matrix4/*View*/ GetView();

    void Initialize()
    {
    }
};
}
