//CLASSGEN GENERATED REGION: Includes
#include "Overlay.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Overlay::Overlay()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Overlay::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Data", toJSONValue(Data));
}
void Overlay::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Data", value);
    fromJSONValue(value, Data);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<UI::OverlayData> Overlay::getData() const
{
    return this->Data;
}
void Overlay::setData(Array<UI::OverlayData> const &Data)
{
    this->Data = Data;
}
void Overlay::setData(Array<UI::OverlayData> &&Data)
{
    this->Data = std::move(Data);
}
//CLASSGEN END REGION

Math::IntegerVector Overlay::getContentSize() const
{
    Math::IntegerVector contentSize{};
    for (size_t i = 0; i < Data.size() && i < getViews().size(); ++i)
    {
        const SharedReference<View> &view = getViews()[i];
        if (view->getVisibility() & Visibility::SelfCollapsed)
        {
            continue;
        }

        const OverlayData &data = Data[i];

        Math::IntegerVector childContentSize = view->getContentSize();
        auto getChildSize = [&](size_t index) {
            auto space = index == 0 ? data.padding.getHorizontalSpace() : data.padding.getVerticalSpace();
            switch (view->getSizePolicyAt(index))
            {
            case SizePolicy::Expanded:
            case SizePolicy::ContentWrapped:
                return childContentSize[index] + space;
            case SizePolicy::Fixed:
                return view->getSize()[index] + space;
            }
        };
        contentSize = Math::getMax2(contentSize, { getChildSize(0), getChildSize(1) });
    }
    return contentSize;
}

void Overlay::onLayout(AUpdateEvent &event)
{
    if (isNeededLayoutUpdate())
    {
        for (size_t i = 0; i < Data.size() && i < getViews().size(); ++i)
        {
            const SharedReference<View> &view = getViews()[i];
            if (view->getVisibility() & Visibility::SelfCollapsed)
            {
                continue;
            }

            const OverlayData &data = Data[i];
            Math::Vector position;
            Math::IntegerVector size;

            Math::IntegerVector contentSize = view->getContentSize();
            auto layout = [&](size_t index) {
                auto space = index == 0 ? data.padding.getHorizontalSpace() : data.padding.getVerticalSpace();
                auto offset = index == 0 ? data.padding.left : data.padding.top;

                SizePolicy sizePolicy = view->getSizePolicyAt(index);
                switch (sizePolicy)
                {
                case SizePolicy::Expanded:
                    position[index] = offset;
                    size[index] = getSize()[index] - space;
                    break;
                case SizePolicy::ContentWrapped:
                    position[index] = offset + align(contentSize[index], getSize()[index] - space, data.alignments[index]);
                    size[index] = contentSize[index];
                    break;
                case SizePolicy::Fixed:
                    position[index] = offset + align(view->getSize()[index], getSize()[index] - space, data.alignments[index]);
                    size[index] = view->getSize()[index];
                    break;
                }
            };

            layout(0);
            layout(1);
            view->setPosition(position);
            view->setSize(size);
        }
    }

    Super::onLayout(event);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
