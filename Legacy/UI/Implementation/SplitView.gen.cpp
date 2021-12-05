//CLASSGEN GENERATED REGION: Includes
#include "SplitView.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "LayoutUtils.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
SplitView::SplitView()
{
    (*this).setDirection(UI::Direction::Horizontal);
    (*this).setSpacing(0.000000);
    (*this).setPrimarySeparatorSize(8.000000);
    (*this).setSecondarySeparatorSize(8.000000);
    (*this).setPrimaryAxisLimit(-1.000000);
    Math::Offsets padding_5;
    padding_5.Top = 0.000000;
    padding_5.Right = 0.000000;
    padding_5.Bottom = 0.000000;
    padding_5.Left = 0.000000;
    (*this).setPadding(padding_5);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void SplitView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Data", toJSONValue(Data));
    object.insert("Direction", toJSONValue(Direction));
    object.insert("Spacing", toJSONValue(Spacing));
    object.insert("PrimarySeparatorSize", toJSONValue(PrimarySeparatorSize));
    object.insert("SecondarySeparatorSize", toJSONValue(SecondarySeparatorSize));
    object.insert("PrimaryAxisLimit", toJSONValue(PrimaryAxisLimit));
    object.insert("Padding", toJSONValue(Padding));
}
void SplitView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Data", value);
    fromJSONValue(value, Data);
    value = AJSONValue();
    object.read("Direction", value);
    fromJSONValue(value, Direction);
    value = AJSONValue();
    object.read("Spacing", value);
    fromJSONValue(value, Spacing);
    value = AJSONValue();
    object.read("PrimarySeparatorSize", value);
    fromJSONValue(value, PrimarySeparatorSize);
    value = AJSONValue();
    object.read("SecondarySeparatorSize", value);
    fromJSONValue(value, SecondarySeparatorSize);
    value = AJSONValue();
    object.read("PrimaryAxisLimit", value);
    fromJSONValue(value, PrimaryAxisLimit);
    value = AJSONValue();
    object.read("Padding", value);
    fromJSONValue(value, Padding);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<UI::SplitViewLayoutData> SplitView::getData() const
{
    return this->Data;
}
void SplitView::setData(Array<UI::SplitViewLayoutData> const &Data)
{
    this->Data = Data;
}
void SplitView::setData(Array<UI::SplitViewLayoutData> &&Data)
{
    this->Data = std::move(Data);
}
UI::Direction SplitView::getDirection() const
{
    return this->Direction;
}
void SplitView::setDirection(UI::Direction const &Direction)
{
    this->Direction = Direction;
}
void SplitView::setDirection(UI::Direction &&Direction)
{
    this->Direction = std::move(Direction);
}
SignedInteger SplitView::getSpacing() const
{
    return this->Spacing;
}
void SplitView::setSpacing(SignedInteger const &Spacing)
{
    this->Spacing = Spacing;
}
void SplitView::setSpacing(SignedInteger &&Spacing)
{
    this->Spacing = std::move(Spacing);
}
SignedInteger SplitView::getPrimarySeparatorSize() const
{
    return this->PrimarySeparatorSize;
}
void SplitView::setPrimarySeparatorSize(SignedInteger const &PrimarySeparatorSize)
{
    this->PrimarySeparatorSize = PrimarySeparatorSize;
}
void SplitView::setPrimarySeparatorSize(SignedInteger &&PrimarySeparatorSize)
{
    this->PrimarySeparatorSize = std::move(PrimarySeparatorSize);
}
SignedInteger SplitView::getSecondarySeparatorSize() const
{
    return this->SecondarySeparatorSize;
}
void SplitView::setSecondarySeparatorSize(SignedInteger const &SecondarySeparatorSize)
{
    this->SecondarySeparatorSize = SecondarySeparatorSize;
}
void SplitView::setSecondarySeparatorSize(SignedInteger &&SecondarySeparatorSize)
{
    this->SecondarySeparatorSize = std::move(SecondarySeparatorSize);
}
UnsignedInteger SplitView::getPrimaryAxisLimit() const
{
    return this->PrimaryAxisLimit;
}
void SplitView::setPrimaryAxisLimit(UnsignedInteger const &PrimaryAxisLimit)
{
    this->PrimaryAxisLimit = PrimaryAxisLimit;
}
void SplitView::setPrimaryAxisLimit(UnsignedInteger &&PrimaryAxisLimit)
{
    this->PrimaryAxisLimit = std::move(PrimaryAxisLimit);
}
Math::Offsets SplitView::getPadding() const
{
    return this->Padding;
}
void SplitView::setPadding(Math::Offsets const &Padding)
{
    this->Padding = Padding;
}
void SplitView::setPadding(Math::Offsets &&Padding)
{
    this->Padding = std::move(Padding);
}
//CLASSGEN END REGION

