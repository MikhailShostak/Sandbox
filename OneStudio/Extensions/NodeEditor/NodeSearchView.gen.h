#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
#include "Core/BaseCGType.h"
#include "Includes/FunctionInfo.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class NodeSearchView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef NodeSearchView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    NodeSearchView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::TextField> searchField;
    SharedReference<UI::ListView> searchResults;
    SharedReference<UI::TextButton> addButton;
    void onHierarchyCreate();
//CLASSGEN END REGION
    Array<LegacyClassGen::FunctionInfo> AvailableFunctions;
    Array<LegacyClassGen::FunctionInfo> FoundFunctions;
    void setType(const SharedReference<LegacyClassGen::BaseCGType> &type);
    void onLoad(ALoadEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
