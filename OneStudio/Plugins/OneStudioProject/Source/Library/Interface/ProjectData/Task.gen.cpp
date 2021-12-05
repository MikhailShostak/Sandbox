//CLASSGEN GENERATED REGION: Includes
#include "Task.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Task::Task()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Task::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Type", toJSONValue(Type));
    object.insert("Title", toJSONValue(Title));
    object.insert("Values", toJSONValue(Values));
}
void Task::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Type", value);
    fromJSONValue(value, Type);
    value = AJSONValue();
    object.read("Title", value);
    fromJSONValue(value, Title);
    value = AJSONValue();
    object.read("Values", value);
    fromJSONValue(value, Values);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
