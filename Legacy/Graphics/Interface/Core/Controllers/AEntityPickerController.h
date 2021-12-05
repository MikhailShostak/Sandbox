#pragma once

#include <Foundation>
#include "Core/AInputController.h"
#include "Core/Components/AStaticMeshComponent.h"
#include "GraphicsMath.h"


class AEntityPickerController : public AInputController
{
    ASpace &space;
    WeakReference<AEntity> selectedEntity;
    WeakReference<AStaticMeshComponent> selectedMeshComponent;
public:
    AEntityPickerController(AWindow &window, ASpace &space):
        AInputController(window),
        space(space)
    {

    }

protected:

    void onTouchDown(AWindowTouchDownEvent &event) override
    {
        if (!event.isPressed(ATouchID::LeftMouseButton))
        {
            return;
        }

        Math::Vector startWorldPoint = mapFromScreenSpaceToWorldSpace(space, event.getPosition(), 1.0f);
        Math::Vector endWorldPoint = mapFromScreenSpaceToWorldSpace(space, event.getPosition(), -1.0f);

        auto &entities = space.getEntities();
        for (const ::SharedReference<AEntity> &entity : entities)
        {
            for (auto &component : entity->getComponents())
            {
                Math::Matrix m = entity->getMatrix().getInversed();
                Math::Vector start = startWorldPoint * m;
                Math::Vector end = endWorldPoint * m;
                ::SharedReference<AStaticMeshComponent> meshComponent = DynamicCast<AStaticMeshComponent>(component);
                if (meshComponent)
                {
                    const Math::BoundingVolume &bv = meshComponent->mesh->getBoundingVolume();
                    Math::Vector plane1 = bv.getRight();
                    Math::Vector plane2 = bv.getTop();
                    Math::Vector plane3 = bv.getBack();
                    Math::Vector plane4 = bv.getLeft();
                    Math::Vector plane5 = bv.getBottom();
                    Math::Vector plane6 = bv.getFront();
                    Math::Vector contactPoint;
                    if (Math::intersectRayWithPlane(start, end, plane1, Math::Vector{ 1, 0, 0 }, contactPoint))
                    {
                        if (-bv.halfExtent.y < contactPoint.y && contactPoint.y < bv.halfExtent.y && -bv.halfExtent.z < contactPoint.z && contactPoint.z < bv.halfExtent.z)
                        {
                            if (auto c = selectedMeshComponent.lock())
                            {
                                c->material->BaseColor = AColor::WhiteColor();
                            }
                            selectedMeshComponent = meshComponent;
                            selectedEntity = entity;
                            return;
                        }
                    }
                    if (Math::intersectRayWithPlane(start, end, plane2, Math::Vector{ 0, 1, 0 }, contactPoint))
                    {
                        if (-bv.halfExtent.x < contactPoint.x && contactPoint.x < bv.halfExtent.x && -bv.halfExtent.z < contactPoint.z && contactPoint.z < bv.halfExtent.z)
                        {
                            if (auto c = selectedMeshComponent.lock())
                            {
                                c->material->BaseColor = AColor::WhiteColor();
                            }
                            meshComponent->material->BaseColor = AColor(0.0, 0.3, 0.7);
                            selectedMeshComponent = meshComponent;
                            selectedEntity = entity;
                            return;
                        }
                    }
                    if (Math::intersectRayWithPlane(start, end, plane3, Math::Vector{ 0, 0, 1 }, contactPoint))
                    {
                        if (-bv.halfExtent.x < contactPoint.x && contactPoint.x < bv.halfExtent.x && -bv.halfExtent.y < contactPoint.y && contactPoint.y < bv.halfExtent.y)
                        {
                            if (auto c = selectedMeshComponent.lock())
                            {
                                c->material->BaseColor = AColor::WhiteColor();
                            }
                            meshComponent->material->BaseColor = AColor(0.0, 0.3, 0.7);
                            selectedMeshComponent = meshComponent;
                            selectedEntity = entity;
                            return;
                        }
                    }
                    if (Math::intersectRayWithPlane(start, end, plane4, Math::Vector{ -1, 0, 0 }, contactPoint))
                    {
                        if (-bv.halfExtent.y < contactPoint.y && contactPoint.y < bv.halfExtent.y && -bv.halfExtent.z < contactPoint.z && contactPoint.z < bv.halfExtent.z)
                        {
                            if (auto c = selectedMeshComponent.lock())
                            {
                                c->material->BaseColor = AColor::WhiteColor();
                            }
                            meshComponent->material->BaseColor = AColor(0.0, 0.3, 0.7);
                            selectedMeshComponent = meshComponent;
                            selectedEntity = entity;
                            return;
                        }
                    }
                    if (Math::intersectRayWithPlane(start, end, plane5, Math::Vector{ 0, -1, 0 }, contactPoint))
                    {
                        if (-bv.halfExtent.x < contactPoint.x && contactPoint.x < bv.halfExtent.x && -bv.halfExtent.z < contactPoint.z && contactPoint.z < bv.halfExtent.z)
                        {
                            if (auto c = selectedMeshComponent.lock())
                            {
                                c->material->BaseColor = AColor::WhiteColor();
                            }
                            meshComponent->material->BaseColor = AColor(0.0, 0.3, 0.7);
                            selectedMeshComponent = meshComponent;
                            selectedEntity = entity;
                            return;
                        }
                    }
                    if (Math::intersectRayWithPlane(start, end, plane6, Math::Vector{ 0, 0, -1 }, contactPoint))
                    {
                        if (-bv.halfExtent.x < contactPoint.x && contactPoint.x < bv.halfExtent.x && -bv.halfExtent.y < contactPoint.y && contactPoint.y < bv.halfExtent.y)
                        {
                            if (auto c = selectedMeshComponent.lock())
                            {
                                c->material->BaseColor = AColor::WhiteColor();
                            }
                            meshComponent->material->BaseColor = AColor(0.0, 0.3, 0.7);
                            selectedMeshComponent = meshComponent;
                            selectedEntity = entity;
                            return;
                        }
                    }
                }
            }
        }
        if (auto c = selectedMeshComponent.lock())
        {
            c->material->BaseColor = AColor::WhiteColor();
            selectedMeshComponent.reset();
        }
        selectedEntity.reset();
    }
};
