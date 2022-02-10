#pragma once

namespace Graphics
{
struct Shader
{
    using This = Shader;
    String SourceCode = {};
    InplaceStorage<ShaderPrivateData, 8, 8> Data;
    Array<SharedReference<ShaderMetatype>> Constants = {};
    Array<SharedReference<ShaderMetatype>> Variables = {};
    SharedReference<ShaderMetatype> InputLayout = {};
    SharedReference<ShaderMetatype> OutputLayout = {};
    Shader();
    Shader(Shader &&other);
    Shader &operator =(Shader &&other);

     ~Shader();
    template<typename T>
    void Serialize(T &&data)
    {
    }

    void Initialize()
    {
    }
};
}
