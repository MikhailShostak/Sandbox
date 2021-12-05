#pragma once

#include <Experimental>

namespace UI
{

class RotationRecognizer : public GestureRecognizer
{
    bool active = false;
    Math::IntegerVector startPoint;
    Math::Quaternion startRotation;
    Math::Quaternion rotation;
public:

    ADelegate<void(const Math::Quaternion &rotation)> rotationUpdated;

    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (isInside)
        {
            active = true;
            startRotation = rotation;
            startPoint = point;
        }
    }

    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        if (active)
        {
            Math::IntegerVector d = point - startPoint;
            rotation = Math::Quaternion::getXRotation(d.Y) * Math::Quaternion::getYRotation(d.X) * startRotation;
            rotation.normalize();
            rotationUpdated(rotation);
        }
    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {
        active = false;
    }
};

}