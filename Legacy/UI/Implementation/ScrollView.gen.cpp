//CLASSGEN GENERATED REGION: Includes
#include "ScrollView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "CanvasView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "Overlay.gen.h"
#include "ImageView.gen.h"
#include "Slider.gen.h"

//CLASSGEN END REGION
#include <Graphics>
#include <UIDarkTheme>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ScrollView::ScrollView()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setAffectsParentLayout(false);
    UI::OverlayData item_576_0;
    UI::OverlayData item_577_1;
    UI::OverlayData item_578_2;
    item_578_2.HorizontalAlignment = Core::Alignment::End;
    UI::OverlayData item_580_3;
    item_580_3.VerticalAlignment = Core::Alignment::End;
    UI::OverlayData item_582_4;
    UI::OverlayData item_583_5;
    item_583_5.HorizontalAlignment = Core::Alignment::End;
    UI::OverlayData item_585_6;
    item_585_6.VerticalAlignment = Core::Alignment::End;
    (*this).setData({item_576_0,item_577_1,item_578_2,item_580_3,item_582_4,item_583_5,item_585_6,});
    (*this).setAlwaysShowVerticalShadow(false);
    (*this).setAlwaysShowHorizontalShadow(false);
    (*this).setContentFit(UI::ContentFit::Fit);
    Math::Offsets contentPaddings_590;
    contentPaddings_590.Top = 0.000000;
    contentPaddings_590.Right = 0.000000;
    contentPaddings_590.Bottom = 0.000000;
    contentPaddings_590.Left = 0.000000;
    (*this).setContentPaddings(contentPaddings_590);
    (*this).setSliderVisibility(UI::ScrollBarVisibility::Dynamic);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ScrollView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("AlwaysShowVerticalShadow", toJSONValue(AlwaysShowVerticalShadow));
    object.insert("AlwaysShowHorizontalShadow", toJSONValue(AlwaysShowHorizontalShadow));
    object.insert("ContentFit", toJSONValue(ContentFit));
    object.insert("ContentPaddings", toJSONValue(ContentPaddings));
    object.insert("SliderVisibility", toJSONValue(SliderVisibility));
}
void ScrollView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("AlwaysShowVerticalShadow", value);
    fromJSONValue(value, AlwaysShowVerticalShadow);
    value = AJSONValue();
    object.read("AlwaysShowHorizontalShadow", value);
    fromJSONValue(value, AlwaysShowHorizontalShadow);
    value = AJSONValue();
    object.read("ContentFit", value);
    fromJSONValue(value, ContentFit);
    value = AJSONValue();
    object.read("ContentPaddings", value);
    fromJSONValue(value, ContentPaddings);
    value = AJSONValue();
    object.read("SliderVisibility", value);
    fromJSONValue(value, SliderVisibility);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Math::IntegerVector ScrollView::getInternalSize() const
{
    return this->InternalSize;
}
void ScrollView::setInternalSize(Math::IntegerVector const &InternalSize)
{
    this->InternalSize = InternalSize;
}
void ScrollView::setInternalSize(Math::IntegerVector &&InternalSize)
{
    this->InternalSize = std::move(InternalSize);
}
Boolean ScrollView::getAlwaysShowVerticalShadow() const
{
    return this->AlwaysShowVerticalShadow;
}
void ScrollView::setAlwaysShowVerticalShadow(Boolean const &AlwaysShowVerticalShadow)
{
    this->AlwaysShowVerticalShadow = AlwaysShowVerticalShadow;
    requestLayoutUpdate();
}
void ScrollView::setAlwaysShowVerticalShadow(Boolean &&AlwaysShowVerticalShadow)
{
    this->AlwaysShowVerticalShadow = std::move(AlwaysShowVerticalShadow);
    requestLayoutUpdate();
}
Boolean ScrollView::getAlwaysShowHorizontalShadow() const
{
    return this->AlwaysShowHorizontalShadow;
}
void ScrollView::setAlwaysShowHorizontalShadow(Boolean const &AlwaysShowHorizontalShadow)
{
    this->AlwaysShowHorizontalShadow = AlwaysShowHorizontalShadow;
    requestLayoutUpdate();
}
void ScrollView::setAlwaysShowHorizontalShadow(Boolean &&AlwaysShowHorizontalShadow)
{
    this->AlwaysShowHorizontalShadow = std::move(AlwaysShowHorizontalShadow);
    requestLayoutUpdate();
}
UI::ContentFit ScrollView::getContentFit() const
{
    return this->ContentFit;
}
void ScrollView::setContentFit(UI::ContentFit const &ContentFit)
{
    this->ContentFit = ContentFit;
    requestLayoutUpdate();
}
void ScrollView::setContentFit(UI::ContentFit &&ContentFit)
{
    this->ContentFit = std::move(ContentFit);
    requestLayoutUpdate();
}
Math::Offsets ScrollView::getContentPaddings() const
{
    return this->ContentPaddings;
}
void ScrollView::setContentPaddings(Math::Offsets const &ContentPaddings)
{
    this->ContentPaddings = ContentPaddings;
    requestLayoutUpdate();
}
void ScrollView::setContentPaddings(Math::Offsets &&ContentPaddings)
{
    this->ContentPaddings = std::move(ContentPaddings);
    requestLayoutUpdate();
}
UI::ScrollBarVisibility ScrollView::getSliderVisibility() const
{
    return this->SliderVisibility;
}
void ScrollView::setSliderVisibility(UI::ScrollBarVisibility const &SliderVisibility)
{
    this->SliderVisibility = SliderVisibility;
    requestLayoutUpdate();
}
void ScrollView::setSliderVisibility(UI::ScrollBarVisibility &&SliderVisibility)
{
    this->SliderVisibility = std::move(SliderVisibility);
    requestLayoutUpdate();
}
void ScrollView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ScrollView");
    surface = CreateShared<UI::CanvasView>([this](UI::CanvasView *v)
    {
    }
);
    (*surface).setName("Surface");
    {
    }
    (*surface).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*surface).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*surface).setAffectsParentLayout(false);
    if (contentView)
    {
        (*surface).addView(contentView);
    }
    else
    {
        SharedReference<UI::Overlay> defaultOverlayContentView = CreateShared<UI::Overlay>([this](UI::Overlay *v)
        {
        }
);
        (*defaultOverlayContentView).setName("DefaultOverlayContentView");
        {
        }
        (*defaultOverlayContentView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*defaultOverlayContentView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*surface).addView(defaultOverlayContentView);
        contentView = defaultOverlayContentView;
    }
    (*this).addView(surface);
    shadowTop = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*shadowTop).setName("ShadowTop");
    {
    }
    (*shadowTop).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*shadowTop).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*shadowTop).setVisibility(UI::Visibility::SelfDisabled);
    (*shadowTop).setAffectsParentLayout(false);
    (*shadowTop).setImage(ShadowBottom);
    (*this).addView(shadowTop);
    shadowRight = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*shadowRight).setName("ShadowRight");
    {
    }
    (*shadowRight).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*shadowRight).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*shadowRight).setVisibility(UI::Visibility::SelfDisabled);
    (*shadowRight).setAffectsParentLayout(false);
    (*shadowRight).setImage(ShadowLeft);
    (*this).addView(shadowRight);
    shadowBottom = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*shadowBottom).setName("ShadowBottom");
    {
    }
    (*shadowBottom).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*shadowBottom).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*shadowBottom).setVisibility(UI::Visibility::SelfDisabled);
    (*shadowBottom).setAffectsParentLayout(false);
    (*shadowBottom).setImage(ShadowTop);
    (*this).addView(shadowBottom);
    shadowLeft = CreateShared<UI::ImageView>([this](UI::ImageView *v)
    {
    }
);
    (*shadowLeft).setName("ShadowLeft");
    {
    }
    (*shadowLeft).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*shadowLeft).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*shadowLeft).setVisibility(UI::Visibility::SelfDisabled);
    (*shadowLeft).setAffectsParentLayout(false);
    (*shadowLeft).setImage(ShadowRight);
    (*this).addView(shadowLeft);
    verticalSlider = CreateShared<UI::Slider>([this](UI::Slider *v)
    {
    }
);
    (*verticalSlider).setName("VerticalSlider");
    {
    }
    (*verticalSlider).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*verticalSlider).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*verticalSlider).setAffectsParentLayout(false);
    (*this).addView(verticalSlider);
    horizontalSlider = CreateShared<UI::Slider>([this](UI::Slider *v)
    {
    }
);
    (*horizontalSlider).setName("HorizontalSlider");
    {
    }
    (*horizontalSlider).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*horizontalSlider).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*horizontalSlider).setAffectsParentLayout(false);
    (*this).addView(horizontalSlider);
}
//CLASSGEN END REGION

