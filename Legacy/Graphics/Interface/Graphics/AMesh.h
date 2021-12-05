#pragma once

#include <Foundation>

#include "AFace.h"
#include "AVertex.h"
#include "BoundingVolume.h"
#include "HardwareHandle.h"

inline Math::BoundingVolume computeAABB(const Array<AVertex> &verticies);
inline Math::BoundingVolume computeAABB(const Legacy::Graphics::Mesh &mesh);

namespace Legacy::Graphics
{

class MaterialInterface;

class Mesh : public HardwareHandle<Mesh>
{
public:

    enum OtherDataType
    {
        Signle = 1,
        Vector2D = 2,
        Vector3D = 3,
        Vector4D = 4
    };

    Mesh() {}
    Mesh(const Array<AVertex> &vertices, const Array<AFace> &faces, bool otherData = false, OtherDataType otherDataType = Vector4D):
        vertices(vertices),
        faces(faces),
        otherData(otherData),
        otherDataType(otherDataType),
        boundingVolume(computeAABB(vertices))
    {}

    ~Mesh() {}

    void onActivate() {}
    void onDeactivate() {}

    const Array<AVertex> &getVertices() const { return vertices; }
    void setVertices(const Array<AVertex> &vertices) { this->vertices = vertices; boundingVolume = computeAABB(vertices); }
    void setVertices(Array<AVertex> &&vertices) { this->vertices = std::move(vertices); }
    Array<AVertex>::size_type countVertices() const { return vertices.size(); }

    const Array<AFace> &getFaces() const { return faces; }
    void setFaces(const Array<AFace> &faces) { this->faces = faces; }
    void setFaces(Array<AFace> &&faces) { this->faces = std::move(faces); }
    Array<AFace>::size_type countFaces() const { return faces.size(); }

    bool hasOtherData() const { return otherData; }

    const Math::BoundingVolume &getBoundingVolume() const
    {
        return boundingVolume;
    }

    void drawPoints(const Array<::SharedReference<MaterialInterface>> &materials) const
    {
        for (auto &material : materials)
        {
            hardwareObject.drawPoints(*this, *material);
        }
    }
    void drawLines(const Array<::SharedReference<MaterialInterface>> &materials) const
    {
        for (auto &material : materials)
        {
            hardwareObject.drawLines(*this, *material);
        }
    }
    void drawSurface(const Array<::SharedReference<MaterialInterface>> &materials) const
    {
        for (auto &material : materials)
        {
            hardwareObject.drawSurface(*this, *material);
        }
    }

private:
    Array<AVertex> vertices;
    Array<AFace> faces;
    bool otherData;
    OtherDataType otherDataType;
    Math::BoundingVolume boundingVolume;
};

}

inline Math::BoundingVolume computeAABB(const Array<AVertex> &verticies)
{
    Math::Vector min;
    Math::Vector max;
    for (const AVertex &vertex : verticies)
    {
        min = Math::getMin3(min, vertex.position);
        max = Math::getMax3(max, vertex.position);
    }
    const Math::Vector center = Math::getAverage<Math::Vector>(min, max);
    const Math::Vector halfExtent = (max - min) / 2.0f;
    return { center, halfExtent };
}

inline Math::BoundingVolume computeAABB(const Legacy::Graphics::Mesh &mesh)
{
    return computeAABB(mesh.getVertices());
}

inline std::ostream& operator<<(std::ostream& stream, const Legacy::Graphics::Mesh &mesh)
{
    return stream << "AMesh[" << &mesh << "](Verticies = " << mesh.countVertices() << ", Faces = " << mesh.countFaces() << ")";
}


