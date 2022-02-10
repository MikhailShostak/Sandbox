#pragma once

namespace ClassGen
{
struct MeshInfo
    : public ClassGen::BaseInfo
{
    using This = MeshInfo;
    using Super = ClassGen::BaseInfo;
    System::Path Path = {};
    String Name = {};
    String Material = {};
    SharedReference<Graphics::Mesh> MeshInstance = {};
    SharedReference<Graphics::Material> MaterialInstance = {};

    virtual ~MeshInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Path"] & Path;
        data["Name"] & Name;
        data["Material"] & Material;
    }
    virtual SharedReference<Graphics::Mesh>/*Mesh*/ Load(Graphics::GraphicsContext & Context, const Graphics::RenderBuffer & RenderBuffer);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
