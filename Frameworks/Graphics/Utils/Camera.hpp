#pragma once

namespace Graphics
{
struct Camera
{
    using This = Camera;
    Graphics::Transform Transform;
    hlslpp::int2 Resolution;
    float NearPlane;
    float FarPlane;
    float FieldOfView;
    Camera();

    template<typename T>
    void Serialize(T &&data)
    {
        data["Resolution"] & Resolution;
        data["NearPlane"] & NearPlane;
        data["FarPlane"] & FarPlane;
        data["FieldOfView"] & FieldOfView;
    }
    virtual std::tuple<hlslpp::float4x4/*Projection*/> GetOrthographicProjection();
    virtual std::tuple<hlslpp::float4x4/*Projection*/> GetPerspectiveProjection();
    virtual std::tuple<hlslpp::float4x4/*View*/> GetView();
};
}
