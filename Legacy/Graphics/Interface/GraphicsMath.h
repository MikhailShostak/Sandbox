#pragma once

#include <Foundation>

#include "Core/AWindow.h"

inline Math::Vector mapFromScreenSpaceToProjectedSpace(const Math::IntegerVector &viewport, const Math::IntegerVector &position, float z = 0.0f)
{
    const Math::IntegerVector halfWindowSize = viewport.getHalf2<Math::IntegerVector>();
    return Math::Vector{ float(position.x - halfWindowSize.x) / halfWindowSize.x, float(viewport.y - position.y - halfWindowSize.y) / halfWindowSize.y, z };
};

inline Math::IntegerVector mapFromProjectedSpaceToScreenSpace(const Math::IntegerVector &viewport, const Math::Vector &position)
{
    const Math::Vector halfWindowSize = viewport.getHalf2<Math::Vector>();
    return Math::IntegerVector{
        static_cast<int32_t>((position.x + 1.0f) * halfWindowSize.x),
        static_cast<int32_t>((2.0f - (position.y + 1.0f)) * halfWindowSize.y)
    };
};

#include "Core/ASpace.h"

inline Math::Vector mapFromCameraProjectionToViewSpace(const ACamera &camera, const Math::IntegerVector &position, float z = 0.0f)
{
    const Math::Vector projectedPoint = mapFromScreenSpaceToProjectedSpace(camera.resolution, position, z);
    const Math::Matrix invMat = camera.getProjectionMatrix().getInversed();
    const Math::Vector result = projectedPoint * invMat;
    return result;
};

inline Math::Vector mapFromCameraProjectionToWorldSpace(const ACamera &camera, const Math::IntegerVector &position, float z = 0.0f)
{
    const Math::Vector projectedPoint = mapFromScreenSpaceToProjectedSpace(camera.resolution, position, z);
    const Math::Matrix invMat = camera.getMatrix().getInversed();
    const Math::Vector result = projectedPoint * invMat;
    return result;
};

inline Math::IntegerVector mapFromViewSpaceToCameraProjection(const ACamera &camera, const Math::Vector &position)
{
    return mapFromProjectedSpaceToScreenSpace(camera.resolution, position * camera.getProjectionMatrix());
};

inline Math::IntegerVector mapFromWorldSpaceToCameraProjection(const ACamera &camera, const Math::Vector &position)
{
    return mapFromProjectedSpaceToScreenSpace(camera.resolution, position * camera.getMatrix());
};

inline Math::Vector mapFromScreenSpaceToViewSpace(const ASpace &space, const Math::IntegerVector &position, float z = 0.0f)
{
    return mapFromCameraProjectionToViewSpace(*space.getCamera(), position, z);
};

inline Math::Vector mapFromScreenSpaceToWorldSpace(const ASpace &space, const Math::IntegerVector &position, float z = 0.0f)
{
    return mapFromCameraProjectionToWorldSpace(*space.getCamera(), position, z);
};

inline Math::IntegerVector mapFromViewSpaceToScreenSpace(const ASpace &space, const Math::Vector &position)
{
    return mapFromViewSpaceToCameraProjection(*space.getCamera(), position);
};

inline Math::IntegerVector mapFromWorldSpaceToScreenSpace(const ASpace &space, const Math::Vector &position)
{
    return mapFromViewSpaceToCameraProjection(*space.getCamera(), position);
};

#include "Core/AEntity.h"

inline Math::Vector mapFromWorldSpaceToLocalSpace(const AEntity &entity, const Math::Vector &worldSpacePoint)
{
    return worldSpacePoint * entity.getMatrix().getInversed();
};

inline Math::Vector mapFromLocalSpaceToWorldSpace(const AEntity &entity, const Math::IntegerVector &localSpacePoint)
{
    return Math::Vector{ static_cast<float>(localSpacePoint.x), static_cast<float>(localSpacePoint.y), 0 } * entity.getMatrix();
};

inline Math::Vector mapFromScreenSpaceToLocalSpace(const AEntity &entity, const Math::IntegerVector &screenSpacePoint, float z)
{
    return mapFromWorldSpaceToLocalSpace(entity, mapFromScreenSpaceToWorldSpace(*entity.getSpace(), screenSpacePoint, z));
}

inline Math::IntegerVector mapFromLocalSpaceToScreenSpace(const AEntity &entity, const Math::IntegerVector &localSpacePoint)
{
    return mapFromWorldSpaceToScreenSpace(*entity.getSpace(), mapFromLocalSpaceToWorldSpace(entity, localSpacePoint));
}
