#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <UI>

#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationHeader : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationHeader This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    ApplicationHeader();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
