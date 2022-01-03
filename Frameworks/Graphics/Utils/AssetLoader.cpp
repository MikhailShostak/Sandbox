#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "PBRMaterial.hpp"

namespace Graphics
{

template<typename Functor>
void LoadScene(const System::Path& path, Functor&& functor)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path.generic_string(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
    if (!scene)
    {
        return;
    }

    functor(*scene);
}

void LoadTextures(Graphics::AssetLoader &loader, const aiScene *scene)
{
    auto loadTexture = [](const aiTexture *t)
    {
        auto r = CreateShared<Graphics::Texture>();

        r->Size = { t->mWidth, t->mHeight, 1 };
        r->Channels = 4;
        size_t s = t->mWidth * t->mHeight;
        size_t o = 0;
        r->Buffer.resize(s * r->Channels);
        for (int i = 0; i < s; ++i)
        {
            r->Buffer[o++] = t->pcData[i].r;
            r->Buffer[o++] = t->pcData[i].g;
            r->Buffer[o++] = t->pcData[i].b;
            r->Buffer[o++] = 256;
        }

        return r;
    };

    for (int j = 0; j < scene->mNumTextures; ++j)
    {
        const aiTexture *t = scene->mTextures[j];
        loader.Textures.push_back(loadTexture(t));
    }
}

SharedReference<Material> LoadMaterial(const aiMaterial &material, const System::Path &path)
{
    auto result = CreateShared<PBRMaterial>();

    auto loadTexture = [&](aiTextureType type, Graphics::TextureSampler& sampler)
    {
        aiString p;
        material.GetTexture(type, 0, &p);
        auto texturePath = path.parent_path() / p.C_Str();
        if (!System::IsRegularFile(path))
        {
            fmt::print("Warning: Texture \"{}\" not found", texturePath.string());
            return;
        }

        sampler.Texture = Graphics::LoadTexture(texturePath);
    };

    if (material.GetTextureCount(aiTextureType_BASE_COLOR))
    {
        loadTexture(aiTextureType_BASE_COLOR, result->BaseColor);
    }
    else if (material.GetTextureCount(aiTextureType_DIFFUSE))
    {
        loadTexture(aiTextureType_DIFFUSE, result->BaseColor);
    }

    if (material.GetTextureCount(aiTextureType_AMBIENT_OCCLUSION))
    {
        loadTexture(aiTextureType_AMBIENT_OCCLUSION, result->AmbientOcclusion);
    }
    else if (material.GetTextureCount(aiTextureType_AMBIENT))
    {
        loadTexture(aiTextureType_AMBIENT, result->AmbientOcclusion);
    }

    if (material.GetTextureCount(aiTextureType_EMISSIVE))
    {
        loadTexture(aiTextureType_EMISSIVE, result->Emissive);
    }
    else if (material.GetTextureCount(aiTextureType_SHININESS))
    {
        loadTexture(aiTextureType_SHININESS, result->Emissive);
    }

    if (material.GetTextureCount(aiTextureType_DISPLACEMENT))
    {
        loadTexture(aiTextureType_DISPLACEMENT, result->Displacement);
    }
    else if (material.GetTextureCount(aiTextureType_HEIGHT))
    {
        loadTexture(aiTextureType_HEIGHT, result->Displacement);
    }

    if (material.GetTextureCount(aiTextureType_NORMALS))
    {
        loadTexture(aiTextureType_NORMALS, result->Normal);
    }

    if (material.GetTextureCount(aiTextureType_METALNESS))
    {
        loadTexture(aiTextureType_METALNESS, result->Metallic);
    }
    else if (material.GetTextureCount(aiTextureType_SHININESS))
    {
        loadTexture(aiTextureType_SHININESS, result->Metallic);
    }

    if (material.GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS))
    {
        loadTexture(aiTextureType_DIFFUSE_ROUGHNESS, result->Roughness);
    }
    return result;
}

