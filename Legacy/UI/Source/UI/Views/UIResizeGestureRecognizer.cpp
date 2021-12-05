#include "UIResizeGestureRecognizer.h"

#include "UITouchGestureRecognizer.h"
#include <Graphics>

namespace UI
{

ResizeGestureRecognizer::ResizeGestureRecognizer(ATouchID touchID, ATouchModifier modifier):
	GestureRecognizer(touchID, modifier)
{
	for (size_t i = 0; i < Count; ++i)
	{
		auto imageView = CreateShared<ImageView>();
		imageView->setSizePolicy(SizePolicy::Fixed);
		controlPoints[i] = imageView;
	}

	ApplyStyle(*this);
}

void ResizeGestureRecognizer::load(View &view)
{
	GestureRecognizer::load(view);

	for (size_t i = 0; i < Count; ++i)
	{
		view.addView(controlPoints[i]);
	}

	update();
}

void ResizeGestureRecognizer::unload()
{
	for (size_t i = 0; i < Count; ++i)
	{
		controlPoints[i]->removeFromParent();
    }

    GestureRecognizer::unload();
}

void ResizeGestureRecognizer::update()
{
	Math::Vector s = getView().getSize().getXY<Math::Vector>();
	Math::Vector hs = s.getHalf2<Math::Vector>();
    Math::Vector o = Math::Vector{ 5, 5 };
    Math::Vector os = Math::Vector{ 10, 10 } -o;
    Math::Vector hos = Math::Vector{ 5, 5 };
	controlPoints[TopLeft]->setPosition(Math::Vector{ 0.0f, 0.0f } - Math::Vector{ o.x, o.y });
	controlPoints[Top]->setPosition(Math::Vector{ hs.x, 0.0f } - Math::Vector{ hos.x, o.y });
	controlPoints[TopRight]->setPosition(Math::Vector{ s.x, 0.0f } - Math::Vector{ os.x, o.y });
	controlPoints[Left]->setPosition(Math::Vector{ 0.0f, hs.y } - Math::Vector{ o.x, hos.y });
	controlPoints[Right]->setPosition(Math::Vector{ s.x, hs.y } - Math::Vector{ os.x, hos.y });
	controlPoints[BottomLeft]->setPosition(Math::Vector{ 0.0f, s.y } - Math::Vector{ o.x, os.y });
	controlPoints[Bottom]->setPosition(Math::Vector{ hs.x, s.y } - Math::Vector{ hos.x, os.y });
    controlPoints[BottomRight]->setPosition(Math::Vector{ s.x, s.y } - Math::Vector{ os.x, os.y });
}

void ResizeGestureRecognizer::onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{

	for (size_t i = 0; i < Count; ++i)
	{
		if (views.front().first.get() == controlPoints[i].get())
		{
			borderType = ControlPointType(i);
			//startPosition = Math::Vector(event.getPosition().x, event.getPosition().y);
            startPosition = getView().getPosition() - event.getPosition().getXY<Math::Vector>();
            startSize = getView().getSize() - event.getPosition();
			event.accept();
			return;
		}
	}

	borderType = Undefined;
}

void ResizeGestureRecognizer::onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
	if (borderType == Undefined)
	{
		return;
	}

	Math::Vector p = getView().getPosition();
	Math::IntegerVector s = getView().getSize();

	Math::Vector position = startPosition + event.getPosition().getXY<Math::Vector>();
    Math::IntegerVector size = startSize + event.getPosition();

    if (gridSize > 0)
    {
        position.x -= std::fmod(position.x, gridSize);
        position.y -= std::fmod(position.y, gridSize);
        position.z -= std::fmod(position.z, gridSize);
    }

    if (gridSize > 0)
    {
        size.x -= std::fmod(size.x, gridSize);
        size.y -= std::fmod(size.y, gridSize);
    }
	
	//Top side
	switch (borderType)
	{
	case TopLeft:
	case Top:
	case TopRight:
		s.y -= position.y - p.y;
		p.y = position.y;
		break;
	default:
		break;
	}

	//Right side
	switch (borderType)
	{
	case TopRight:
	case Right:
	case BottomRight:
		s.x = size.x;
		break;
	default:
		break;
	}

	//Bottom side
	switch (borderType)
	{
	case BottomLeft:
	case Bottom:
	case BottomRight:
		s.y = size.y;
		break;
	default:
		break;
	}

	//Left side
	switch (borderType)
	{
	case TopLeft:
	case Left:
	case BottomLeft:
		s.x -= position.x - p.x;
		p.x = position.x;
		break;
	default:
		break;
	}

	p.x = std::min<float>(getView().getPosition().x + getView().getSize().x, p.x);
	p.y = std::min<float>(getView().getPosition().y + getView().getSize().y, p.y);

	s.x = std::max<int32_t>(0, s.x);
    s.y = std::max<int32_t>(0, s.y);

	getView().setPosition(p);
	getView().setSize(s);

	update();

    event.accept();

    ATransformEvent e(*this);
    sendEventToView(e);
}

void ResizeGestureRecognizer::onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
	borderType = Undefined;
}

}