void ScrollView::updateShadow()
{
    updateShadowVisibility();
    updateShadowSize();
}

void ScrollView::updateShadowVisibility()
{
}

void ScrollView::updateShadowSize()
{
    auto updateShadowOnAxis = [](auto &slider, auto &startShadow, auto &endShadow, uint8_t axis, bool forceVisibility) {
        const auto shadowTransitionScale = 10.0f;
        auto startShadowSize = startShadow->getSize();
        auto endShadowSize = endShadow->getSize();
        if (forceVisibility)
        {
            startShadowSize[axis] = startShadow->getContentSize()[axis];
            endShadowSize[axis] = endShadow->getContentSize()[axis];
        }
        else
        {
            if (slider->isScrollable())
            {
                const auto value = slider->getHandlePosition();
                const auto endValue = slider->getMaxHandlePosition();
                const auto originalShadowSize = startShadow->getContentSize()[axis];
                const auto shadowTransitionRange = shadowTransitionScale * originalShadowSize;
                const auto inversedShadowTransitionRange = Math::inverseInRange<Math::FloatType>(shadowTransitionRange, 0.0f, endValue);
                startShadowSize[axis] = Math::remapAndClamp<Math::FloatType>(value, 0.0f, shadowTransitionRange) * originalShadowSize;
                endShadowSize[axis] = Math::remapAndClamp<Math::FloatType>(value, endValue, inversedShadowTransitionRange) * originalShadowSize;
            }
            else
            {
                startShadowSize[axis] = 0;
                endShadowSize[axis] = 0;
            }
        }
        startShadow->setSize(startShadowSize);
        endShadow->setSize(endShadowSize);
    };

    updateShadowOnAxis(horizontalSlider, shadowLeft, shadowRight, 0, AlwaysShowHorizontalShadow);
    updateShadowOnAxis(verticalSlider, shadowTop, shadowBottom, 1, AlwaysShowVerticalShadow);
}

