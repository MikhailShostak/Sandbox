#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "GraphEditor.gen.h"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
#include "NodeSearchView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class FunctionLibraryEditor : public LegacyClassGen::GraphEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FunctionLibraryEditor This;
    typedef LegacyClassGen::GraphEditor Super;
    typedef void Interfaces;
public:
    FunctionLibraryEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::ListView> outlinerView;
    void onHierarchyCreate();
//CLASSGEN END REGION
    SharedReference<UI::NodeView> createNode(const LegacyClassGen::NodeData &node) { return nullptr; }
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        SharedReference<UI::NodeSearchView> nodeSearchView = CreateShared<UI::NodeSearchView>();
        AttachMenuToView(graphView, nodeSearchView);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
