//CLASSGEN GENERATED REGION: Includes
#include "Slider.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassImplementation
Slider::Slider()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setHandleSize(1.000000);
    (*this).setSliderSize(100.000000);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Slider::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("HandlePosition", toJSONValue(HandlePosition));
    object.insert("HandleSize", toJSONValue(HandleSize));
    object.insert("SliderSize", toJSONValue(SliderSize));
    object.insert("SliderBorder", toJSONValue(SliderBorder));
}
void Slider::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("HandlePosition", value);
    fromJSONValue(value, HandlePosition);
    value = AJSONValue();
    object.read("HandleSize", value);
    fromJSONValue(value, HandleSize);
    value = AJSONValue();
    object.read("SliderSize", value);
    fromJSONValue(value, SliderSize);
    value = AJSONValue();
    object.read("SliderBorder", value);
    fromJSONValue(value, SliderBorder);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SignedInteger Slider::getHandlePosition() const
{
    return this->HandlePosition;
}
void Slider::setHandlePosition(SignedInteger const &HandlePosition)
{
    this->HandlePosition = HandlePosition;
    clampHandle();
    updateSlider();
    notifySlider();
}
void Slider::setHandlePosition(SignedInteger &&HandlePosition)
{
    this->HandlePosition = std::move(HandlePosition);
    clampHandle();
    updateSlider();
    notifySlider();
}
SizeInteger Slider::getHandleSize() const
{
    return this->HandleSize;
}
void Slider::setHandleSize(SizeInteger const &HandleSize)
{
    this->HandleSize = HandleSize;
    clampHandle();
    updateSlider();
    notifySlider();
}
void Slider::setHandleSize(SizeInteger &&HandleSize)
{
    this->HandleSize = std::move(HandleSize);
    clampHandle();
    updateSlider();
    notifySlider();
}
SizeInteger Slider::getSliderSize() const
{
    return this->SliderSize;
}
void Slider::setSliderSize(SizeInteger const &SliderSize)
{
    this->SliderSize = SliderSize;
    clampHandle();
    updateSlider();
    notifySlider();
}
void Slider::setSliderSize(SizeInteger &&SliderSize)
{
    this->SliderSize = std::move(SliderSize);
    clampHandle();
    updateSlider();
    notifySlider();
}
Math::Offsets Slider::getSliderBorder() const
{
    return this->SliderBorder;
}
void Slider::setSliderBorder(Math::Offsets const &SliderBorder)
{
    this->SliderBorder = SliderBorder;
    updateSlider();
}
void Slider::setSliderBorder(Math::Offsets &&SliderBorder)
{
    this->SliderBorder = std::move(SliderBorder);
    updateSlider();
}
SharedReference<DraggingGestureRecognizer> Slider::getDraggingComponent() const
{
    return this->DraggingComponent;
}
void Slider::setDraggingComponent(SharedReference<DraggingGestureRecognizer> const &DraggingComponent)
{
    this->DraggingComponent = DraggingComponent;
}
void Slider::setDraggingComponent(SharedReference<DraggingGestureRecognizer> &&DraggingComponent)
{
    this->DraggingComponent = std::move(DraggingComponent);
}
void Slider::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("Slider");
    sliderView = CreateShared<UI::Button>([this](UI::Button *v)
    {
    }
);
    (*sliderView).setName("SliderView");
    {
    }
    (*this).addView(sliderView);
}
//CLASSGEN END REGION
void Slider::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    this->DraggingComponent = CreateShared<DraggingGestureRecognizer>();

    sliderView->addGestureRecognizer(this->DraggingComponent);
    sliderView->eventChannel.registerDelegate<TouchMoveGestureEvent>([this](TouchMoveGestureEvent &event) {
        Math::IntegerVector s = getSize();
        const size_t mainDirection = s.getXYAspectRatio() > 1 ? 0 : 1;
        SignedInteger p = sliderView->getPosition()[mainDirection];
        if (p > 0)
        {
            this->HandlePosition = (p * this->SliderSize) / s[mainDirection];
        }
        else
        {
            this->HandlePosition = 0;
        }
        notifySlider();
    });

    updateSlider();
}

void Slider::onLayout(AUpdateEvent &event)
{
    Super::onLayout(event);

    this->DraggingComponent->draggingArea = Math::IntegerRectangle{ Math::IntegerVector{}, getSize() };
    const size_t mainDirection = getSize().getXYAspectRatio() > 1 ? 0 : 1;
    if (getSliderSize() > 0)
    {
        this->DraggingComponent->gridSize = getSize()[mainDirection] / getSliderSize();
    }
    updateSlider();
}

void Slider::clampHandle()
{
    this->HandlePosition = Math::clamp<SignedInteger>(this->HandlePosition, 0, Math::getMax<SignedInteger>(this->SliderSize - this->HandleSize, 0));
}

void Slider::updateSlider()
{
    if (!isLoaded())
    {
        return;
    }

    Math::IntegerVector s = getSize();

    const size_t mainDirection = s.getXYAspectRatio() > 1 ? 0 : 1;
    const size_t subDirection = 1 - mainDirection;

    if (this->SliderSize == 0)
    {
        //TODO: Use slider size == parent size?
        sliderView->setPosition(Math::Vector{});
        sliderView->setSize(getSize());
        return;
    }

    Math::Vector p{};
    p[mainDirection] = s[mainDirection] * (this->HandlePosition / float(this->SliderSize)); // int32_t(s[mainDirection] * (handlePosition / float(sliderSize)) - s[subDirection] / 2.0f);
    sliderView->setPosition(p);

    s[mainDirection] = std::max(s[subDirection], int32_t((s[mainDirection] * this->HandleSize) / float(this->SliderSize)));
    sliderView->setSize(s);
}

void Slider::notifySlider()
{
    SliderPositionChanged e(*this, this->HandlePosition);
    eventChannel.sendEvent(e);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
