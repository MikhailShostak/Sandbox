#include "Raycast.h"

bool Raycast::worldCast(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<UI::View> &view)
{
    clear();
    castInternal(startWorldPoint, endWorldPoint, view);
    return !report.results.empty();
}

bool Raycast::screenCast(const ACamera &camera, const Math::IntegerVector &screenPoint, const SharedReference<UI::View> &view)
{
    const auto &&start = mapFromCameraProjectionToWorldSpace(camera, screenPoint, 1.0f);
    const auto &&end = mapFromCameraProjectionToWorldSpace(camera, screenPoint, -1.0f);
    return worldCast(start, end, view);
}

void Raycast::castInternal(const Math::Vector &startWorldPoint, const Math::Vector &endWorldPoint, const SharedReference<UI::View> &view)
{
    if (!view->isVisible() || !view->isEnabled() || !view->isExpanded())
    {
        return;
    }

    for (auto it = view->getViews().rbegin(); it != view->getViews().rend(); ++it)
    {
        castInternal(startWorldPoint, endWorldPoint, *it);
    }

    const Math::Vector planePosition = Math::Vector{ 0, 0, 0 };
    const Math::Vector planeNormal = Math::Vector{ 0, 0, -1 };

    Math::Vector contactPoint;
    bool isInside = false;
    if (Math::intersectRayWithPlane(mapFromWorldSpaceToLocalSpace(*view, startWorldPoint), mapFromWorldSpaceToLocalSpace(*view, endWorldPoint), planePosition, planeNormal, contactPoint))
    {
        //TODO: const Math::BoundingVolume &spriteBV = getSprite().getBoundingVolume();
        if (0.0f <= contactPoint.x && contactPoint.x <= 1.0f && 0.0f <= contactPoint.y && contactPoint.y <= 1.0f)
        {
            isInside = true;
        }
    }

    report.results.push_back(CollisionInfo{ isInside, Collision{ view, Math::IntegerVector{
        static_cast<int32_t>(view->getSize().x * contactPoint.x),
        static_cast<int32_t>(view->getSize().y * contactPoint.y)
    } } });
}

