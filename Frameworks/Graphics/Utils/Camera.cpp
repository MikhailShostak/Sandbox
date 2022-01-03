namespace Graphics
{

inline hlslpp::float4x4 GetOrthographicProjection(float Aspect, float NearPlane, float FarPlane)
{
    const hlslpp::frustum f(-Aspect, Aspect, -1.0, 1.0, NearPlane, FarPlane);
    return hlslpp::float4x4::orthographic(hlslpp::projection(f, hlslpp::zclip::zero));
}

inline hlslpp::float4x4 GetOrthographicProjection(hlslpp::float2 Resolution, float NearPlane, float FarPlane)
{
    return GetOrthographicProjection(Resolution.x / Resolution.y, NearPlane, FarPlane);
}

inline hlslpp::float4x4 GetPerspectiveProjection(float Aspect, float FieldOfView, float NearPlane, float FarPlane)
{
    const float RadiansRatio = (3.14 / 180.0L); //TODO: remove
    const float FieldOfViewInRadians = FieldOfView * RadiansRatio;
    const float HalfYFovTan = tan(FieldOfViewInRadians / 2.0f);

    hlslpp::float4x4 result;
    result._m00 = 1.0f / (Aspect * HalfYFovTan);
    result._m11 = 1.0f / (HalfYFovTan);
    result._m22 = (FarPlane + NearPlane) / (FarPlane - NearPlane);
    result._m23 = 1.0f;
    result._m32 = -(2.0f * FarPlane * NearPlane) / (FarPlane - NearPlane);
    return result;
}

inline hlslpp::float4x4 GetPerspectiveProjection(hlslpp::float2 Resolution, float FieldOfView, float NearPlane, float FarPlane)
{
    return GetPerspectiveProjection(Resolution.x / Resolution.y, FieldOfView, NearPlane, FarPlane);
}

Camera::Camera() :
    Resolution(hlslpp::int2{ 0, 0 }),
    NearPlane(0.01f),
    FarPlane(100.f),
    FieldOfView(45.0f)
{

}

std::tuple<hlslpp::float4x4/*Projection*/> Camera::GetOrthographicProjection()
{
    return { Graphics::GetOrthographicProjection(Resolution, NearPlane, FarPlane) };
}

std::tuple<hlslpp::float4x4/*Projection*/> Camera::GetPerspectiveProjection()
{
    return { Graphics::GetPerspectiveProjection(Resolution, FieldOfView, NearPlane, FarPlane) };
}

std::tuple<hlslpp::float4x4/*View*/> Camera::GetView()
{
    if (FieldOfView == 0.0f)
    {
        auto [projection] = GetOrthographicProjection();
        auto [view] = Transform.GetInverseMatrix();
        return { hlslpp::mul(view, projection) };
    }
    else
    {
        auto [projection] = GetPerspectiveProjection();
        auto [view] = Transform.GetInverseMatrix();
        return { hlslpp::mul(view, projection) };
    }
}

}