void ScrollView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    CullViews = true;

    Data = {
        UI::OverlayData{ {} },

        UI::OverlayData{ {}, Core::Alignment::Start, Core::Alignment::Start },
        UI::OverlayData{ {}, Core::Alignment::End, Core::Alignment::Start },
        UI::OverlayData{ {}, Core::Alignment::Start, Core::Alignment::End },
        UI::OverlayData{ {}, Core::Alignment::Start, Core::Alignment::Start },

        UI::OverlayData{ {}, Core::Alignment::End, Core::Alignment::Start },
        UI::OverlayData{ {}, Core::Alignment::Start, Core::Alignment::End },
    };

    //TODO: make this adjustable
    surface->affectsParentLayout = affectsParentLayout;
    if (!wheelRecognizer)
    {
        wheelRecognizer = CreateShared<TouchWheelGestureRecognizer>();
        addGestureRecognizer(wheelRecognizer);
        eventChannel.registerDelegate<TouchWheelGestureEvent>([this](TouchWheelGestureEvent &event) {
            if (event.isInside())
            {
                if (horizontalSlider->isVisible() && event.getWindowTouchEvent().getTouchModifier() == ATouchModifier::ShiftKey)
                {
                    horizontalSlider->setHandlePosition(horizontalSlider->getHandlePosition() - event.getWindowTouchEvent().getValue() * 60);
                    requestLayoutUpdate();
                    event.accept();
                }
                else if (verticalSlider->isVisible())
                {
                    verticalSlider->setHandlePosition(verticalSlider->getHandlePosition() - event.getWindowTouchEvent().getValue() * 60);
                    requestLayoutUpdate();
                    event.accept();
                }
                if (onScrollChanged)
                {
                    onScrollChanged();
                }
            }
        });

        auto updateContent = [this](SliderPositionChanged &event) {
            updateContentPosition();
            updateShadowSize();
            if (onScrollChanged)
            {
                onScrollChanged();
            }
        };
        horizontalSlider->eventChannel.registerDelegate(updateContent);
        verticalSlider->eventChannel.registerDelegate(updateContent);
    }
}

