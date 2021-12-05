//CLASSGEN GENERATED REGION: Includes
#include "Application2.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace Core
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
Application2::Application2()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Application2::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Components", toJSONValue(Components));
}
void Application2::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Components", value);
    fromJSONValue(value, Components);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<::SharedReference<Core::ApplicationComponent2>> Application2::getComponents() const
{
    return this->Components;
}
void Application2::setComponents(Array<::SharedReference<Core::ApplicationComponent2>> const &Components)
{
    this->Components = Components;
}
void Application2::setComponents(Array<::SharedReference<Core::ApplicationComponent2>> &&Components)
{
    this->Components = std::move(Components);
}
//CLASSGEN END REGION
SignedInteger Application2::execute()
{
    ApplicationStorage::getInstance().instance = this;

    for(auto &component : this->Components)
    {
        component->onLoad();
    }

    while(running)
    {
        for(auto &component : this->Components)
        {
            component->onUpdate();
        }
    }

    for(auto &component : this->Components)
    {
        component->onUnload();
    }

    ApplicationStorage::getInstance().instance = nullptr;

    return error.value();
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
