namespace Graphics
{

bool IsValid(const hlslpp::quaternion &q)
{
    return std::isfinite(q.f32[0]) && std::isfinite(q.f32[1]) && std::isfinite(q.f32[2]) && std::isfinite(q.f32[3]);
}

std::tuple<hlslpp::float4x4/*Transform*/> Transform::GetMatrix()
{
    hlslpp::float4x4 result = hlslpp::float4x4::translation(Position);
    if (IsValid(Rotation))
    {
        result = mul(hlslpp::float4x4(Rotation), result);
    }
    return { result };
}

std::tuple<hlslpp::float4x4/*Transform*/> Transform::GetInverseMatrix()
{
    hlslpp::float4x4 result = hlslpp::float4x4::translation(-Position);
    if (IsValid(Rotation))
    {
        result = mul(result, hlslpp::float4x4(Rotation));
    }
    return { result };
}


}
