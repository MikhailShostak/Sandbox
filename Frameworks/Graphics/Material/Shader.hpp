#pragma once

namespace Graphics
{
struct Shader
{
    using This = Shader;
    String SourceCode;
    InplaceStorage<ShaderPrivateData, 8, 8> Data;
    Array<SharedReference<ShaderMetatype>> Constants;
    Array<SharedReference<ShaderMetatype>> Variables;
    SharedReference<ShaderMetatype> InputLayout;
    SharedReference<ShaderMetatype> OutputLayout;
    Shader();
    ~Shader();

    template<typename T>
    void Serialize(T &&data)
    {
    }
};
}