size_t SplitViewGestureRecgonizer::getSeparatorIndex(const Math::IntegerVector &point, size_t axis) const
{
    auto &views = owner->getViews();

    UnsignedInteger primaryAxisLimit = owner->getClampedPrimaryAxisLimit();
    auto delta = axis == getPrimaryAxisIndex(owner->getDirection()) ? 1 : primaryAxisLimit;

    for (size_t i = 0; i < views.size() - delta; i += delta)
    {
        auto previousView = views[i];
        if (point[axis] < previousView->getPosition()[axis])
        {
            return -1;
        }

        auto nextViewIndex = i + delta;
        if (nextViewIndex >= views.size())
        {
            return -1;
        }
        auto nextView = views[nextViewIndex];

        if ((previousView->getPosition()[axis] + previousView->getSize()[axis]) < point[axis] && point[axis] < nextView->getPosition()[axis])
        {
            return i / delta;
        }
    }

    return -1;
}

Math::Vector SplitViewGestureRecgonizer::getSperatorPositionAt(size_t index, size_t axis) const
{
    const auto &view = owner->getViews()[index];

    Math::Vector position{};
    for (size_t i = 0; i <= index; ++i)
    {
        position[axis] += (axis == getPrimaryAxisIndex(owner->getDirection()) ? owner->primaryNodes[i] : owner->secondaryNodes[i]).currentSize;
    }
    position[axis] += (owner->getSpacing() * 2 + owner->getSeparatorSize(axis)) * (index + 1) - owner->getSpacing() - owner->getSeparatorSize(axis);
    //position[axis] = view->getPosition()[axis] + owner->primaryNodes[index].currentSize - (owner->primaryNodes[index].currentSize - view->getSize()[axis]) / 2 + owner->getSpacing();
    return position;
}

void SplitViewGestureRecgonizer::onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
    if (views.size() < 2)
    {
        return;
    }

    if (views.front().first.get() == owner)
    {
        auto processTouchDown = [this, &point](auto &separatorView, auto &separatorIndex, auto axis) {
            separatorIndex = getSeparatorIndex(point, axis);
            if (separatorIndex == -1)
            {
                return;
            }

            owner->addView(separatorView);
            Math::IntegerVector size;
            size[axis] = owner->getSeparatorSize(axis);
            auto invertexAxis = getInvertedAxisIndex(axis);
            size[invertexAxis] = owner->getSize()[invertexAxis];

            separatorView->setPosition(getSperatorPositionAt(separatorIndex, axis));
            separatorView->setSize(size);
        };

        AxisData axis = getAxisData(owner->getDirection());
        processTouchDown(primarySeparator, primarySeparatorIndex, axis.Indexes.Primary);
        processTouchDown(secondarySeparator, secondarySeparatorIndex, axis.Indexes.Secondary);
    }
}

void SplitViewGestureRecgonizer::onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
    auto processTouchMove = [this, &point](auto &nodes, auto &separatorView, auto &separatorIndex, auto axis) {
        if (separatorIndex == -1)
        {
            return;
        }

        auto &previousNode = nodes[separatorIndex];
        auto &nextNode = nodes[separatorIndex + 1];

        Math::Vector position = getSperatorPositionAt(separatorIndex, axis);
        position[axis] = Math::clamp<float>(
            point[axis] - owner->getSeparatorSize(axis) / 2,
            position[axis] - (previousNode.currentSize - previousNode.minimalSize),
            position[axis] + (nextNode.currentSize - nextNode.minimalSize)
        );
        separatorView->setPosition(position);
    };

    AxisData axis = getAxisData(owner->getDirection());
    processTouchMove(owner->primaryNodes, primarySeparator, primarySeparatorIndex, axis.Indexes.Primary);
    processTouchMove(owner->secondaryNodes, secondarySeparator, secondarySeparatorIndex, axis.Indexes.Secondary);
}

