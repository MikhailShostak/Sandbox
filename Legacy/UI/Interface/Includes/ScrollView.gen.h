#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Overlay.gen.h"
#include "Math"
#include "ContentFit.gen.h"
#include "ScrollBarVisibility.gen.h"

#include "Foundation"
#include "CanvasView.gen.h"
#include "View.gen.h"
#include "ImageView.gen.h"
#include "Slider.gen.h"

//CLASSGEN END REGION
#include <Data>

#include "Includes/CanvasView.gen.h"
#include "Includes/Slider.gen.h"
#include "Includes/Overlay.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ScrollView : public UI::Overlay
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ScrollView This;
    typedef UI::Overlay Super;
    typedef void Interfaces;
protected:
    Math::IntegerVector InternalSize;
Boolean AlwaysShowVerticalShadow;
Boolean AlwaysShowHorizontalShadow;
UI::ContentFit ContentFit;
Math::Offsets ContentPaddings;
UI::ScrollBarVisibility SliderVisibility;
public:
    ScrollView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Math::IntegerVector getInternalSize() const;
    void setInternalSize(Math::IntegerVector const &InternalSize);
    void setInternalSize(Math::IntegerVector &&InternalSize);
    Boolean getAlwaysShowVerticalShadow() const;
    void setAlwaysShowVerticalShadow(Boolean const &AlwaysShowVerticalShadow);
    void setAlwaysShowVerticalShadow(Boolean &&AlwaysShowVerticalShadow);
    Boolean getAlwaysShowHorizontalShadow() const;
    void setAlwaysShowHorizontalShadow(Boolean const &AlwaysShowHorizontalShadow);
    void setAlwaysShowHorizontalShadow(Boolean &&AlwaysShowHorizontalShadow);
    UI::ContentFit getContentFit() const;
    void setContentFit(UI::ContentFit const &ContentFit);
    void setContentFit(UI::ContentFit &&ContentFit);
    Math::Offsets getContentPaddings() const;
    void setContentPaddings(Math::Offsets const &ContentPaddings);
    void setContentPaddings(Math::Offsets &&ContentPaddings);
    UI::ScrollBarVisibility getSliderVisibility() const;
    void setSliderVisibility(UI::ScrollBarVisibility const &SliderVisibility);
    void setSliderVisibility(UI::ScrollBarVisibility &&SliderVisibility);
    SharedReference<UI::CanvasView> surface;
    SharedReference<UI::View> contentView;
    SharedReference<UI::ImageView> shadowTop;
    SharedReference<UI::ImageView> shadowRight;
    SharedReference<UI::ImageView> shadowBottom;
    SharedReference<UI::ImageView> shadowLeft;
    SharedReference<UI::Slider> verticalSlider;
    SharedReference<UI::Slider> horizontalSlider;
    void onHierarchyCreate();
//CLASSGEN END REGION
    ADelegate<void()> onScrollChanged;
    SharedReference<BorderImageView> backgroundView = SharedReference<BorderImageView>(Create<BorderImageView>());
    SharedReference<TouchWheelGestureRecognizer> wheelRecognizer;
private:
    Math::IntegerVector internalSize;
public:

    const Array<OverlayData> &getData() const { return DynamicCast<UI::Overlay>(this->contentView) ? StaticCast<UI::Overlay>(this->contentView)->getData() : Array<OverlayData>(); };
    void setData(const Array<OverlayData> &overlayData) { if (DynamicCast<UI::Overlay>(this->contentView)) { StaticCast<UI::Overlay>(this->contentView)->setData(overlayData); } }
    void setData(Array<OverlayData> &&overlayData) { if (DynamicCast<UI::Overlay>(this->contentView)) { StaticCast<UI::Overlay>(this->contentView)->setData(std::move(overlayData)); } }

    SharedReference<BorderImageView> &getBackgroundView()
    {
        return backgroundView;
    }

    SharedReference<BorderImageView> const &getBackgroundView() const
    {
        return backgroundView;
    }

    SharedReference<Legacy::Graphics::Texture> const &getImage() const
    {
        return backgroundView->getImage();
    }

    void setImage(SharedReference<Legacy::Graphics::Texture> const &image)
    {
        backgroundView->setImage(image);
    }

    void setImage(SharedReference<Legacy::Graphics::Texture> &&image)
    {
        backgroundView->setImage(std::move(image));
    }

    UIOffsets getBorder() const
    {
        return backgroundView->getBorder();
    }

    void setBorder(UIOffsets border)
    {
        backgroundView->setBorder(border);
    }

    bool getFillCenter() const
    {
        return backgroundView->getFillCenter();
    }

    void setFillCenter(bool fillCenter)
    {
        backgroundView->setFillCenter(fillCenter);
    }

    /*void addView(const SharedReference<UI::View> &view) override
    {
        if (view.data() == contentView.data() ||
            view.data() == tempContainer.data() ||
            view.data() == surface.data() ||
            view.data() == horizontalSlider.data() ||
            view.data() == verticalSlider.data())
        {
            Super::addView(view);
            return;
        }
        contentView->addView(view);
    }

    void insertView(size_t index, const SharedReference<UI::View> &view) override
    {
        if (view.data() == contentView.data() ||
            view.data() == tempContainer.data() ||
            view.data() == surface.data() ||
            view.data() == horizontalSlider.data() ||
            view.data() == verticalSlider.data())
        {
            Super::insertView(index, view);
            return;
        }
        contentView->insertView(index, view);
    }

    void removeView(const SharedReference<UI::View> &view) override
    {
        if (view.data() == contentView.data() ||
            view.data() == tempContainer.data() ||
            view.data() == surface.data() ||
            view.data() == horizontalSlider.data() ||
            view.data() == verticalSlider.data())
        {
            Super::removeView(view);
            return;
        }
        contentView->removeView(view);
    }

    void removeAllViews() override
    {
        contentView->removeAllViews();
    }*/
    Math::IntegerOffsets getContentPaddingsInternal(const Math::IntegerVector &) const;
    void updateContentPosition();
    void updateContentPosition(const Math::IntegerOffsets &paddings);

    void updateShadow();
    void updateShadowVisibility();
    void updateShadowSize();

    Math::IntegerVector getContentSize() const override;
    Math::Vector getSurfacePosition(const Math::Vector &offset = Math::Constants::NullVector) const;
    Math::Vector getScrollOffset() const;

    void onLoad(ALoadEvent &event) override;
    void onLayout(AUpdateEvent &event) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
