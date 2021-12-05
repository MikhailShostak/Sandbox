//CLASSGEN GENERATED REGION: Includes
#include "PinNodeView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "FlexBox.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "Direction.gen.h"
#include "View.gen.h"

//CLASSGEN END REGION
#include <Graphics>
#include <UIDarkTheme>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PinNodeView::PinNodeView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PinNodeView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void PinNodeView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PinNodeView::onHierarchyCreate()
{
    SharedReference<UI::FlexBox> content = SharedReference<UI::FlexBox>(Create<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
));
    (*content).setName("Content");
    {
    }
    (*content).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*content).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_472_0;
    UI::FlexBoxData item_473_1;
    UI::FlexBoxData item_474_2;
    (*content).setData({item_472_0,item_473_1,item_474_2,});
    inputPins = SharedReference<UI::FlexBox>(Create<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
));
    (*inputPins).setName("InputPins");
    {
    }
    (*inputPins).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*inputPins).setDirection(UI::Direction::Vertical);
    (*content).addView(inputPins);
    if (nodeContent)
    {
        (*content).addView(nodeContent);
    }
    else
    {
        SharedReference<UI::View> emptyContent = SharedReference<UI::View>(Create<UI::View>([this](UI::View *v)
        {
        }
));
        (*emptyContent).setName("EmptyContent");
        {
        }
        (*emptyContent).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*emptyContent).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*content).addView(emptyContent);
        nodeContent = emptyContent;
    }
    outputPins = SharedReference<UI::FlexBox>(Create<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
));
    (*outputPins).setName("OutputPins");
    {
    }
    (*outputPins).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*outputPins).setDirection(UI::Direction::Vertical);
    (*content).addView(outputPins);
    (*this).content = content;
    Super::onHierarchyCreate();
    setName("PinNodeView");
}
//CLASSGEN END REGION

SharedReference<UI::Line> PinNodeView::connect(const SharedReference<UI::NodeView> &sourceNode, const SharedReference<UI::NodeView> &targetNode, const UI::Connection &connection)
{
    SharedReference<UI::Line> line = Super::connect(sourceNode, targetNode, connection);
    line->setImage(::Line);

    SharedReference<PinNodeView::Pin> sourcePin = StaticCast<PinNodeView::Pin>(sourceNode->findSource(connection));
    line->sourceAnchor.view = sourcePin->socket;
    line->sourceAnchor.alignments[0] = Core::Alignment::Center;
    line->sourceAnchor.alignments[1] = Core::Alignment::Center;

    SharedReference<PinNodeView::Pin> targetPin = StaticCast<PinNodeView::Pin>(targetNode->findTarget(connection));
    line->destinationAnchor.view = targetPin->socket;
    line->destinationAnchor.alignments[0] = Core::Alignment::Center;
    line->destinationAnchor.alignments[1] = Core::Alignment::Center;

    return line;
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
