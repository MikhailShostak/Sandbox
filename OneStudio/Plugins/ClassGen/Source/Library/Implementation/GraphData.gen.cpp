//CLASSGEN GENERATED REGION: Includes
#include "GraphData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
GraphData::GraphData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void GraphData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Nodes", toJSONValue(Nodes));
    object.insert("EntryPoint", toJSONValue(EntryPoint));
    object.insert("ReturnPoint", toJSONValue(ReturnPoint));
}
void GraphData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Nodes", value);
    fromJSONValue(value, Nodes);
    value = AJSONValue();
    object.read("EntryPoint", value);
    fromJSONValue(value, EntryPoint);
    value = AJSONValue();
    object.read("ReturnPoint", value);
    fromJSONValue(value, ReturnPoint);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