void LoadMaterials(Graphics::AssetLoader &loader, const aiScene *scene, const System::Path &path)
{
    for (int j = 0; j < scene->mNumMaterials; ++j)
    {
        const aiMaterial &m = *scene->mMaterials[j];
        auto material = LoadMaterial(m, path);
        loader.Materials.push_back(material);
    }
}

SharedReference<Graphics::Mesh> LoadMesh(const aiMesh& mesh)
{
    auto result = CreateShared<Graphics::Mesh>();

    result->Vertices.resize(mesh.mNumVertices);
    for (size_t i = 0; i < mesh.mNumVertices; ++i)
    {
        aiVector3D p = mesh.mVertices[i];
        aiVector3D n = mesh.mNormals[i];
        result->Vertices[i].pos = { p.x, p.y, p.z, 0.0f };
        result->Vertices[i].normal = { n.x, n.y, n.z, 0.0f };
        if (mesh.mTextureCoords[0])
        {
            aiVector3D uv = mesh.mTextureCoords[0][i];
            result->Vertices[i].uv = { uv.x, 1.0f - uv.y, 0.0f, 0.0f };
        }

        if (mesh.mTangents)
        {
            aiVector3D t = mesh.mTangents[i];
            result->Vertices[i].data = { t.x, t.y, t.z, 0.0f };
        }
        /*if (mesh.mColors[0])
        {
            aiColor4D c = mesh.mColors[0][i];
            result->Vertices[i].data = { c.r, c.g, c.b, c.a };
        }*/
    }

    result->Faces.resize(mesh.mNumFaces);
    for (size_t i = 0; i < mesh.mNumFaces; ++i)
    {
        aiFace f = mesh.mFaces[i];
        result->Faces[i] = { f.mIndices[0], f.mIndices[1], f.mIndices[2] };
    }

    return result;
}

void LoadMeshes(Graphics::AssetLoader& loader, const aiScene* scene, size_t InitialMaterialIndex)
{
    for (int j = 0; j < scene->mNumMeshes; ++j)
    {
        auto& m = *scene->mMeshes[j];
        auto mesh = LoadMesh(m);
        loader.Meshes.push_back({ mesh, loader.Materials[InitialMaterialIndex + m.mMaterialIndex] });
    }
}

SharedReference<Graphics::Mesh> AssetLoader::LoadMesh(const System::Path& path, const String& name)
{
    SharedReference<Graphics::Mesh> result;
    LoadScene(path, [&](const aiScene& scene)
    {
        for (size_t i = 0; i < scene.mNumMeshes; ++i)
        {
            aiMesh* mesh = scene.mMeshes[i];
            if (name == mesh->mName.C_Str())
            {
                result = Graphics::LoadMesh(*mesh);
                break;
            }
        }
    });
    return result;
}

SharedReference<Graphics::Material> AssetLoader::LoadMaterial(const System::Path& path, const String& name)
{
    SharedReference<Graphics::Material> result;
    LoadScene(path, [&](const aiScene& scene)
    {
        for (size_t i = 0; i < scene.mNumMaterials; ++i)
        {
            aiMaterial* material = scene.mMaterials[i];
            if (name == material->GetName().C_Str())
            {
                result = Graphics::LoadMaterial(*material, path);
                break;
            }
        }
    });
    return result;
}

void AssetLoader::Load(Graphics::GraphicsContext &Context, Graphics::RenderBuffer &RenderBuffer, const System::Path &Path)
{
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(Path.string(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        return;
    }
    size_t InitialMaterialIndex = Materials.size();
    LoadTextures(*this, scene);
    LoadMaterials(*this, scene, Path);
    LoadMeshes(*this, scene, InitialMaterialIndex);

    for (auto &material : Materials)
    {
        material->RenderBuffer = RenderBuffer;
    }

    for (auto &mesh : Meshes)
    {
        Context.CreateMesh(*mesh.first);
    }
}

void AssetLoader::Clear()
{
    Textures.clear();
    Meshes.clear();
    Materials.clear();
}

}
