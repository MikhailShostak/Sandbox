#pragma once

#include "Core/AVisualComponent.h"
#include "Graphics/AMesh.h"
#include "Materials/PBRMaterial.g.h"

class AStaticMeshComponent : public AVisualComponent
{
public:
    ::SharedReference<Legacy::Graphics::Mesh> mesh;
    using AVisualComponent::AVisualComponent;

    ::SharedReference<Legacy::Graphics::PBRMaterial> material = std::make_shared<Legacy::Graphics::PBRMaterial>();
protected:
    void onLoad(ALoadEvent &event) override;
    void onUnload(AUnloadEvent &event) override;
    void onDraw(AUpdateEvent &event) override;
};