void ScrollView::updateContentPosition()
{
    const auto &paddings = getContentPaddingsInternal(contentView->getMinimalSize());
    updateContentPosition(paddings);
}

void ScrollView::updateContentPosition(const Math::IntegerOffsets &paddings)
{
    auto p = contentView->getPosition();
    contentView->setPosition(Math::Vector{
        paddings.Left - decltype(p.x)(horizontalSlider->getHandlePosition()),
        paddings.Top - decltype(p.x)(verticalSlider->getHandlePosition()),
        p.z
    });
}

Math::IntegerVector ScrollView::getContentSize() const
{
    Math::IntegerVector result;
    if (getHorizontalSizePolicy() == SizePolicy::ContentWrapped || getVerticalSizePolicy() == SizePolicy::ContentWrapped)
    {
        Math::IntegerVector contentSize = contentView->getContentSize();
        result = Math::IntegerVector{
            getHorizontalSizePolicy() == SizePolicy::ContentWrapped ? contentSize.x : 0,
            getVerticalSizePolicy() == SizePolicy::ContentWrapped ? contentSize.y : 0
        };
    }
    else
    {
        result = Math::IntegerVector{};
    }
    return result;
}

Math::Vector ScrollView::getSurfacePosition(const Math::Vector &offset) const
{
    return Math::getMax2(getSize(), contentView->getMinimalSize()).getXY<Math::Vector>() * offset;
}

Math::Vector ScrollView::getScrollOffset() const
{
    return getSurfacePosition(Math::Vector{
        horizontalSlider->getHandlePositionRatio(),
        verticalSlider->getHandlePositionRatio()
    });
}

Math::IntegerOffsets ScrollView::getContentPaddingsInternal(const Math::IntegerVector &contentSize) const
{
    Math::IntegerOffsets paddings;
    switch (getContentFit())
    {
    case UI::ContentFit::Fit:
        paddings = {};
        break;
    case UI::ContentFit::FullPaddings:
    {
        auto parentSize = contentView->getParent()->getSize().getXY<Math::Vector>();
        parentSize = parentSize + Math::getMax2<Math::FloatType>(parentSize - contentSize.getXY<Math::Vector>(), Math::Constants::NullVector);
        paddings = Math::IntegerOffsets{
            static_cast<int32_t>(parentSize.Y),
            static_cast<int32_t>(parentSize.X),
            static_cast<int32_t>(parentSize.Y),
            static_cast<int32_t>(parentSize.X)
        };
    }
    break;
    case UI::ContentFit::HalfPaddings:
    {
        auto parentSize = contentView->getParent()->getSize().getHalf2<Math::Vector>();
        parentSize = parentSize + Math::getMax2<Math::FloatType>(parentSize - contentSize.getHalf2<Math::Vector>(), Math::Constants::NullVector);
        paddings = Math::IntegerOffsets{
            static_cast<int32_t>(parentSize.Y),
            static_cast<int32_t>(parentSize.X),
            static_cast<int32_t>(parentSize.Y),
            static_cast<int32_t>(parentSize.X)
        };
    }
    break;
    case UI::ContentFit::Custom:
        paddings.Top = ContentPaddings.Top;
        paddings.Right = ContentPaddings.Right;
        paddings.Bottom = ContentPaddings.Bottom;
        paddings.Left = ContentPaddings.Left;
        break;
    }
    return paddings;
}

