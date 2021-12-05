#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"

#include "Foundation"
#include <Experimental>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class AnchorView : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef AnchorView This;
    typedef UI::View Super;
    typedef void Interfaces;
public:
    AnchorView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    UI::View *view = nullptr;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
