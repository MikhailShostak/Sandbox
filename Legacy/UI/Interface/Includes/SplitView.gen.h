#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include "Foundation"
#include "SplitViewLayoutData.gen.h"
#include "Direction.gen.h"
#include "Math"

//CLASSGEN END REGION
#include "ImageView.gen.h"//TODO: temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

class SplitView;

class SplitViewGestureRecgonizer : public GestureRecognizer
{
    size_t primarySeparatorIndex = -1;
    size_t secondarySeparatorIndex = -1;
public:
    SharedReference<ImageView> primarySeparator = std::make_shared<ImageView>();
    SharedReference<ImageView> secondarySeparator = std::make_shared<ImageView>();

    SplitView *owner = nullptr;

    bool isAccepted = false;

    using GestureRecognizer::GestureRecognizer;

    size_t getSeparatorIndex(const Math::IntegerVector &point, size_t side) const;
    Math::Vector getSperatorPositionAt(size_t index, size_t side) const;

    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override;
    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override;
    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override;
};

//CLASSGEN GENERATED REGION: ClassHeader
class SplitView : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef SplitView This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    Array<UI::SplitViewLayoutData> Data;
UI::Direction Direction;
SignedInteger Spacing;
SignedInteger PrimarySeparatorSize;
SignedInteger SecondarySeparatorSize;
UnsignedInteger PrimaryAxisLimit;
Math::Offsets Padding;
public:
    SplitView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<UI::SplitViewLayoutData> getData() const;
    void setData(Array<UI::SplitViewLayoutData> const &Data);
    void setData(Array<UI::SplitViewLayoutData> &&Data);
    UI::Direction getDirection() const;
    void setDirection(UI::Direction const &Direction);
    void setDirection(UI::Direction &&Direction);
    SignedInteger getSpacing() const;
    void setSpacing(SignedInteger const &Spacing);
    void setSpacing(SignedInteger &&Spacing);
    SignedInteger getPrimarySeparatorSize() const;
    void setPrimarySeparatorSize(SignedInteger const &PrimarySeparatorSize);
    void setPrimarySeparatorSize(SignedInteger &&PrimarySeparatorSize);
    SignedInteger getSecondarySeparatorSize() const;
    void setSecondarySeparatorSize(SignedInteger const &SecondarySeparatorSize);
    void setSecondarySeparatorSize(SignedInteger &&SecondarySeparatorSize);
    UnsignedInteger getPrimaryAxisLimit() const;
    void setPrimaryAxisLimit(UnsignedInteger const &PrimaryAxisLimit);
    void setPrimaryAxisLimit(UnsignedInteger &&PrimaryAxisLimit);
    Math::Offsets getPadding() const;
    void setPadding(Math::Offsets const &Padding);
    void setPadding(Math::Offsets &&Padding);
//CLASSGEN END REGION
    UnsignedInteger getClampedPrimaryAxisLimit() const { return Math::getMin<UnsignedInteger>(getPrimaryAxisLimit(), getData().size()); }
    enum Direction
    {
        Up,
        Right,
        Down,
        Left,
    };

    struct Node
    {
        int32_t currentSize = 0;
        int32_t minimalSize = 0;
        void applyMinimalSize(int32_t size)
        {
            minimalSize = Math::getMax(minimalSize, size);
            currentSize = Math::getMax(currentSize, minimalSize);
        }
    };
    mutable Array<Node> primaryNodes;
    mutable Array<Node> secondaryNodes;

    SignedInteger getSpacingSize(int32_t axis) const;
    SignedInteger getSeparatorSize(int32_t axis) const;
    void setSeparatorSize(int32_t axis, SignedInteger &&Separator);

    SharedReference<SplitViewGestureRecgonizer> gestureRecognizer;
    void onLoad(ALoadEvent &event) override;
    Math::IntegerVector getContentSize() const override;
    void onLayout(AUpdateEvent &event) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
