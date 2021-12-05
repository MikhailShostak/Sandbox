#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "GraphEditor.gen.h"

#include "Foundation"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class LogicEditor : public LegacyClassGen::GraphEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef LogicEditor This;
    typedef LegacyClassGen::GraphEditor Super;
    typedef void Interfaces;
public:
    LogicEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    SharedReference<UI::NodeView> createNode(const LegacyClassGen::NodeData &data) override
    {
        return CreateShared<UI::NodeView>();
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
