#pragma once

#include "Core/AWindow.h"

#include "Core/ASpace.h"
#include "Core/AEntity.h"

#include "Graphics/AForwardRenderer.h"
#include "Graphics/APerspectiveCamera.h"

template<typename ComponentType, typename CameraType = APerspectiveCamera, typename RendererType = Legacy::Graphics::AForwardRenderer>
class TemplateWindow : public AWindow
{
protected:
    CameraType rootCamera;
    RendererType rootRenderer;

    ::SharedReference<ASpace> rootSpace = CreateShared<ASpace>(rootRenderer, rootCamera);
    ::SharedReference<AEntity> rootEntity = CreateShared<AEntity>();
    ::SharedReference<ComponentType> rootComponent = CreateShared<ComponentType>(*rootEntity);
public:

    CameraType &getRootCamera() { return rootCamera; }
    const CameraType &getRootCamera() const { return rootCamera; }
    RendererType &getRootRenderer() { return rootRenderer; }
    const RendererType &getRootRenderer() const { return rootRenderer; }

    ::SharedReference<ASpace> getRootSpace() const { return rootSpace; }
    ::SharedReference<AEntity> getRootEntity() const { return rootEntity; }
    ::SharedReference<ComponentType> getRootComponent() const { return rootComponent; }

    TemplateWindow() :
        AWindow()
    {
        rootEntity->addComponent(rootComponent);
        rootSpace->addEntity(rootEntity);
        setSpaces({ rootSpace });
    }
};
