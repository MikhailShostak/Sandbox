#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include <Graphics>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct FlexBoxData : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FlexBoxData This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    Core::Alignment Alignment;
public:
    FlexBoxData();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION

template<>
inline AJSONValue toJSONValue<UI::FlexBoxData>(const UI::FlexBoxData &value)
{
    AJSONObject object;
    object.insert("Alignment", toJSONValue(value.Alignment));
    return object;
}

template<>
inline void fromJSONValue<UI::FlexBoxData>(const AJSONValue &value, UI::FlexBoxData &output)
{
    if (!value.isObject())
    {
        return;
    }

    const AJSONObject &object = value.asObject();

    AJSONValue alignment;
    object.read("Alignment", alignment);
    fromJSONValue(alignment, output.Alignment);
}
