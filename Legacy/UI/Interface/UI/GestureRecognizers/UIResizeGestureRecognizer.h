#pragma once

#include "Includes/ImageView.gen.h"
#include "UI/GestureRecognizers/UIGestureRecognizer.h"

namespace UI
{

class ResizeGestureRecognizer : public GestureRecognizer
{
	enum ControlPointType
	{
		TopLeft,
		Top,
		TopRight,
		Left,
		Right,
		BottomLeft,
		Bottom,
		BottomRight,
		Count,
		Undefined,
	};

	SharedReference<ImageView> controlPoints[Count];

	ControlPointType borderType = Undefined;
	Math::Vector startPosition;
	Math::IntegerVector startSize;
public:
    size_t gridSize = 0;
	//TODO: add constructors from base class
	ResizeGestureRecognizer(ATouchID touchID = ATouchID::Touch0, ATouchModifier modifier = ATouchModifier::Undefined);

	const SharedReference<Legacy::Graphics::Texture> &getControlPointImage() const
	{
		return controlPoints[0]->getImage();
	}

	void setControlPointImage(const SharedReference<Legacy::Graphics::Texture> &image)
	{
		for (size_t i = 0; i < Count; ++i)
		{
            controlPoints[i]->setImage(image);
		}
	}

	const Math::IntegerVector &getControlPointSize() const
	{
		return controlPoints[0]->getSize();
	}

	void setControlPointSize(const Math::IntegerVector &size)
	{
		for (size_t i = 0; i < Count; ++i)
		{
			controlPoints[i]->setSize(size);
		}
	}


	void load(View &view) override;
	void unload() override;
	void update();

protected:
	virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views);
	virtual void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views);
	virtual void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views);
};

}
