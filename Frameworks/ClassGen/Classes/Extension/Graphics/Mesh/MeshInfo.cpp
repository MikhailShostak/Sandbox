#pragma once

namespace ClassGen
{

SharedReference<Graphics::Mesh>/*Mesh*/ MeshInfo::Load(Graphics::GraphicsContext& Context, const Graphics::RenderBuffer &RenderBuffer)
{
    if (MeshInstance)
    {
        return MeshInstance;
    }

    MeshInstance = Graphics::AssetLoader::LoadMesh(Path, Name);
    if (MeshInstance)
    {
        Context.CreateMesh(*MeshInstance);
    }

    auto FileInfo = FindClassByName(Material);
    auto MaterialInfo = DynamicCast<ClassGen::MaterialInfo>(FileInfo.Instance);
    if (MaterialInfo)
    {
        MaterialInstance = MaterialInfo->Load(Context, RenderBuffer);
    }

    return MeshInstance;
}

}
