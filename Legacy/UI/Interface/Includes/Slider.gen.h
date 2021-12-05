#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include "Math"

#include "Foundation"
#include "Button.gen.h"

//CLASSGEN END REGION
#include "UI/GestureRecognizers/UIDraggingGestureRecognizer.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Slider : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Slider This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    SignedInteger HandlePosition;
SizeInteger HandleSize;
SizeInteger SliderSize;
Math::Offsets SliderBorder;
SharedReference<DraggingGestureRecognizer> DraggingComponent;
public:
    Slider();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SignedInteger getHandlePosition() const;
    void setHandlePosition(SignedInteger const &HandlePosition);
    void setHandlePosition(SignedInteger &&HandlePosition);
    SizeInteger getHandleSize() const;
    void setHandleSize(SizeInteger const &HandleSize);
    void setHandleSize(SizeInteger &&HandleSize);
    SizeInteger getSliderSize() const;
    void setSliderSize(SizeInteger const &SliderSize);
    void setSliderSize(SizeInteger &&SliderSize);
    Math::Offsets getSliderBorder() const;
    void setSliderBorder(Math::Offsets const &SliderBorder);
    void setSliderBorder(Math::Offsets &&SliderBorder);
    SharedReference<DraggingGestureRecognizer> getDraggingComponent() const;
    void setDraggingComponent(SharedReference<DraggingGestureRecognizer> const &DraggingComponent);
    void setDraggingComponent(SharedReference<DraggingGestureRecognizer> &&DraggingComponent);
    SharedReference<UI::Button> sliderView;
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event) override;
    void onLayout(AUpdateEvent &event) override;
    void clampHandle();
    void updateSlider();
    void notifySlider();

    SizeInteger getMaxHandlePosition() const { return getSliderSize() > getHandleSize() ? getSliderSize() - getHandleSize() : 0; }
    Math::FloatType getHandlePositionRatio() const { return getSliderSize() > getHandleSize() ? Math::FloatType(getHandlePosition()) / getMaxHandlePosition() : 0; };
    void setHandlePositionRatio(Math::FloatType ratio) { setHandlePosition(getMaxHandlePosition() * ratio); }
    Math::FloatType getHandleSizeRatio() const { return Math::FloatType(getHandleSize()) / getSliderSize(); };
    Math::FloatType isScrollable() const { return getHandleSizeRatio() < 1; };
};

class SliderPositionChanged : public UIPropertyChangeEvent<size_t>
{
public:
    using Super = UIPropertyChangeEvent<size_t>;
    using Super::Super;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
