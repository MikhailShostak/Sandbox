#pragma once

//CLASSGEN GENERATED REGION: Includes
//CLASSGEN END REGION
#include "ApplicationStateView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationWindowStateView : public LegacyClassGen::ApplicationStateView
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationWindowStateView This;
    typedef LegacyClassGen::ApplicationStateView Super;
    typedef void Interfaces;
public:
    ApplicationWindowStateView();
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
