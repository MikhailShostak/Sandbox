//CLASSGEN GENERATED REGION: Includes
#include "Connection.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Connection::Connection()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Connection::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Source", toJSONValue(Source));
    object.insert("Target", toJSONValue(Target));
    object.insert("Data", toJSONValue(Data));
}
void Connection::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Source", value);
    fromJSONValue(value, Source);
    value = AJSONValue();
    object.read("Target", value);
    fromJSONValue(value, Target);
    value = AJSONValue();
    object.read("Data", value);
    fromJSONValue(value, Data);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