void SplitViewGestureRecgonizer::onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
{
    auto processTouchUp = [this, &point](auto &nodes, auto &separatorView, auto &separatorIndex, auto axis) {
        if (separatorIndex == -1)
        {
            return;
        }

        auto &previousNode = nodes[separatorIndex];
        auto &nextNode = nodes[separatorIndex + 1];

        Math::Vector initialPosition = getSperatorPositionAt(separatorIndex, axis);
        Math::Vector newPosition = initialPosition;
        newPosition[axis] = Math::clamp<float>(
            point[axis] - owner->getSeparatorSize(axis) / 2,
            newPosition[axis] - (previousNode.currentSize - previousNode.minimalSize),
            newPosition[axis] + (nextNode.currentSize - nextNode.minimalSize)
        );

        auto delta = newPosition[axis] - initialPosition[axis];

        previousNode.currentSize += delta;
        nextNode.currentSize -= delta;

        separatorView->removeFromParent();
        separatorIndex = -1;
    };

    AxisData axis = getAxisData(owner->getDirection());
    processTouchUp(owner->primaryNodes, primarySeparator, primarySeparatorIndex, axis.Indexes.Primary);
    processTouchUp(owner->secondaryNodes, secondarySeparator, secondarySeparatorIndex, axis.Indexes.Secondary);
}

SignedInteger SplitView::getSpacingSize(int32_t axis) const
{
    return 2 * Spacing + getSeparatorSize(axis);
}

SignedInteger SplitView::getSeparatorSize(int32_t axis) const
{
    return getPrimaryAxisIndex(Direction) == axis ? getPrimarySeparatorSize() : getSecondarySeparatorSize();
}

void SplitView::setSeparatorSize(int32_t axis, SignedInteger &&value)
{
    if (getPrimaryAxisIndex(Direction) == axis)
    {
        setPrimarySeparatorSize(value);
    }
    else
    {
        setSecondarySeparatorSize(value);
    }
}

void SplitView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    
    if (!gestureRecognizer)
    {
        gestureRecognizer = CreateShared<SplitViewGestureRecgonizer>();
        gestureRecognizer->owner = this;

        APixmap pixmap;
        pixmap.setBuffer(Array<uint8_t>{ 128, 255 }, Math::IntegerVector{ 1, 1 }, APixmapDataFormat::GrayAlpha);

        SharedReference<Legacy::Graphics::Texture> texture = CreateShared<Legacy::Graphics::Texture>();
        texture->setPixmap(pixmap);
        texture->setWrapping(Legacy::Graphics::TextureWrapping::WrapToEdge);
        texture->load();
        gestureRecognizer->primarySeparator->setImage(texture);
        gestureRecognizer->secondarySeparator->setImage(texture);

        addGestureRecognizer(gestureRecognizer);
    }
}

template<typename This, typename SlotType>
size_t getValidSlotSize(This *_this, SlotType &&data)
{
    return Math::getMin(_this->getData().size(), _this->getViews().size());
}

template<typename This, typename Type, bool skipCollapsed = true>
void interateViews(This *_this, Type &&callback)
{
    size_t size = getValidSlotSize(_this, _this->getData());
    for (size_t i = 0; i < size; ++i)
    {
        const SharedReference<View> &view = _this->getViews()[i];
        if constexpr (skipCollapsed)
        {
            if (view->getVisibility() & Visibility::SelfCollapsed)
            {
                continue;
            }
        }

        callback(view, i, _this->getData()[i]);
    }
}

/*void layoutInBox(auto &begin, auto &end, UI::Direction direction, size_t separator) {

    while (begin != end)
    {

    }
};*/


Math::IntegerVector SplitView::getContentSize() const
{
    size_t validViews = getValidSlotSize(this, Data);
    Math::IntegerVector contentSize{};
    if (validViews == 0)
    {
        return contentSize;
    }

    AxisData axis = getAxisData(Direction);
    UnsignedInteger primaryAxisLimit = getClampedPrimaryAxisLimit();

    if (validViews <= primaryAxisLimit)
    {
        primaryNodes.resize(Math::getMax<size_t>(validViews, 1));
        secondaryNodes.resize(1);
    }
    else
    {
        primaryNodes.resize(primaryAxisLimit);
        secondaryNodes.resize((validViews / primaryAxisLimit) + 1);
    }

    Math::IntegerVector minimalSize;
    //for (size_t i = 0; i < Data.size() && i < getViews().size(); ++i)

    auto resetMinimalSize = [](auto &nodes) { for (auto &node : nodes) { node.minimalSize = 0; } };
    resetMinimalSize(primaryNodes);
    resetMinimalSize(secondaryNodes);

    interateViews(this, [&](auto &view, size_t i, auto &data) {
        minimalSize = view->getMinimalSize();
        if (view->getSizePolicyAt(axis.Indexes.Primary) != SizePolicy::Expanded)
        {
            contentSize[axis.Indexes.Primary] += minimalSize[axis.Indexes.Primary];
        }

        //contentSize[axis.Indexes.Secondary] = Math::getMax(contentSize[axis.Indexes.Secondary], minimalSize[axis.Indexes.Secondary]);
        
        auto x = i % primaryAxisLimit;
        auto y = i / primaryAxisLimit;

        primaryNodes[x].applyMinimalSize(minimalSize[axis.Indexes.Primary]);
        secondaryNodes[y].applyMinimalSize(minimalSize[axis.Indexes.Secondary]);
    });


    for (SplitView::Node &node : secondaryNodes)
    {
        contentSize[axis.Indexes.Secondary] += node.minimalSize;
    }

    if (secondaryNodes.size() > 1)
    {
        contentSize[axis.Indexes.Secondary] += (secondaryNodes.size() - 1) * getSpacingSize(axis.Indexes.Secondary);
    }

    return contentSize;
}

