#pragma once

#include "Vector.h"

namespace Math
{

inline bool intersectRayWithPlane(const Vector &start, const Vector &end, const Vector &planePosition, const Vector &planeNormal, Vector &intersectPoint)
{
    Vector rayDirection = (end - start).getNormalized3();

    if (rayDirection.getDot3(planeNormal) < 0)
    {
        auto d = planeNormal.getDot3(planePosition);
        auto rayLenght = (d - planeNormal.getDot3(start) / planeNormal.getDot3(rayDirection));
        intersectPoint = start + rayDirection * rayLenght;
        return true;
    }

    return false;
}

}