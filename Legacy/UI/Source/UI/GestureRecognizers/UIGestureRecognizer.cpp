#include "UIGestureRecognizer.h"
#include "UIMath.h"

#include <Graphics>

#include "Includes/View.gen.h"

namespace UI
{
    AWindow &GestureRecognizer::getWindow() const
    {
        AAssert(view && view->getOwner() && view->getOwner()->getWindow(), "Invalid window");
        return *view->getOwner()->getWindow();
    }

    void GestureRecognizer::load(View &view)
    {
        this->view = &view;
    }

    void GestureRecognizer::unload()
    {
        view = nullptr;
    }

    void GestureRecognizer::sendEventToView(AEvent &event)
    {
        getView().sendEvent(event);
        getView().eventChannel.sendEvent(event);
    }

    bool GestureRecognizer::sendAcceptableEventToView(AAcceptableEvent &event)
    {
        getView().sendEvent(event);
        if (!event.isAccepted())
        {
            getView().eventChannel.sendAcceptableEvent(event);
        }

        return event.isAccepted();
    }

    bool GestureRecognizer::raycastToView(const Math::IntegerVector &screenPosition, const UI::View &view)
    {
        Math::Vector startLocalPoint = mapFromScreenSpaceToLocalSpace(view, screenPosition, 1.0f);
        Math::Vector endLocalPoint = mapFromScreenSpaceToLocalSpace(view, screenPosition, -1.0f);

        Math::Vector planePosition = Math::Vector{ 0, 0, 0 };
        Math::Vector planeNormal = Math::Vector{ 0, 0, -1 };

        Math::Vector contactPoint;
        if (Math::intersectRayWithPlane(startLocalPoint, endLocalPoint, planePosition, planeNormal, contactPoint))
        {
            point = Math::IntegerVector{ 
                static_cast<int32_t>(view.getSize().x * contactPoint.x),
                static_cast<int32_t>(view.getSize().y * contactPoint.y)
            };
            if (0.0f <= contactPoint.x && contactPoint.x <= 1.0f && 0.0f <= contactPoint.y && contactPoint.y <= 1.0f)
            {
                return true;
            }
        }
        return false;
    }

    bool GestureRecognizer::raycastToView(const Math::IntegerVector &screenPosition)
    {
        return raycastToView(screenPosition, getView());
    }
}
