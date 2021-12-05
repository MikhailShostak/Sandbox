//CLASSGEN GENERATED REGION: Includes
#include "TestClass.gen.h"
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TestClass::TestClass()
{
    (*this).setArrayProperty({true,false,true,});
    (*this).setOrderedDictionaryProperty({{LegacyClassGen::VisibilityType::Public,LegacyClassGen::VisibilityType::TestTexture,},{LegacyClassGen::VisibilityType::Protected,LegacyClassGen::VisibilityType::TestTexture2,},{LegacyClassGen::VisibilityType::Private,LegacyClassGen::VisibilityType::TestTexture3,},});
    (*this).setAbstractProperty(false);
    (*this).ReadOnlyProperty = false;
    (*this).setReplicatedProperty(false);
    (*this).setMappedProperty(false);
    (*this).setSerializedProperty(false);
    (*this).setPropertyWithCallbacks(false);
    (*this).setProtectedProperty(false);
    (*this).setPrivateProperty(false);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TestClass::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("SerializedProperty", toJSONValue(SerializedProperty));
}
void TestClass::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("SerializedProperty", value);
    fromJSONValue(value, SerializedProperty);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<Boolean> TestClass::getArrayProperty() const
{
    return this->ArrayProperty;
}
void TestClass::setArrayProperty(Array<Boolean> const &ArrayProperty)
{
    this->ArrayProperty = ArrayProperty;
}
void TestClass::setArrayProperty(Array<Boolean> &&ArrayProperty)
{
    this->ArrayProperty = std::move(ArrayProperty);
}
OrderedDictionary<LegacyClassGen::VisibilityType, Graphics::Texture> TestClass::getOrderedDictionaryProperty() const
{
    return this->OrderedDictionaryProperty;
}
void TestClass::setOrderedDictionaryProperty(OrderedDictionary<LegacyClassGen::VisibilityType, Graphics::Texture> const &OrderedDictionaryProperty)
{
    this->OrderedDictionaryProperty = OrderedDictionaryProperty;
}
void TestClass::setOrderedDictionaryProperty(OrderedDictionary<LegacyClassGen::VisibilityType, Graphics::Texture> &&OrderedDictionaryProperty)
{
    this->OrderedDictionaryProperty = std::move(OrderedDictionaryProperty);
}
Boolean TestClass::getAbstractProperty() const
{
    return this->AbstractProperty;
}
void TestClass::setAbstractProperty(Boolean const &AbstractProperty)
{
    this->AbstractProperty = AbstractProperty;
}
void TestClass::setAbstractProperty(Boolean &&AbstractProperty)
{
    this->AbstractProperty = std::move(AbstractProperty);
}
Boolean TestClass::getReadOnlyProperty() const
{
    return this->ReadOnlyProperty;
}
Boolean TestClass::getReplicatedProperty() const
{
    return this->ReplicatedProperty;
}
void TestClass::setReplicatedProperty(Boolean const &ReplicatedProperty)
{
    this->ReplicatedProperty = ReplicatedProperty;
}
void TestClass::setReplicatedProperty(Boolean &&ReplicatedProperty)
{
    this->ReplicatedProperty = std::move(ReplicatedProperty);
}
Boolean TestClass::getMappedProperty() const
{
    return this->MappedProperty;
}
void TestClass::setMappedProperty(Boolean const &MappedProperty)
{
    this->MappedProperty = MappedProperty;
}
void TestClass::setMappedProperty(Boolean &&MappedProperty)
{
    this->MappedProperty = std::move(MappedProperty);
}
Boolean TestClass::getSerializedProperty() const
{
    return this->SerializedProperty;
}
void TestClass::setSerializedProperty(Boolean const &SerializedProperty)
{
    this->SerializedProperty = SerializedProperty;
}
void TestClass::setSerializedProperty(Boolean &&SerializedProperty)
{
    this->SerializedProperty = std::move(SerializedProperty);
}
Boolean TestClass::getPropertyWithCallbacks() const
{
    return this->PropertyWithCallbacks;
}
void TestClass::setPropertyWithCallbacks(Boolean const &PropertyWithCallbacks)
{
    Callback1();
    Callback2();
    this->PropertyWithCallbacks = PropertyWithCallbacks;
    Callback3();
    Callback4();
}
void TestClass::setPropertyWithCallbacks(Boolean &&PropertyWithCallbacks)
{
    Callback1();
    Callback2();
    this->PropertyWithCallbacks = std::move(PropertyWithCallbacks);
    Callback3();
    Callback4();
}
Boolean TestClass::getProtectedProperty() const
{
    return this->ProtectedProperty;
}
void TestClass::setProtectedProperty(Boolean const &ProtectedProperty)
{
    this->ProtectedProperty = ProtectedProperty;
}
void TestClass::setProtectedProperty(Boolean &&ProtectedProperty)
{
    this->ProtectedProperty = std::move(ProtectedProperty);
}
Boolean TestClass::getPrivateProperty() const
{
    return this->PrivateProperty;
}
void TestClass::setPrivateProperty(Boolean const &PrivateProperty)
{
    this->PrivateProperty = PrivateProperty;
}
void TestClass::setPrivateProperty(Boolean &&PrivateProperty)
{
    this->PrivateProperty = std::move(PrivateProperty);
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
