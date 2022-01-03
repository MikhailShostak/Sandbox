#pragma once

namespace Graphics
{
struct Transform
{
    using This = Transform;
    hlslpp::float3 Position;
    hlslpp::quaternion Rotation;

    template<typename T>
    void Serialize(T &&data)
    {
        data["Position"] & Position;
        data["Rotation"] & Rotation;
    }
    virtual std::tuple<hlslpp::float4x4/*Transform*/> GetMatrix();
    virtual std::tuple<hlslpp::float4x4/*Transform*/> GetInverseMatrix();
};
}
