#pragma once

#include <Foundation>

#include "Graphics/Graphics.h"
#include "Graphics/MeshGenerator.h"
#include "Materials/UIImageMaterial.g.h"

struct Shape
{
public:

};

struct BoxShape : public Shape
{
public:
    Math::Vector halfExtents;
};

struct SphereShape : public Shape
{
public:
    float radius = 0;
};

struct CapsuleShape : public Shape
{
public:
    float radius = 0;
    float height = 0;
};

class DebugRenderer
{
public:

    struct Element
    {
        ::SharedReference<Legacy::Graphics::Mesh> mesh;
        ATimePoint<ASteadyClock> endTime;
        AColor color;
        Math::Matrix transform;
        bool wireframe = false;
    };

private:
    ::SharedReference<UI::ImageMaterial> material = std::make_shared<UI::ImageMaterial>();
    Array<Element> elements;
public:

    DebugRenderer()
    {
        elements.reserve(1024);
    }

    Element &drawLine(const Math::Vector &start, const Math::Vector &end, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawGrid(const Math::Vector &origin, const Math::Vector &cellSize, const AColor &color, AMilliseconds duration = AMilliseconds::zero());

    Element &drawCapsuleSurface(const Math::Matrix &transform, float height, float radius, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawCapsuleSurface(const Math::Vector &start, const Math::Vector &end, float radius, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawCapsuleWireframe(const Math::Matrix &transform, float height, float radius, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawCapsuleWireframe(const Math::Vector &start, const Math::Vector &end, float radius, const AColor &color, AMilliseconds duration = AMilliseconds::zero());

    Element &drawBoxSurface(const Math::Vector &position, const Math::Vector halfExtents, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawBoxWireframe(const Math::Vector &position, const Math::Vector halfExtents, const AColor &color, AMilliseconds duration = AMilliseconds::zero());

    Element &drawSphereSurface(const Math::Vector &position, float radius, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawSphereWireframe(const Math::Vector &position, float radius, const AColor &color, AMilliseconds duration = AMilliseconds::zero());

    Element &drawShapeSurface(const Math::Matrix &transform, ::SharedReference<Shape> shape, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawShapeWireframe(const Math::Matrix &transform, ::SharedReference<Shape> shape, const AColor &color, AMilliseconds duration = AMilliseconds::zero());

    Element &drawMeshSurface(const Math::Matrix &transform, const ::SharedReference<Legacy::Graphics::Mesh> &mesh, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    Element &drawMeshWireframe(const Math::Matrix &transform, const ::SharedReference<Legacy::Graphics::Mesh> &mesh, const AColor &color, AMilliseconds duration = AMilliseconds::zero());
    
    void render()
    {
        if (elements.empty())
        {
            return;
        }

        if (!material->isLoaded())
        {
            APixmap whitePixmap;
            whitePixmap.setBuffer(Array<uint8_t>{ 255, 255, 255, 255, }, Math::IntegerVector{ 1, 1 }, APixmapDataFormat::RGBA);
            material->Image = std::make_shared<Legacy::Graphics::Texture>(whitePixmap);
            material->ImageScale = Math::Vector{ 1.0, 1.0 };
            material->ClippingTopLeft = Math::Vector{ 0.0f, 0.0f };
            material->ClippingBottomRight = Math::Vector{ 1.0f, 1.0f };
            material->Image->load();
            material->load();
        }
        Math::Matrix viewProjectionMatrix = ACamera::getCurrentCamera()->getMatrix();

        Legacy::Graphics::API::setBlending(true);
        Legacy::Graphics::API::setDepthFunction(Legacy::Graphics::API::DepthFunction::Always);
        Legacy::Graphics::API::setWritingDepth(false);
        for(auto it = elements.begin(); it != elements.end(); ++it)
        {
            const Element &element = *it;
            if (!element.mesh->isLoaded())
            {
                element.mesh->load();
            }
            material->ModelViewProjectionMatrix = element.transform * viewProjectionMatrix;
            material->Color = element.color;
            if (element.wireframe)
            {
                element.mesh->drawLines({ material });
            }
            else
            {
                element.mesh->drawSurface({ material });
            }

            if (ASteadyClock::now() > element.endTime)
            {
                it = elements.erase(it);
                --it;
            }
        }
    }

private:

    Element &createElement(const Math::Matrix &transform, const ::SharedReference<Legacy::Graphics::Mesh> &mesh, const AColor &color, AMilliseconds duration)
    {
        elements.push_back(Element());
        Element &element = elements.back();
        element.transform = transform;
        element.mesh = mesh;
        element.color = color;
        element.endTime = ASteadyClock::now() + duration;
        return element;
    }
};

inline DebugRenderer::Element &DebugRenderer::drawLine(const Math::Vector &start, const Math::Vector &end, const AColor &color, AMilliseconds duration)
{
    Math::Matrix transform;
    return createElement(transform, Legacy::Graphics::generateCapsule(), color, duration);
}

inline DebugRenderer::Element &DebugRenderer::drawGrid(const Math::Vector &origin, const Math::Vector &cellSize, const AColor &color, AMilliseconds duration)
{
    Math::Matrix transform;
    return createElement(transform, Legacy::Graphics::generateCapsule(), color, duration);
}

inline ::SharedReference<Legacy::Graphics::Mesh> generateCapsuleMesh(float height, float radius)
{
   /* Array<AVertex> vertices;
    Array<AFace> faces;
    const uint8_t segments = 16;
    const float halfHeight = height / 2;
    for (int i = 0; i < segments; ++i)
    {
        float xRatio = i / segments;
        for (int j = 0; j < segments; ++j)
        {
            float zRatio = j / segments;

            for (int k = 0; k < segments; ++k)
            {
                float yRatio = k / segments;
                float x = cos(AMathConstans::Pi * xRatio);
                float y = sin(AMathConstans::Pi * yRatio);
                float z = sin(AMathConstans::Pi * zRatio);
                vertices.append(AVertex(x * radius, halfHeight + y * radius, z * radius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
                vertices.append(AVertex(-x * radius, -halfHeight + -y * radius, -z * radius, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f));
            }
        }        
    }
    mesh = new Legacy::Graphics::Mesh();
    mesh->setVertices();
    mesh->setFaces();*/
    return nullptr;
}

inline DebugRenderer::Element &DebugRenderer::drawCapsuleSurface(const Math::Matrix &transform, float height, float radius, const AColor &color, AMilliseconds duration)
{
    return createElement(transform, Legacy::Graphics::generateCapsule(), color, duration);
}

inline DebugRenderer::Element &DebugRenderer::drawCapsuleSurface(const Math::Vector &start, const Math::Vector &end, float radius, const AColor &color, AMilliseconds duration)
{
    Math::Matrix transform;
    return createElement(transform, Legacy::Graphics::generateCapsule(), color, duration);
    /*Math::Vector d = end - start;
    Math::Matrix t;
    t.position = start + d / 2.0f;
    //t.rotation;
    drawCapsuleSurface(t, std::sqrt(std::pow(d.x, 2) + std::pow(d.y, 2) + std::pow(d.z, 2)), radius, color, duration);*/
}

inline DebugRenderer::Element &DebugRenderer::drawCapsuleWireframe(const Math::Matrix &transform, float height, float radius, const AColor &color, AMilliseconds duration)
{
    Element &element = drawCapsuleSurface(transform, height, radius, color, duration);
    element.wireframe = true;
    return element;
}

inline DebugRenderer::Element &DebugRenderer::drawCapsuleWireframe(const Math::Vector &start, const Math::Vector &end, float radius, const AColor &color, AMilliseconds duration)
{
    Element &element = drawCapsuleSurface(start, end, radius, color, duration);
    element.wireframe = true;
    return element;
}

inline DebugRenderer::Element &DebugRenderer::drawBoxSurface(const Math::Vector &position, const Math::Vector halfExtents, const AColor &color, AMilliseconds duration)
{
    Math::Matrix transform;
    return createElement(transform, Legacy::Graphics::generateBox(), color, duration);
}

inline DebugRenderer::Element &DebugRenderer::drawBoxWireframe(const Math::Vector &position, const Math::Vector halfExtents, const AColor &color, AMilliseconds duration)
{
    Element &element = drawBoxSurface(position, halfExtents, color, duration);
    element.wireframe = true;
    return element;
}

inline DebugRenderer::Element &DebugRenderer::drawSphereSurface(const Math::Vector &position, float radius, const AColor &color, AMilliseconds duration)
{
    static Math::Vector p = Math::Vector{ 0.0f, 0.0f, 0.0f };
    Math::Matrix transform;
    transform = Math::Matrix::getTranslation({100, 100, 0});
    return createElement(transform, Legacy::Graphics::generateSphere(), color, duration);
}

inline DebugRenderer::Element &DebugRenderer::drawSphereWireframe(const Math::Vector &position, float radius, const AColor &color, AMilliseconds duration)
{
    Element &element = drawSphereSurface(position, radius, color, duration);
    element.wireframe = true;
    return element;
}

inline DebugRenderer::Element &DebugRenderer::drawShapeSurface(const Math::Matrix &transform, ::SharedReference<Shape> shape, const AColor &color, AMilliseconds duration)
{
    Element &element = createElement(transform, nullptr, color, duration);
    return element;
}

inline DebugRenderer::Element &DebugRenderer::drawShapeWireframe(const Math::Matrix &transform, ::SharedReference<Shape> shape, const AColor &color, AMilliseconds duration)
{
    Element &element = drawShapeSurface(transform, nullptr, color, duration);
    element.wireframe = true;
    return element;
}

inline DebugRenderer::Element &DebugRenderer::drawMeshSurface(const Math::Matrix &transform, const ::SharedReference<Legacy::Graphics::Mesh> &mesh, const AColor &color, AMilliseconds duration)
{
    return createElement(transform, mesh, color, duration);
}

inline DebugRenderer::Element &DebugRenderer::drawMeshWireframe(const Math::Matrix &transform, const ::SharedReference<Legacy::Graphics::Mesh> &mesh, const AColor &color, AMilliseconds duration)
{
    Element &element = drawMeshSurface(transform, mesh, color, duration);
    element.wireframe = true;
    return element;
}

class DebugRendererContainer : public ASingleton<DebugRendererContainer>
{
    Map<const char *, DebugRenderer> renderers;
public:
    DebugRenderer & operator[](const char *name)
    {
        return renderers[name];
    }
};

inline DebugRenderer &VisualDebug(const char *name)
{
    return DebugRendererContainer::getInstance()[name];
}

inline DebugRenderer &WorldVisualDebug()
{
    return VisualDebug("World");
}

inline DebugRenderer &FirstPersonVisualDebug()
{
    return VisualDebug("FirstPerson");
}

inline DebugRenderer &UIVisualDebug()
{
    return VisualDebug("UI");
}
