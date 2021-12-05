#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"

//CLASSGEN END REGION
#include <Experimental>
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TransitionView : public UI::Line
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TransitionView This;
    typedef UI::Line Super;
    typedef void Interfaces;
public:
    TransitionView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    UI::Connection connection;
    LegacyClassGen::ConditionalTransitionData data;

    using Super = UI::Line;

    SharedReference<UI::ImageView> transitionIcon = CreateShared<UI::ImageView>();

    SharedReference<UI::NodeView> getSourceNode() const
    {
        return destinationAnchor.view.as<UI::NodeView>();
    };

    SharedReference<UI::NodeView> getDestinationNode() const
    {
        return destinationAnchor.view.as<UI::NodeView>();
    };

    void onLoad(ALoadEvent &event)
    {
        transitionIcon->setImage(::TransitionIcon);
        addView(transitionIcon);
    }

    void onLayout(AUpdateEvent &event)
    {
        Super::onLayout(event);

        transitionIcon->setPosition(backgroundView->getPosition() + Core::align(transitionIcon->getSize(), getSize(), Core::Alignment::Center).getXY<Math::Vector>());
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
