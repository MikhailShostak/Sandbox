#pragma once

#include <Foundation>
#include <ImageFormats.pch.hpp>

#include "Graphics/AMesh.h"
#include "Materials/PBRMaterial.g.h"

inline Map<String, ::SharedReference<Legacy::Graphics::PBRMaterial>> loadWafefrontOBJMaterials(const APath &textureDirectory, const Array<uint8_t> &buffer)
{
    Map<String, ::SharedReference<Legacy::Graphics::PBRMaterial>> materials;

    ::SharedReference<Legacy::Graphics::PBRMaterial> material;

    Array<String> lines;
    boost::split(lines, buffer, boost::is_any_of("\n"));
    for (auto line : lines)
    {
        String::size_type index = line.find_first_of(' ');
        String key = line.substr(0, index);
        if (key == "#" || key.empty())
            continue;

        String command = line.substr(index + 1);

        if (key == "newmtl")
        {
            material = std::make_shared<Legacy::Graphics::PBRMaterial>();
            materials.insert({command, material});
            continue;
        }
        if (key == "\tmap_Kd")
        {
            if (textureDirectory.size() == 1 && textureDirectory.source()[0] == "assets")
            {
                material->ColorMap = std::make_shared<Legacy::Graphics::Texture>(APixmapLoader::getInstance().decompress(getAsset(APath(command).baseName())));
            }
            else
            {
                material->ColorMap = std::make_shared<Legacy::Graphics::Texture>(APixmapLoader::getInstance().load(textureDirectory + command));
            }
            continue;
        }

        if (key == "\tmap_bump")
        {
            if (textureDirectory.size() == 1 && textureDirectory.source()[0] == "assets")
            {
                material->NormalMap = std::make_shared<Legacy::Graphics::Texture>(APixmapLoader::getInstance().decompress(getAsset(APath(command).baseName())));
            }
            else
            {
                material->NormalMap = std::make_shared<Legacy::Graphics::Texture>(APixmapLoader::getInstance().load(textureDirectory + command));
            }
            continue;
        }
    }
    return materials;
}

