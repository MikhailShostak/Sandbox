//CLASSGEN GENERATED REGION: Includes
#include "Settings.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
Settings::Settings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Settings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Type", toJSONValue(Type));
    object.insert("Data", toJSONValue(Data));
}
void Settings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Type", value);
    fromJSONValue(value, Type);
    value = AJSONValue();
    object.read("Data", value);
    fromJSONValue(value, Data);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
*/
Settings::Settings()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Settings::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    AJSONObject d;
    DataInstance->serialize(d);
    object.insert(Type, d); //TODO: implemet code generation for this
}
void Settings::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    if (object)
    {
        auto it = object.begin();
        Type = it->first;
        Data = it->second.toObject();
    }
    /*AJSONValue value;
    value = AJSONValue();
    object.read("Type", value);
    fromJSONValue(value, Type);
    value = AJSONValue();
    object.read("Data", value);
    Data = value.toObject(); //TODO: implemet code generation for this*/
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
