//CLASSGEN GENERATED REGION: Includes
#include "FlexBox.gen.h"
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
FlexBox::FlexBox()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setDirection(UI::Direction::Horizontal);
    (*this).setSpacing(0.000000);
    Math::Offsets padding_392;
    padding_392.Top = 0.000000;
    padding_392.Right = 0.000000;
    padding_392.Bottom = 0.000000;
    padding_392.Left = 0.000000;
    (*this).setPadding(padding_392);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FlexBox::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Data", toJSONValue(Data));
    object.insert("Direction", toJSONValue(Direction));
    object.insert("Spacing", toJSONValue(Spacing));
    object.insert("Padding", toJSONValue(Padding));
}
void FlexBox::deserialize(const AJSONObject &object)
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
    object.read("Padding", value);
    fromJSONValue(value, Padding);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<UI::FlexBoxData> FlexBox::getData() const
{
    return this->Data;
}
void FlexBox::setData(Array<UI::FlexBoxData> const &Data)
{
    this->Data = Data;
}
void FlexBox::setData(Array<UI::FlexBoxData> &&Data)
{
    this->Data = std::move(Data);
}
UI::Direction FlexBox::getDirection() const
{
    return this->Direction;
}
void FlexBox::setDirection(UI::Direction const &Direction)
{
    this->Direction = Direction;
}
void FlexBox::setDirection(UI::Direction &&Direction)
{
    this->Direction = std::move(Direction);
}
SignedInteger FlexBox::getSpacing() const
{
    return this->Spacing;
}
void FlexBox::setSpacing(SignedInteger const &Spacing)
{
    this->Spacing = Spacing;
}
void FlexBox::setSpacing(SignedInteger &&Spacing)
{
    this->Spacing = std::move(Spacing);
}
Math::Offsets FlexBox::getPadding() const
{
    return this->Padding;
}
void FlexBox::setPadding(Math::Offsets const &Padding)
{
    this->Padding = Padding;
}
void FlexBox::setPadding(Math::Offsets &&Padding)
{
    this->Padding = std::move(Padding);
}
//CLASSGEN END REGION

Math::IntegerVector FlexBox::getContentSize() const
{
    int8_t primaryAxis = Direction == UI::Direction::Horizontal ? 0 : 1;
    int8_t secondaryAxis = 1 - primaryAxis;

    Math::IntegerVector minimalSize;
    Math::IntegerVector contentSize{};
    bool usesSpacing = false;
    for (size_t i = 0; i < Data.size() && i < getViews().size(); ++i)
    {
        const SharedReference<View> &view = getViews()[i];
        if (view->getVisibility() & Visibility::SelfCollapsed)
        {
            continue;
        }
        const FlexBoxData &data = Data[i];

        minimalSize = view->getMinimalSize();
        //if (view->getSizePolicyAt(primaryAxis) != SizePolicy::Expanded)
        {
            contentSize[primaryAxis] += minimalSize[primaryAxis];
        }

        contentSize[primaryAxis] += Spacing;
        usesSpacing = true;
        contentSize[secondaryAxis] = Math::getMax(contentSize[secondaryAxis], minimalSize[secondaryAxis]);
    }
    if (usesSpacing)
    {
        contentSize[primaryAxis] -= Spacing;
    }

    return contentSize + Math::IntegerVector{ Padding.getHorizontalSpace(), Padding.getVerticalSpace() };
}

void FlexBox::onLayout(AUpdateEvent &event)
{
    Super::onLayout(event);

    if (getViews().empty())
    {
        return;
    }

    int8_t primaryAxis = Direction == UI::Direction::Horizontal ? 0 : 1;
    int8_t secondaryAxis = 1 - primaryAxis;

    Math::IntegerVector axisAlignedPadding = Math::IntegerVector{ Padding.Left, Padding.Top };
    Math::IntegerVector availableSpace = getSize() - Math::IntegerVector{ Padding.getHorizontalSpace(), Padding.getVerticalSpace() };
    availableSpace[primaryAxis] -= Spacing * (getViews().size() - 1);

    Array<Math::IntegerVector> minimalSizes;
    minimalSizes.resize(getViews().size(), Math::IntegerVector{}); //TODO: fix indexes and use reserve instead resize
    int32_t primarySize = 0;
    size_t count = 0;
    for (size_t i = 0; i < Data.size() && i < getViews().size(); ++i)
    {
        const SharedReference<View> &view = getViews()[i];

        if (view->getVisibility() & Visibility::SelfCollapsed)
        {
            continue;
        }

        const FlexBoxData &data = Data[i];

        minimalSizes[i] = view->getMinimalSize();
        if (view->getSizePolicyAt(primaryAxis) != SizePolicy::Expanded)
        {
            primarySize += minimalSizes[i][primaryAxis];
        }
        else
        {
            ++count;
        }
    }


    int32_t offset = axisAlignedPadding[primaryAxis];

    int32_t expandedSize = count != 0 ? (availableSpace[primaryAxis] - primarySize) / count : 0;

    for (size_t i = 0; i < Data.size() && i < getViews().size(); ++i)
    {
        const SharedReference<View> &view = getViews()[i];

        if (view->getVisibility() & Visibility::SelfCollapsed)
        {
            continue;
        }

        const FlexBoxData &data = Data[i];

        Math::Vector position;
        Math::IntegerVector &size = minimalSizes[i];

        position[primaryAxis] = offset;
        if (view->getSizePolicyAt(primaryAxis) == SizePolicy::Expanded)
        {
            size[primaryAxis] = expandedSize;
        }

        if (view->getSizePolicyAt(secondaryAxis) == SizePolicy::Expanded)
        {
            position[secondaryAxis] = axisAlignedPadding[secondaryAxis];
            size[secondaryAxis] = availableSpace[secondaryAxis];
        }
        else
        {
            position[secondaryAxis] = axisAlignedPadding[secondaryAxis] + Core::align(size[secondaryAxis], availableSpace[secondaryAxis], data.Alignment);
        }

        view->setPosition(position);
        view->setSize(size);

        offset += size[primaryAxis] + Spacing;
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
