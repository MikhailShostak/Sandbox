namespace Graphics
{

inline Matrix4 GetOrthographicProjection(float Aspect, float NearPlane, float FarPlane)
{
    const hlslpp::frustum f(-Aspect, Aspect, -1.0, 1.0, NearPlane, FarPlane);
    return Matrix4::orthographic(hlslpp::projection(f, hlslpp::zclip::zero));
}

inline Matrix4 GetOrthographicProjection(Float2 Resolution, float NearPlane, float FarPlane)
{
    return GetOrthographicProjection(Resolution.x / Resolution.y, NearPlane, FarPlane);
}

inline Matrix4 GetPerspectiveProjection(float Aspect, float FieldOfView, float NearPlane, float FarPlane)
{
    const float RadiansRatio = (3.14 / 180.0L); //TODO: remove
    const float FieldOfViewInRadians = FieldOfView * RadiansRatio;
    const float HalfYFovTan = tan(FieldOfViewInRadians / 2.0f);

    Matrix4 result;
    result._m00 = 1.0f / (Aspect * HalfYFovTan);
    result._m11 = 1.0f / (HalfYFovTan);
    result._m22 = (FarPlane + NearPlane) / (FarPlane - NearPlane);
    result._m23 = 1.0f;
    result._m32 = -(2.0f * FarPlane * NearPlane) / (FarPlane - NearPlane);
    return result;
}

inline Matrix4 GetPerspectiveProjection(Float2 Resolution, float FieldOfView, float NearPlane, float FarPlane)
{
    return GetPerspectiveProjection(Resolution.x / Resolution.y, FieldOfView, NearPlane, FarPlane);
}

Camera::Camera() :
    Resolution(Int2{ 0, 0 }),
    NearPlane(0.01f),
    FarPlane(100.f),
    FieldOfView(45.0f)
{

}

Matrix4/*Projection*/ Camera::GetOrthographicProjection()
{
    return Graphics::GetOrthographicProjection(Resolution, NearPlane, FarPlane);
}

Matrix4/*Projection*/ Camera::GetPerspectiveProjection()
{
    return Graphics::GetPerspectiveProjection(Resolution, FieldOfView, NearPlane, FarPlane);
}

Matrix4/*View*/ Camera::GetView()
{
    auto projection = FieldOfView == 0.0f ? GetOrthographicProjection() : GetPerspectiveProjection();
    auto view = Transform.GetInverseMatrix();
    view = mul(Matrix4(hlslpp::axisangle({ 1, 0, 0 }, hlslpp::radians(hlslpp::float1{ 90 }))), view);
    return hlslpp::mul(view, projection);
}

}
