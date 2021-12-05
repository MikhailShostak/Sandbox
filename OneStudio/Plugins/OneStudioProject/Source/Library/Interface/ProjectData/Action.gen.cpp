//CLASSGEN GENERATED REGION: Includes
#include "Action.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudioProject2
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Action::Action()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Action::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Name", toJSONValue(Name));
    object.insert("Tasks", toJSONValue(Tasks));
}
void Action::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Name", value);
    fromJSONValue(value, Name);
    value = AJSONValue();
    object.read("Tasks", value);
    fromJSONValue(value, Tasks);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
