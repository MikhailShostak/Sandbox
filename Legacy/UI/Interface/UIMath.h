#pragma once

#include <Graphics>

#include "UI/UIComponent.h"
#include "Includes/View.gen.h"

inline Math::Vector mapFromWorldSpaceToLocalSpace(const UI::View &toView, const Math::Vector &worldSpacePoint)
{
    UI::Component *component = toView.getOwner();
    //AEntity &entity = component->getOwner();
    return worldSpacePoint * (toView.getGraphicsMatrix() /** entity.getMatrix()*/).getInversed();
};

inline Math::Vector mapFromLocalSpaceToWorldSpace(const UI::View &fromView, const Math::Vector &localSpacePoint)
{
	UI::Component *component = fromView.getOwner();
	//AEntity &entity = component->getOwner();
	return localSpacePoint * (fromView.getGlobalMatrix() /** entity.getMatrix()*/);
};

inline Math::Vector mapFromLocalSpaceToWorldSpace(const UI::View &fromView, const Math::IntegerVector &localSpacePoint)
{
    return mapFromLocalSpaceToWorldSpace(fromView, localSpacePoint.getXY<Math::Vector>());
};

inline Math::Vector mapFromScreenSpaceToLocalSpace(const UI::View &toView, const Math::IntegerVector &screenSpacePoint, float z)
{
    return mapFromWorldSpaceToLocalSpace(toView, mapFromScreenSpaceToWorldSpace(*toView.getOwner()->getSpace(), screenSpacePoint, z));
}

inline Math::IntegerVector mapFromLocalSpaceToScreenSpace(const UI::View &fromView, const Math::Vector &localSpacePoint)
{
	return mapFromWorldSpaceToScreenSpace(*fromView.getOwner()->getSpace(), mapFromLocalSpaceToWorldSpace(fromView, localSpacePoint));
}

inline Math::IntegerVector mapFromLocalSpaceToScreenSpace(const UI::View &fromView, const Math::IntegerVector &localSpacePoint)
{
	return mapFromWorldSpaceToScreenSpace(*fromView.getOwner()->getSpace(), mapFromLocalSpaceToWorldSpace(fromView, localSpacePoint));
}

inline Math::Vector mapFromLocalSpaceToLocalSpace(const UI::View &fromView, const UI::View &toView, const Math::IntegerVector &localSpacePoint)
{
	return mapFromWorldSpaceToLocalSpace(toView, mapFromLocalSpaceToWorldSpace(fromView, localSpacePoint));
}

inline Math::Vector mapFromLocalSpaceToLocalSpace(const UI::View &fromView, const UI::View &toView, const Math::Vector &localSpacePoint)
{
	return mapFromWorldSpaceToLocalSpace(toView, mapFromLocalSpaceToWorldSpace(fromView, localSpacePoint));
}
