#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION
#include <AData>
#include <MetaObjectSerializationHelper.h>
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
struct Settings : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
protected:
    typedef Settings This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Type;
    AJSONObject Data;
public:
    Settings();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    Serializable *DataInstance = nullptr;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION

template<>
inline AJSONValue toJSONValue(const Array<OneStudioProject2::Settings> &value)
{
    AJSONObject a;
    for (auto &v : value)
    {
        AJSONObject d;
        v.DataInstance->serialize(d);
        a.insert(v.Type, d);
    }
    return a;
}

template<>
inline void fromJSONValue(const AJSONValue &value, Array<OneStudioProject2::Settings> &output)
{
    AJSONObject o;

    if (!value.isObject())
    {
        return;
    }

    AJSONObject a = value.asObject();
    for (auto &pair : a)
    {
        if (!pair.second.isObject())
        {
            continue;
        }

        OneStudioProject2::Settings s;
        s.Type = pair.first;
        s.Data = pair.second.asObject();

        output.append(std::move(s));
    }
}
