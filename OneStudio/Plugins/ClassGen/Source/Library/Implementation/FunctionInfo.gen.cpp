//CLASSGEN GENERATED REGION: Includes
#include "FunctionInfo.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FunctionInfo::FunctionInfo()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FunctionInfo::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Attributes", toJSONValue(Attributes));
    object.insert("ExecutionBranches", toJSONValue(ExecutionBranches));
    object.insert("Callable", toJSONValue(Callable));
}
void FunctionInfo::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Attributes", value);
    fromJSONValue(value, Attributes);
    value = AJSONValue();
    object.read("ExecutionBranches", value);
    fromJSONValue(value, ExecutionBranches);
    value = AJSONValue();
    object.read("Callable", value);
    fromJSONValue(value, Callable);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
