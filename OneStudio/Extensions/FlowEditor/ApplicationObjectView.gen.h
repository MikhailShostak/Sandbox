#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationObjectView : public UI::NamedNodeView
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationObjectView This;
    typedef UI::NamedNodeView Super;
    typedef void Interfaces;
public:
    ApplicationObjectView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    SharedReference<UI::Line> connect(const SharedReference<UI::NodeView> &sourceNode, const SharedReference<UI::NodeView> &destinationNode, const UI::Connection &connection) override
    {
        SharedReference<UI::Line> line = Super::connect(sourceNode, destinationNode, connection);
        line->setImage(::Line);
        line->sourceAnchor.alignments[0] = Core::Alignment::Center;
        line->sourceAnchor.alignments[1] = Core::Alignment::Center;
        line->sourceAnchor.view = sourceNode;
        line->destinationAnchor.alignments[0] = Core::Alignment::Center;
        line->destinationAnchor.alignments[1] = Core::Alignment::Center;
        line->destinationAnchor.view = destinationNode;
        return line;
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
