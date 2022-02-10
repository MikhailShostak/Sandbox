#include "../Views.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Tools
{

Graphics::AssetLoader g_ImportAssetLoder;

Assimp::Importer g_Importer;
const aiScene* g_Scene = nullptr;


void Draw()
{
    static String path = "C:/Assets/EditorContent.fbx";
    ImGui::InputText("Path", &path);
    if (ImGui::Button("Import"))
    {
        //g_ImportAssetLoder.Clear();
        //g_ImportAssetLoder.Load(*g_GraphicsContext, g_GraphicsContext->CurrentRenderBuffer, path);
        g_Scene = g_Importer.ReadFile(path, /*aiProcess_CalcTangentSpace |*/ aiProcess_Triangulate | aiProcess_JoinIdenticalVertices /*| aiProcess_SortByPType*/);

        if (!g_Scene)
        {
            return;
        }
    }

    if (!g_Scene)
    {
        return;
    }

    ImGui::Text(fmt::format("Name: {} {}", g_Scene->mName.C_Str(), g_Scene->GetShortFilename(path.data())).data());

    if (ImGui::CollapsingHeader(fmt::format("Animations ({})##ImportWindow.Header", g_Scene->mNumAnimations).data(), nullptr))
    {
        if (ImGui::BeginTable("Animations##ImportWindow.Table", 2, DefaultTableFlags))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            /*for (auto& [Name, Type] : g_ExtensionLibrary.Types)
            {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text(Name.data());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text(Type->m_Name);
            }*/
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader(fmt::format("Cameras ({})##ImportWindow.Header", g_Scene->mNumCameras).data(), nullptr))
    {
        if (ImGui::BeginTable("Cameras##ImportWindow.Table", 2, DefaultTableFlags))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader(fmt::format("Lights ({})##ImportWindow.Header", g_Scene->mNumLights).data(), nullptr))
    {
        if (ImGui::BeginTable("Lights##ImportWindow.Table", 2, DefaultTableFlags))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader(fmt::format("Materials ({})##ImportWindow.Header", g_Scene->mNumMaterials).data(), nullptr))
    {
        if (ImGui::BeginTable("Materials##ImportWindow.Table", 3, DefaultTableFlags))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Properties", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Textures", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableHeadersRow();
            for (size_t i = 0; i < g_Scene->mNumMaterials; ++i)
            {
                aiMaterial* material = g_Scene->mMaterials[i];
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text(material->GetName().C_Str());
                ImGui::TableSetColumnIndex(1);
                for (size_t j = 0; j < material->mNumProperties; ++j)
                {
                    aiMaterialProperty* materialProperty = material->mProperties[j];
                    ImGui::Text(fmt::format("{}:", materialProperty->mKey.C_Str()).data());
                    ImGui::SameLine();
                    if (materialProperty->mType == aiPTI_String)
                    {
                        aiString str;
                        material->Get(materialProperty->mKey.C_Str(), materialProperty->mType, materialProperty->mIndex, str);
                        ImGui::Text(fmt::format("{}", str.C_Str()).data());
                    }
                    else if (materialProperty->mType == aiPTI_Integer)
                    {
                        int32_t value = 0;
                        material->Get(materialProperty->mKey.C_Str(), materialProperty->mType, materialProperty->mIndex, value);
                        ImGui::Text(fmt::format("{}", value).data());
                    }
                    else if (materialProperty->mType == aiPTI_Float)
                    {
                        float value = 0;
                        material->Get(materialProperty->mKey.C_Str(), materialProperty->mType, materialProperty->mIndex, value);
                        ImGui::Text(fmt::format("{}", value).data());
                    }
                    else if ( materialProperty->mType == aiPTI_Double)
                    {
                        double value = 0;
                        material->Get(materialProperty->mKey.C_Str(), materialProperty->mType, materialProperty->mIndex, value);
                        ImGui::Text(fmt::format("{}", value).data());
                    }
                    else if (materialProperty->mType == aiPTI_Buffer)
                    {
                        ImGui::Text("[...]");
                    }
                }
                ImGui::TableSetColumnIndex(2);
                Array<String> TextureTypes = {
                     "aiTextureType_NONE",
                     "aiTextureType_DIFFUSE",
                     "aiTextureType_SPECULAR",
                     "aiTextureType_AMBIENT",
                     "aiTextureType_EMISSIVE",
                     "aiTextureType_HEIGHT",
                     "aiTextureType_NORMALS",
                     "aiTextureType_SHININESS",
                     "aiTextureType_OPACITY",
                     "aiTextureType_DISPLACEMENT",
                     "aiTextureType_LIGHTMAP",
                     "aiTextureType_REFLECTION",
                     "aiTextureType_BASE_COLOR",
                     "aiTextureType_NORMAL_CAMERA",
                     "aiTextureType_EMISSION_COLOR",
                     "aiTextureType_METALNESS",
                     "aiTextureType_DIFFUSE_ROUGHNESS",
                     "aiTextureType_AMBIENT_OCCLUSION",
                     "aiTextureType_UNKNOWN",
                     "aiTextureType_SHEEN",
                     "aiTextureType_CLEARCOAT",
                     "aiTextureType_TRANSMISSION",
                };
                for (size_t i = 1; i < 22; ++i)
                {
                    ImGui::Text(fmt::format("{}: {}\n", TextureTypes[i], material->GetTextureCount(aiTextureType(i))).data());
                }
            }
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader(fmt::format("Meshes ({})##ImportWindow.Header", g_Scene->mNumMeshes).data(), nullptr))
    {
        if (ImGui::BeginTable("Meshes##ImportWindow.Table", 9, DefaultTableFlags))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Anim Meshes", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Bones", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Faces", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Vertices", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("UV Components", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("UV Channels", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Color Channels", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Texture Coords Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableHeadersRow();
            for (size_t i = 0; i < g_Scene->mNumMeshes; ++i)
            {
                aiMesh* mesh = g_Scene->mMeshes[i];
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text(mesh->mName.C_Str());
                ImGui::TableSetColumnIndex(1);
                ImGui::Text(fmt::format("{}", mesh->mNumAnimMeshes).data());
                ImGui::TableSetColumnIndex(2);
                ImGui::Text(fmt::format("{}", mesh->mNumBones).data());
                ImGui::TableSetColumnIndex(3);
                ImGui::Text(fmt::format("{}", mesh->mNumFaces).data());
                ImGui::TableSetColumnIndex(4);
                ImGui::Text(fmt::format("{}", mesh->mNumVertices).data());
                ImGui::TableSetColumnIndex(5);
                ImGui::Text(fmt::format("{}", mesh->mNumUVComponents).data());
                ImGui::TableSetColumnIndex(6);
                ImGui::Text(fmt::format("{}", mesh->GetNumUVChannels()).data());
                ImGui::TableSetColumnIndex(7);
                ImGui::Text(fmt::format("{}", mesh->GetNumUVChannels()).data());
                ImGui::TableSetColumnIndex(8);
                if (mesh->GetTextureCoordsName(0))
                {
                    ImGui::Text(fmt::format("{}", mesh->GetTextureCoordsName(0)->C_Str()).data());
                }
            }
            ImGui::EndTable();
        }
    }

    if (ImGui::CollapsingHeader(fmt::format("Textures ({})##ImportWindow.Header", g_Scene->mNumTextures).data(), nullptr))
    {
        if (ImGui::BeginTable("Textures##ImportWindow.Table", 3, DefaultTableFlags))
        {
            ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Format", ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableHeadersRow();
            for (size_t i = 0; i < g_Scene->mNumTextures; ++i)
            {
                aiTexture *texture = g_Scene->mTextures[i];
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Text(texture->mFilename.C_Str());
                ImGui::TableSetColumnIndex(1);
                if (texture->mHeight > 0)
                {
                    ImGui::Text(fmt::format("{}x{}", texture->mWidth, texture->mHeight).data());
                }
                else
                {
                    ImGui::Text(fmt::format("{}", texture->mWidth).data());
                }
                ImGui::TableSetColumnIndex(2);
                ImGui::Text(fmt::format("{}", texture->achFormatHint).data());
            }
            ImGui::EndTable();
        }
    }    
}

void ShowImportWindow()
{
    if (!DisplayImportWindow)
    {
        return;
    }

    if (ImGui::Begin("Import"))
    {
        Draw();
    }
    ImGui::End();
}

}
