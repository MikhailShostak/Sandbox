//CLASSGEN GENERATED REGION: Includes
#include "LaunchComponent.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
LaunchComponent::LaunchComponent()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void LaunchComponent::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Windows", toJSONValue(Windows));
}
void LaunchComponent::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Windows", value);
    fromJSONValue(value, Windows);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<::SharedReference<Core::Window2>> LaunchComponent::getWindows() const
{
    return this->Windows;
}
void LaunchComponent::setWindows(Array<::SharedReference<Core::Window2>> const &Windows)
{
    this->Windows = Windows;
}
void LaunchComponent::setWindows(Array<::SharedReference<Core::Window2>> &&Windows)
{
    this->Windows = std::move(Windows);
}
//CLASSGEN END REGION
void LaunchComponent::onLoad()
{
    
}

void LaunchComponent::onUnload()
{

}

void LaunchComponent::onUpdate()
{

}
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
