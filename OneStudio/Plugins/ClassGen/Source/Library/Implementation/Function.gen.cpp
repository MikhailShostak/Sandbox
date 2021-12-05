//CLASSGEN GENERATED REGION: Includes
#include "Function.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Function::Function()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Function::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Identifier", toJSONValue(Identifier));
    object.insert("TemplateParameters", toJSONValue(TemplateParameters));
    object.insert("InputArguments", toJSONValue(InputArguments));
    object.insert("OutputArguments", toJSONValue(OutputArguments));
}
void Function::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Identifier", value);
    fromJSONValue(value, Identifier);
    value = AJSONValue();
    object.read("TemplateParameters", value);
    fromJSONValue(value, TemplateParameters);
    value = AJSONValue();
    object.read("InputArguments", value);
    fromJSONValue(value, InputArguments);
    value = AJSONValue();
    object.read("OutputArguments", value);
    fromJSONValue(value, OutputArguments);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