inline Map<String, APair<::SharedReference<Legacy::Graphics::Mesh>, ::SharedReference<Legacy::Graphics::PBRMaterial>>> loadWafefrontOBJ(const Map<String, ::SharedReference<Legacy::Graphics::PBRMaterial>> &materials, const Array<uint8_t> &buffer)
{
    Map<String, APair<::SharedReference<Legacy::Graphics::Mesh>, ::SharedReference<Legacy::Graphics::PBRMaterial>>> meshes;
    ::SharedReference<Legacy::Graphics::Mesh> mesh = nullptr;

    Array<Math::Vector> points;
    Array<Math::Vector> normals;
    Array<Math::Vector> textureCoords;
    Array<AVertex> &&vertices = Array<AVertex>();
    Array<AFace> &&faces = Array<AFace>();
    String group = "";
    String object = "";
    String material = "";

    Array<String> lines;
    boost::split(lines, buffer, boost::is_any_of("\n"));
    for(auto line : lines)
    {
        String::size_type index = line.find_first_of(' ');
        String key = line.substr(0, index);
        if(key == "#" || key.empty())
            continue;
        String command = line.substr(index + 1, (line.back() == '\r' ? line.size() - 1 : line.size()) - (index + 1));
        if(key == "usemtl")
        {
            material = command;
            if (mesh)
            {
                mesh->setVertices(vertices);
                vertices.clear();
                mesh->setFaces(faces);
                faces.clear();
            }
            mesh = std::make_shared<Legacy::Graphics::Mesh>();
            auto it = materials.find(material);
            meshes.insert({ group + object + material + ".obj", { mesh, it != materials.end() ? it->second : ::SharedReference<Legacy::Graphics::PBRMaterial>() } });
            continue;
        }
        if (key == "g")
        {
            group = command + "_";
            continue;
        }
        if (key == "o")
        {
            object = command + "_";
            continue;
        }
        if(key == "v")
        {
            Array<String> raw;
            boost::split(raw, command, boost::is_any_of(" "));
            if(raw.size() == 3)
            {
                
                points.push_back(Math::Vector{
                    Str::To<float>(raw.at(0)),
                    Str::To<float>(raw.at(1)),
                    Str::To<float>(raw.at(2))
                } * 0.01f);
            }
            continue;
        }
        if(key == "vt")
        {
            Array<String> raw;
            boost::split(raw, command, boost::is_any_of(" "));
            if(raw.size() == 2)
            {
                textureCoords.push_back(Math::Vector{ Str::To<float>(raw.at(0)), -Str::To<float>(raw.at(1)) });
            }
            else if(raw.size() == 3)
            {
                textureCoords.push_back(Math::Vector{ Str::To<float>(raw.at(0)), -Str::To<float>(raw.at(1)), Str::To<float>(raw.at(2)) });
            }
            continue;
        }
        if(key == "vn")
        {
            Array<String> raw;
            boost::split(raw, command, boost::is_any_of(" "));
            if(raw.size() == 3)
            {
                normals.push_back(Math::Vector{
                    Str::To<float>(raw.at(0)),
                    Str::To<float>(raw.at(1)),
                    Str::To<float>(raw.at(2))
                });
            }
            continue;
        }
        if(key == "f")
        {
            auto parseVertexProperties = [&points, &normals, &textureCoords, &vertices](const String &propertiesData) {
                enum class IndexType {
                    Position = 0,
                    Texture = 1,
                    Normal = 2,
                };

                Array<String> vertexPropertyIndicies;
                boost::split(vertexPropertyIndicies, propertiesData, boost::is_any_of("/"));
                auto getIndex = [&vertexPropertyIndicies](IndexType indexType) -> size_t
                {
                    if (vertexPropertyIndicies[size_t(indexType)].size() > 0)
                    {
                        return std::stoi(vertexPropertyIndicies[size_t(indexType)]) - 1;
                    }
                    return -1;
                };

                AVertex vertex;
                size_t i = 0;
                if ((i = getIndex(IndexType::Position)) != size_t(-1))
                {
                    vertex.setPosition(points[i].x, points[i].y, points[i].z);
                }
                if ((i = getIndex(IndexType::Normal)) != size_t(-1))
                {
                    vertex.setNormal(normals[i].x, normals[i].y, normals[i].z);
                }
                if ((i = getIndex(IndexType::Texture)) != size_t(-1))
                {
                    vertex.setTexture(textureCoords[i].x, textureCoords[i].y);
                }
                vertices.push_back(std::move(vertex));
            };

            Array<String> face;
            boost::split(face, command, boost::is_any_of(" "));
            if(face.size() == 3)
            {
                faces.push_back(AFace(vertices.size(), vertices.size() + 1, vertices.size() + 2));
                for (int i = 0; i < 3; ++i)
                {
                    parseVertexProperties(face[i]);
                }
            }
            else if(face.size() == 4)
            {
                faces.push_back(AFace(vertices.size(), vertices.size() + 1, vertices.size() + 2));
                parseVertexProperties(face[0]);
                parseVertexProperties(face[1]);
                parseVertexProperties(face[2]);

                faces.push_back(AFace(vertices.size(), vertices.size() + 1, vertices.size() + 2));
                parseVertexProperties(face[2]);
                parseVertexProperties(face[3]);
                parseVertexProperties(face[0]);
            }
            else
            {
                AAssert(false, "Invalid face");
            }
            continue;
        }
    }

    if(mesh)
    {
            mesh->setVertices(vertices);
            mesh->setFaces(faces);
    }

    return meshes;
}

inline Map<String, APair<::SharedReference<Legacy::Graphics::Mesh>, ::SharedReference<Legacy::Graphics::PBRMaterial>>> loadWafefrontOBJFromAssets(const String &asset)
{
    return loadWafefrontOBJ(loadWafefrontOBJMaterials("assets", getAsset(asset + "-mtl")), getAsset(asset + "-obj"));
}

inline Map<String, APair<::SharedReference<Legacy::Graphics::Mesh>, ::SharedReference<Legacy::Graphics::PBRMaterial>>> loadWafefrontOBJFromFiles(const APath &filename)
{
    AFile mtl;
    mtl.open(filename.resolveWithExtension("mtl"), AFileOpenMode::Read);

    AFile file;
    file.open(filename, AFileOpenMode::Read);

    return loadWafefrontOBJ(loadWafefrontOBJMaterials(filename.directory(), mtl.readAll()), file.readAll());
}
