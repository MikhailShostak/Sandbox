#pragma once

namespace Graphics
{

struct AssetLoader
{
    Array<SharedReference<Graphics::Texture>> Textures;
    Array<std::pair<SharedReference<Graphics::Mesh>, SharedReference<Graphics::Material>>> Meshes;
    Array<SharedReference<Graphics::Material>> Materials;

    static SharedReference<Graphics::Mesh> LoadMesh(const System::Path& path, const String& name);
    static SharedReference<Graphics::Material> LoadMaterial(const System::Path& path, const String& name);

    void Load(Graphics::GraphicsContext &Context, Graphics::RenderBuffer &RenderBuffer, const System::Path &Path);
    void Clear();
};

}
