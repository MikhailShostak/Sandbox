#pragma once

#include <Foundation>

#include "Core/AWindowEvents.h"

class AWindow;

class AGestureRecognizer : public AObject
{
public:
    virtual AWindow &getWindow() const = 0;
};

class AWindowTouchDownEvent;
class AWindowTouchMoveEvent;
class AWindowTouchUpEvent;

namespace UI
{

class View;

class GestureRecognizer : public AGestureRecognizer
{
	View *view = nullptr;

	Math::IntegerVector point;
	ATouchID touchID = ATouchID::Touch0;
	ATouchModifier modifier = ATouchModifier::Undefined;

public:

	bool useAnyID = touchID == ATouchID::Undefined;
	bool useAnyModifier = modifier == ATouchModifier::Undefined;

	GestureRecognizer(ATouchModifier modifier):
		modifier(modifier)
	{

	}

	GestureRecognizer(ATouchID touchID = ATouchID::Touch0, ATouchModifier modifier = ATouchModifier::Undefined):
		touchID(touchID),
		modifier(modifier)
	{

	}

	AWindow &getWindow() const;

	bool isLoaded() const { return view; }
	virtual void load(View &view);
	virtual void unload();

	View &getView() const
	{
		return *view;
	}

	const Math::IntegerVector &getPoint() const
	{
		return point;
	}

	ATouchID getTouchID() const
	{
		return touchID;
	}

	void setTouchID(ATouchID touchID)
	{
		this->touchID = touchID;
	}

	ATouchModifier getTouchModifier() const
	{
		return modifier;
	}

	void setTouchModifier(ATouchModifier modifier)
	{
		this->modifier = modifier;
	}

	virtual bool shouldProcessTouchDown(AWindowTouchDownEvent &event) const
	{
		return checkTouchIDandModifier(event);
	}

	virtual bool shouldProcessTouchMove(AWindowTouchMoveEvent &event) const
	{
		return checkTouchIDandModifier(event);
	}

	virtual bool shouldProcessTouchUp(AWindowTouchUpEvent &event) const
	{
		return checkTouchIDandModifier(event);
	}

	virtual void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) {}
	virtual void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) {}
    virtual void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) {}
    virtual void onTouchWheel(AWindowTouchWheelEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) {}

protected:

	bool checkTouchIDandModifier(AWindowTouchEvent &event) const
	{
		if (!(useAnyID || getTouchID() == event.getTouchID()))
		{
			return false;
		}

		if (!(useAnyModifier || getTouchModifier() == event.getTouchModifier()))
		{
			return false;
		}

		return true;
	}

	void sendEventToView(AEvent &event);
	bool sendAcceptableEventToView(AAcceptableEvent &event);

	bool raycastToView(const Math::IntegerVector &screenPosition, const UI::View &view);
	bool raycastToView(const Math::IntegerVector &screenPosition);
};

class ViewEvent : public AEvent
{
    View &view;
public:
    ViewEvent(AObject &sender, View &view):
        AEvent(sender),
        view(view)
    {
    }

    View &getView() const { return view; }
};

class ViewAcceptableEvent : public AAcceptableEvent
{
    View &view;
public:
    ViewAcceptableEvent(AObject &sender, View &view):
        AAcceptableEvent(sender),
        view(view)
    {
    }

    View &getView() const { return view; }
};

class GestureEvent : public ViewAcceptableEvent
{
	const Math::IntegerVector &point;
public:
	GestureEvent(AObject &sender, View &view, const Math::IntegerVector &point):
        ViewAcceptableEvent(sender, view),
		point(point)
	{}

	const Math::IntegerVector &getPoint() const { return point; }
};

}
