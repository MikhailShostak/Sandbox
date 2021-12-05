#pragma once

#include "Vector.h"

#include <array>
#include <utility>

namespace Math
{

struct BoundingVolume
{
public:
    Math::Vector halfExtent;
    Math::Vector center;

    Math::Vector getMax() const { return this->center + this->halfExtent; }
    Math::Vector getMin() const { return this->center - this->halfExtent; }

    Math::Vector getRight() const { return this->center + Math::Vector{ this->halfExtent.x, 0, 0 }; }
    Math::Vector getTop() const { return this->center + Math::Vector{ 0, this->halfExtent.y, 0 }; }
    Math::Vector getBack() const { return this->center + Math::Vector{ 0, 0, this->halfExtent.z }; }
    Math::Vector getLeft() const { return this->center - Math::Vector{ this->halfExtent.x, 0, 0 }; }
    Math::Vector getBottom() const { return this->center - Math::Vector{ 0, this->halfExtent.y, 0 }; }
    Math::Vector getFront() const { return this->center - Math::Vector{ 0, 0, this->halfExtent.z }; }

    template<typename PlaneType = std::pair<Math::Vector, Math::Vector>, typename ContainerType = std::array<PlaneType, 6>>
    ContainerType getPlanes() const
    {
        return {
            PlaneType{ getRight(), Math::Vector{ 1, 0, 0 } },
            PlaneType{ getTop(), Math::Vector{ 0, 1, 0 } },
            PlaneType{ getBack(), Math::Vector{ 0, 0, 1 } },
            PlaneType{ getLeft(), Math::Vector{ -1, 0, 0 } },
            PlaneType{ getBottom(), Math::Vector{ 0, -1, 0 } },
            PlaneType{ getFront(), Math::Vector{ 0, 0, -1 } },
        };
    }
};

}