void ScrollView::onLayout(AUpdateEvent &event)
{
    bool layout = isNeededLayoutUpdate();
    Super::onLayout(event);
    if (layout)
    {
        static size_t s = 14;

        Math::IntegerVector size = getSize();

        Math::Vector contentPosition = contentView->getPosition();
        Math::IntegerVector contentSize = contentView->getMinimalSize();

        const auto &paddings = getContentPaddingsInternal(contentSize);

        contentSize.X += paddings.getHorizontalSpace();
        contentSize.Y += paddings.getVerticalSpace();

        Math::IntegerVector topLeft = Math::IntegerVector{ std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max() };
        Math::IntegerVector bottomRight = Math::IntegerVector{ std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::min() };
        for (size_t i = (DynamicCast<UI::Overlay>(contentView) ? StaticCast<UI::Overlay>(contentView)->getData().size() : 0); i < contentView->getViews().size(); ++i)
        {
            auto &view = contentView->getViews()[i];
            if (view->getVisibility() & Visibility::SelfCollapsed)
            {
                continue;
            }

            const Math::Vector position = view->getPosition();
            const Math::IntegerVector size = view->getMinimalSize();

            topLeft.x = std::min<int32_t>(topLeft.x, position.x);
            topLeft.y = std::min<int32_t>(topLeft.y, position.y);
            bottomRight.x = std::max<int32_t>(bottomRight.x, position.x + size.x);
            bottomRight.y = std::max<int32_t>(bottomRight.y, position.y + size.y);
        }
        contentSize = Math::getMax2(bottomRight, contentSize);

        horizontalSlider->setHandleSize(size.x);
        horizontalSlider->setSliderSize(contentSize.x);
        if (SliderVisibility == UI::ScrollBarVisibility::Always || contentSize.x > size.x && SliderVisibility != UI::ScrollBarVisibility::Never)
        {
            horizontalSlider->setSize(Math::IntegerVector{ static_cast<int32_t>(size.x - s + 1), static_cast<int32_t>(s) });
            horizontalSlider->setPosition(Math::Vector{ 0.0f, static_cast<float>(size.y - s), 0.0f });
            horizontalSlider->setExpanded(true);
            contentPosition.x = std::max<float>(contentPosition.x, -(contentSize.x - size.x));
        }
        else
        {
            horizontalSlider->setPosition(Math::Vector{});
            horizontalSlider->setExpanded(false);
            contentPosition.x = 0.0f;
        }

        verticalSlider->setHandleSize(size.y);
        verticalSlider->setSliderSize(contentSize.y);
        if (SliderVisibility == UI::ScrollBarVisibility::Always || contentSize.y > size.y && SliderVisibility != UI::ScrollBarVisibility::Never)
        {
            verticalSlider->setSize(Math::IntegerVector{ static_cast<int32_t>(s), static_cast<int32_t>(size.y - s + 1) });
            verticalSlider->setPosition(Math::Vector{ static_cast<float>(size.x - s), 0.0f, 0.0f });
            verticalSlider->setExpanded(true);
            contentPosition.y = std::max<float>(contentPosition.y, -(contentSize.y - size.y));
        }
        else
        {
            verticalSlider->setPosition(Math::Vector{});
            verticalSlider->setExpanded(false);
            contentPosition.y = 0.0f;
        }

        //contentPosition.X += paddings.Left;
        //contentPosition.Y += paddings.Top;
        
        updateContentPosition(paddings);
        //contentView->setSize(contentSize);
        //contentView->setPosition(contentPosition);


        auto layoutContentView = [&](size_t i, View &v) {
            switch (v.getSizePolicyAt(i))
            {
            case SizePolicy::Expanded:
                return getSize()[i];
            case SizePolicy::Fixed:
                return v.getSize()[i];
            }
            return contentSize[i];
        };
        contentView->setSize(Math::IntegerVector{ layoutContentView(0, *contentView), layoutContentView(1, *contentView) });

        updateShadow();
    }
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
