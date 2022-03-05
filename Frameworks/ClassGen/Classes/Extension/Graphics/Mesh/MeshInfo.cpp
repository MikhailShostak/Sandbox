#pragma once

namespace ClassGen
{

SharedReference<Graphics::Mesh>/*Mesh*/ MeshInfo::Load(Graphics::GraphicsContext& Context)
{
    if (MeshInstance)
    {
        return MeshInstance;
    }

    MeshInstance = Graphics::AssetLoader::LoadMesh(Path, Name);

    auto FileInfo = FindClassByName(Material);
    auto MaterialInfo = DynamicCast<ClassGen::MaterialInfo>(FileInfo.Instance);
    if (MaterialInfo)
    {
        MaterialInstance = MaterialInfo->Load(Context);
    }

    return MeshInstance;
}

}
