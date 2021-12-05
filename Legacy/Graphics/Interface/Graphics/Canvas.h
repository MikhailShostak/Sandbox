#pragma once

#include "HardwareHandle.h"
#include "Includes/Texture.gen.h"
#include "AMesh.h"
#include "GraphicsContext.h"
#include "AForwardRenderer.h"
#include "APerspectiveCamera.h"

namespace Legacy::Graphics
{

class CanvasCamera : public APerspectiveCamera
{
public:

    Math::Matrix inverseParentMatrix;

    Math::Matrix getViewMatrix() const override //TODO: should it be overridden?
    {
        return inverseParentMatrix * APerspectiveCamera::getViewMatrix();
    }

    Math::Matrix getProjectionMatrix() const override
    {
        Math::Matrix perspectiveMatrix = APerspectiveCamera::getProjectionMatrix();
        auto inverseHalfHeightResolution = 1 / resolution.getHalfY();
        auto aspectRatio = resolution.getXYAspectRatio();
        return Math::Matrix::getScale3({ inverseHalfHeightResolution, inverseHalfHeightResolution, inverseHalfHeightResolution }) * Math::Matrix::getTranslation({ -aspectRatio, -1.0f, -perspectiveMatrix[1][1] }) * perspectiveMatrix;
    }
};

class Canvas : public HardwareHandle<Canvas>, public GraphicsContext
{
    AColor backgroundColor = AColor::fromHex(0);
    AForwardRenderer forwardRenderer;
    ::SharedReference<ACamera> camera;
public:

    enum Attachment
    {
        ColorAttachment0,
        ColorAttachment1,
        ColorAttachment2,
        ColorAttachment3,
        ColorAttachment4,
        ColorAttachment5,
        ColorAttachment6,
        ColorAttachment7,
        ColorAttachment8,
        ColorAttachment9,
        ColorAttachment10,
        ColorAttachment11,
        ColorAttachment12,
        ColorAttachment13,
        ColorAttachment14,
        ColorAttachment15,
        DepthAttachment,
        StencilAttachment,
        CountAttachments,
    };

    Canvas()
    {
        CanvasCamera* camera = new CanvasCamera();
        camera->fieldOfView = 45.0f;
        camera->farClipping = 100;
        camera->nearClipping = 0.1;
        setCamera(::SharedReference<CanvasCamera>(camera));
    }

    Canvas(const ::SharedReference<ACamera> &camera)
    {
        setCamera(camera);
    }

    ::SharedReference<ACamera> getCamera() const { return camera; }
    void setCamera(const ::SharedReference<ACamera> &camera) { this->camera = camera; }

    const AColor getBackgroundColor() const { return backgroundColor; }
    void setBackgroundColor(const AColor &backgroundColor) { this->backgroundColor = backgroundColor; }

    Math::Matrix getMatrix() const { return camera->getMatrix(); }

    Math::IntegerVector getSize() const
    {
        return camera->resolution;
    }

    void setSize(const Math::IntegerVector &size)
    {
        camera->resolution = size;
    }

    Math::IntegerVector getViewport() const override
    {
        return getSize();
    }

    void onActive() override
    {
        ACamera::pushCamera(*camera);
        forwardRenderer.clear();
    }

    void draw(const ::SharedReference<Mesh> &mesh, const ::SharedReference<MaterialInterface> &material) override
    {
        forwardRenderer.addMesh(mesh, material);
    }

    void onDeactive() override
    {
        activate();
        Graphics::API::setBackgroundColor(backgroundColor);
        Graphics::API::clear();
        forwardRenderer.render();
        Graphics::API::flush();
        ACamera::popCamera();
        deactivate();
    }

    void onActivate() {}
    void onDeactivate() {}

    ::SharedReference<Texture> attachments[CountAttachments];
    bool useDepth = true;
};

}