void SplitView::onLayout(AUpdateEvent &event)
{
    Super::onLayout(event);
    
    size_t validViews = getValidSlotSize(this, Data);
    if (validViews == 0)
    {
        return;
    }

    AxisData axis = getAxisData(Direction);
    UnsignedInteger primaryAxisLimit = getClampedPrimaryAxisLimit();

    Math::IntegerVector axisAlignedPadding = Math::IntegerVector{ Padding.Left, Padding.Top };

    Array<Math::IntegerVector> minimalSizes;
    minimalSizes.resize(validViews, Math::IntegerVector{});
    int32_t primarySize = 0;
    int32_t secondarySize = 0;

    if (validViews <= primaryAxisLimit)
    {
        primaryNodes.resize(Math::getMax<size_t>(validViews, 1));
        secondaryNodes.resize(1);
    }
    else
    {
        primaryNodes.resize(primaryAxisLimit);
        secondaryNodes.resize((validViews / primaryAxisLimit) + 1);
    }

    interateViews(this, [&](auto &view, size_t i, auto &data) {
        minimalSizes[i] = view->getMinimalSize();

        auto x = i % primaryAxisLimit;
        auto y = i / primaryAxisLimit;

        primaryNodes[x].applyMinimalSize(minimalSizes[i][axis.Indexes.Primary]);
        secondaryNodes[y].applyMinimalSize(minimalSizes[i][axis.Indexes.Secondary]);
    });

    for (auto &n : primaryNodes) { primarySize += n.currentSize; }
    for (auto &n : secondaryNodes) { secondarySize += n.currentSize; }


    Math::IntegerVector availableSpace = getSize() - Math::IntegerVector{ Padding.getHorizontalSpace(), Padding.getVerticalSpace() };
    availableSpace[axis.Indexes.Primary] -= (2 * Spacing + getSeparatorSize(axis.Indexes.Primary)) * (primaryNodes.size() - 1);
    availableSpace[axis.Indexes.Secondary] -= (2 * Spacing + getSeparatorSize(axis.Indexes.Secondary)) * (secondaryNodes.size() - 1);

    //expand node
    primaryNodes[primaryNodes.size() / 2].currentSize += availableSpace[axis.Indexes.Primary] - primarySize;
    secondaryNodes[secondaryNodes.size() / 2].currentSize += availableSpace[axis.Indexes.Secondary] - secondarySize;

    Math::Vector offset = axisAlignedPadding.getXY<Math::Vector>();
    struct LayoutRectangle
    {
        Math::Vector position;
        Math::IntegerVector size;
    };

    auto layout = [](LayoutRectangle &r, auto &view, auto &node, Core::Alignment alignment, size_t side) {
        if (view->getSizePolicyAt(side) == SizePolicy::Expanded)
        {
            r.size[side] = node.currentSize;
        }
        else
        {
            r.position[side] += Core::align(r.size[side], node.currentSize, alignment);
        }
    };

    interateViews(this, [&](auto &view, size_t i, auto &data) {
        auto x = i % primaryAxisLimit;
        auto y = i / primaryAxisLimit;

        LayoutRectangle r = { {}, minimalSizes[i] };

        r.position = offset;
        layout(r, view, primaryNodes[x], data.PrimaryAlignment, axis.Indexes.Primary);
        layout(r, view, secondaryNodes[y], data.SecondaryAlignment, axis.Indexes.Secondary);
        view->setPosition(r.position);
        view->setSize(r.size);

        if (x + 1 == primaryAxisLimit)
        {
            offset[axis.Indexes.Primary] = axisAlignedPadding[axis.Indexes.Primary];
            offset[axis.Indexes.Secondary] += secondaryNodes[y].currentSize + getSpacingSize(axis.Indexes.Secondary);
        }
        else
        {
            offset[axis.Indexes.Primary] += primaryNodes[x].currentSize + getSpacingSize(axis.Indexes.Primary);
        }
    });
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
