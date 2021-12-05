//CLASSGEN GENERATED REGION: Includes
#include "NodeData.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
NodeData::NodeData()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void NodeData::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("ExecutionBranches", toJSONValue(ExecutionBranches));
    object.insert("Connections", toJSONValue(Connections));
    object.insert("Identifier", toJSONValue(Identifier));
    object.insert("Type", toJSONValue(Type));
    object.insert("Position", toJSONValue(Position));
    object.insert("Data", toJSONValue(Data));
}
void NodeData::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("ExecutionBranches", value);
    fromJSONValue(value, ExecutionBranches);
    value = AJSONValue();
    object.read("Connections", value);
    fromJSONValue(value, Connections);
    value = AJSONValue();
    object.read("Identifier", value);
    fromJSONValue(value, Identifier);
    value = AJSONValue();
    object.read("Type", value);
    fromJSONValue(value, Type);
    value = AJSONValue();
    object.read("Position", value);
    fromJSONValue(value, Position);
    value = AJSONValue();
    object.read("Data", value);
    fromJSONValue(value, Data);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
