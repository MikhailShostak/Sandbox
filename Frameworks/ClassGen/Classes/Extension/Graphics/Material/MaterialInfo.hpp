#pragma once

namespace ClassGen
{
struct MaterialInfo
    : public ClassGen::BaseInfo
{
    using This = MaterialInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};
    String Name = {};
    Array<ClassGen::MaterialProperty> Properties = {};
    Array<ClassGen::TextureSamplerInfo> Textures = {};
    System::Path VertexShader = {};
    System::Path PixelShader = {};
    SharedReference<Graphics::Material> MaterialInstance = {};
    Array<Graphics::TextureSampler> Samplers = {};

    virtual ~MaterialInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
        data["Name"] & Name;
        data["Properties"] & Properties;
        data["Textures"] & Textures;
        data["VertexShader"] & VertexShader;
        data["PixelShader"] & PixelShader;
    }
    virtual SharedReference<Graphics::Material>/*Material*/ Load(Graphics::GraphicsContext & Context, const Graphics::RenderBuffer & RenderBuffer);
    virtual void Update();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
