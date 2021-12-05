#include "UILinkingGestureRecognizer.h"
#include "Includes/View.gen.h"

#include "UIMath.h"

namespace UI
{

void LinkingGestureRecognizer::onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
    source = dynamic_cast<LinkingSourceGestureAdapter*>(&getView());
    if (!source || !source->canBeLinkedAsSouce())
    {
        return;
    }

    data = source->getLinkingSourceData();

    if (raycastToView(event.getPosition()))
    {
        event.accept();
        viewTouched = true;
        startPosition = getView().getPosition() - event.getPosition().getReflectedY<Math::Vector>();

        UI::View &root = *getView().getOwner()->getView();
        Math::Vector startLocalPoint = mapFromScreenSpaceToLocalSpace(root, event.getPosition(), 1.0f);
        Math::Vector endLocalPoint = mapFromScreenSpaceToLocalSpace(root, event.getPosition(), -1.0f);

        Math::Vector planePosition = Math::Vector{ 0, 0, 0 };
        Math::Vector planeNormal = Math::Vector{ 0, 0, -1 };

        Math::Vector contactPoint;
        /*bool intersected = */Math::intersectRayWithPlane(startLocalPoint, endLocalPoint, planePosition, planeNormal, contactPoint);

        line->sourceAnchor.offset = Math::Vector{ contactPoint.x * root.getSize().x, contactPoint.y * root.getSize().y, contactPoint.z };
        line->destinationAnchor.offset = Math::Vector{ 0.0f, 0.0f, 0.0f};
        root.addView(line);
    }
}

void LinkingGestureRecognizer::onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
    if (viewTouched)
    {
        event.accept();
        raycastToView(event.getPosition());
        UI::View &root = *getView().getOwner()->getView();
        Math::Vector startLocalPoint = mapFromScreenSpaceToLocalSpace(root, event.getPosition(), 1.0f);
        Math::Vector endLocalPoint = mapFromScreenSpaceToLocalSpace(root, event.getPosition(), -1.0f);

        Math::Vector planePosition = Math::Vector{ 0, 0, 0 };
        Math::Vector planeNormal = Math::Vector{ 0, 0, -1 };

        Math::Vector contactPoint;
        /*bool intersected = */Math::intersectRayWithPlane(startLocalPoint, endLocalPoint, planePosition, planeNormal, contactPoint);
        line->destinationAnchor.offset = Math::Vector{ contactPoint.x * root.getSize().x - line->getPosition().x, contactPoint.y * root.getSize().y - line->getPosition().y, 0.0f };

        LinkingTargetGestureAdapter *newTarget = nullptr;
        for (const APair<SharedReference<View>, Math::IntegerVector> &pair : views)
        {
            newTarget = dynamic_cast<LinkingTargetGestureAdapter*>(pair.first.get());
            if (newTarget)
            {
                if (!newTarget->canBeLinkedAsTarget(getView(), data))
                {
                    newTarget = nullptr;
                }
                break;
            }
        }

        if (target != newTarget)
        {
            if (target)
            {
                target->onLinkingUnhighlight();
            }
            target = newTarget;
            if (target)
            {
                target->onLinkingHighlight();
            }
        }
    }
}

void LinkingGestureRecognizer::onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
    if (viewTouched)
    {
        event.accept();
        viewTouched = false;

        if (target)
        {
            source->onSourceLink(*dynamic_cast<UI::View *>(target), getPoint(), data);
            target->onTargetLink(getView(), getPoint(), data);
            target->onLinkingUnhighlight();
        }

        source = nullptr;
        target = nullptr;

        UI::View &root = *line->getParent();
        root.removeView(line);
    }
}
}
