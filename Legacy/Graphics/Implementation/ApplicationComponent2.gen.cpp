//CLASSGEN GENERATED REGION: Includes
#include "ApplicationComponent2.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ApplicationComponent2::ApplicationComponent2()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ApplicationComponent2::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ApplicationComponent2::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<String> ApplicationComponent2::getTags() const
{
    return this->Tags;
}
void ApplicationComponent2::setTags(Array<String> const &Tags)
{
    this->Tags = Tags;
}
void ApplicationComponent2::setTags(Array<String> &&Tags)
{
    this->Tags = std::move(Tags);
}
Boolean ApplicationComponent2::getActive() const
{
    return this->Active;
}
void ApplicationComponent2::setActive(Boolean const &Active)
{
    this->Active = Active;
}
void ApplicationComponent2::setActive(Boolean &&Active)
{
    this->Active = std::move(Active);
}
//CLASSGEN END REGION
void ApplicationComponent2::load() { onLoad(); }
void ApplicationComponent2::unload() { onUnload(); }
void ApplicationComponent2::update() { onUpdate(); }
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
