namespace Graphics
{

Transform::Transform():
    Scale(1)
{

}

bool IsValid(const hlslpp::quaternion &q)
{
    return std::isfinite(q.f32[0]) && std::isfinite(q.f32[1]) && std::isfinite(q.f32[2]) && std::isfinite(q.f32[3]);
}

Matrix4/*Transform*/ Transform::GetMatrix()
{
    Matrix4 result = Matrix4::translation(Position);
    auto r = hlslpp::euler(hlslpp::radians(Rotation));
    if (IsValid(r))
    {
        result = hlslpp::mul(Matrix4(r), result);
    }
    return result;
}

Matrix4/*Transform*/ Transform::GetInverseMatrix()
{
    Matrix4 result = Matrix4::translation(-Position);
    auto r = hlslpp::euler(hlslpp::radians(Rotation));
    if (IsValid(r))
    {
        result = hlslpp::mul(result, Matrix4(r));
    }
    return result;
}


}
