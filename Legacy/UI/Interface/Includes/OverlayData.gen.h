#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include "LegacyGraphics.pch.hpp"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
struct OverlayData : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef OverlayData This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Math::Offsets Padding;
    Core::Alignment HorizontalAlignment;
    Core::Alignment VerticalAlignment;
public:
    OverlayData();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};*/

struct OverlayData : public Serializable
{
    typedef OverlayData This;
    typedef Serializable Super;
    typedef void Interfaces;

    union
    {
        UIOffsets padding;
        UIOffsets Padding = {};
    };
    union
    {
        struct
        {
            Core::Alignment horizontalAlignment;
            Core::Alignment verticalAlignment;
        };
        struct
        {
            Core::Alignment HorizontalAlignment;
            Core::Alignment VerticalAlignment;
        };
        Core::Alignment alignments[2] = { Core::Alignment::Start, Core::Alignment::Start };
    };

    Core::Alignment getHorizontalAlignment() const { return alignments[0]; }
    Core::Alignment getVerticalAlignment() const { return alignments[1]; }

    OverlayData();
    OverlayData(const OverlayData &data): Padding(data.Padding), VerticalAlignment(data.VerticalAlignment), HorizontalAlignment(data.HorizontalAlignment) {}
    OverlayData &operator =(const OverlayData &data)
    {
        Padding = data.Padding;
        VerticalAlignment = data.VerticalAlignment;
        HorizontalAlignment = data.HorizontalAlignment;
        return *this;
    }

    OverlayData(UIOffsets Padding, Core::Alignment HorizontalAlignment = Core::Alignment::Start, Core::Alignment VerticalAlignment = Core::Alignment::Start):
        Padding(Padding),
        VerticalAlignment(VerticalAlignment),
        HorizontalAlignment(HorizontalAlignment)
    {
    }

    OverlayData(UIOffsets Padding, std::initializer_list<Core::Alignment> alignments):
        Padding(Padding),
        alignments{ *alignments.begin(), *(alignments.begin() + 1) }
    {
    }

    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION

/*template<>
inline AJSONValue toJSONValue<UI::OverlayData>(const UI::OverlayData &value)
{
    AJSONObject object;
    object.insert("Padding", toJSONValue(value.Padding));
    object.insert("HorizontalAlignment", toJSONValue(value.HorizontalAlignment));
    object.insert("VerticalAlignment", toJSONValue(value.VerticalAlignment));
    return object;
}

template<>
inline void fromJSONValue<UI::OverlayData>(const AJSONValue &value, UI::OverlayData &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &object = value.asObject();

    AJSONValue padding;
    object.read("Padding", padding);
    fromJSONValue(padding, output.Padding);

    AJSONValue horizontalAlignment;
    object.read("HorizontalAlignment", horizontalAlignment);
    fromJSONValue(horizontalAlignment, output.HorizontalAlignment);

    AJSONValue verticalAlignment;
    object.read("VerticalAlignment", verticalAlignment);
    fromJSONValue(verticalAlignment, output.VerticalAlignment);
}*/
