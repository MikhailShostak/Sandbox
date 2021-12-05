#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

//CLASSGEN END REGION
#include "ItemView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class GraphAdapter : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GraphAdapter This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    GraphAdapter();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    virtual ~GraphAdapter() {}
    virtual SizeType getCountNodes(const AObject &sender) const { return 0; }
    virtual SizeType getCountConnections(const AObject &sender) const { return 0; }
    virtual SharedReference<View> provideViewForNode(const AObject &sender, SizeType index) { return nullptr; }
    virtual SharedReference<View> provideViewForConnection(const AObject &sender, SizeType index) { return nullptr; }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
