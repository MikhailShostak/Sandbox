#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"
#include "Math"
#include "VisibilityType.gen.h"
#include "Experimental"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TestClass : public AObject, public NewInterface
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
protected:
    typedef TestClass This;
    typedef AObject Super;
    typedef std::tuple<NewInterface> Interfaces;
protected:
    Array<Boolean> ArrayProperty;
OrderedDictionary<LegacyClassGen::VisibilityType, Graphics::Texture> OrderedDictionaryProperty;
Boolean AbstractProperty;
Boolean ReadOnlyProperty;
Boolean ReplicatedProperty;
Boolean MappedProperty;
Boolean SerializedProperty;
Boolean PropertyWithCallbacks;
Boolean ProtectedProperty;
Boolean PrivateProperty;
public:
    TestClass();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<Boolean> getArrayProperty() const;
    void setArrayProperty(Array<Boolean> const &ArrayProperty);
    void setArrayProperty(Array<Boolean> &&ArrayProperty);
    OrderedDictionary<LegacyClassGen::VisibilityType, Graphics::Texture> getOrderedDictionaryProperty() const;
    void setOrderedDictionaryProperty(OrderedDictionary<LegacyClassGen::VisibilityType, Graphics::Texture> const &OrderedDictionaryProperty);
    void setOrderedDictionaryProperty(OrderedDictionary<LegacyClassGen::VisibilityType, Graphics::Texture> &&OrderedDictionaryProperty);
    Boolean getAbstractProperty() const;
    void setAbstractProperty(Boolean const &AbstractProperty);
    void setAbstractProperty(Boolean &&AbstractProperty);
    Boolean getReadOnlyProperty() const;
    Boolean getReplicatedProperty() const;
    void setReplicatedProperty(Boolean const &ReplicatedProperty);
    void setReplicatedProperty(Boolean &&ReplicatedProperty);
    Boolean getMappedProperty() const;
    void setMappedProperty(Boolean const &MappedProperty);
    void setMappedProperty(Boolean &&MappedProperty);
    Boolean getSerializedProperty() const;
    void setSerializedProperty(Boolean const &SerializedProperty);
    void setSerializedProperty(Boolean &&SerializedProperty);
    Boolean getPropertyWithCallbacks() const;
    void setPropertyWithCallbacks(Boolean const &PropertyWithCallbacks);
    void setPropertyWithCallbacks(Boolean &&PropertyWithCallbacks);
    Boolean getProtectedProperty() const;
    void setProtectedProperty(Boolean const &ProtectedProperty);
    void setProtectedProperty(Boolean &&ProtectedProperty);
    Boolean getPrivateProperty() const;
    void setPrivateProperty(Boolean const &PrivateProperty);
    void setPrivateProperty(Boolean &&PrivateProperty);
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
