#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include "TransitionView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationStateView : public UI::NamedNodeView
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationStateView This;
    typedef UI::NamedNodeView Super;
    typedef void Interfaces;
public:
    ApplicationStateView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void onHierarchyCreate();
//CLASSGEN END REGION
    ADelegate<void(ApplicationStateView &state, size_t index)> objectSelected;

    using Super = UI::NamedNodeView;

    SharedReference<UI::ListView> listView = CreateShared<UI::ListView>();

    AJSONArray objects;

    void onLoad(ALoadEvent &event) override
    {
        Super::onLoad(event);
        //listView->setAdapter(this);
        //listView->setSizePolicy(UI::SizePolicy::Expanded);
        //addView(listView);
    }

    AJSONObject getData() const
    {
        AJSONObject data;
        //data.insert("Objects", objects);
        return data;
    }

    void setData(const AJSONObject &data)
    {
        //data.read("Objects", objects);
        //listView->notifyUpdateAllItems();
    }

    void onUpdate(AUpdateEvent &event)
    {
        Super::onUpdate(event);
        //listView->removeFromParent();
        //addView(listView);
    }

    SharedReference<UI::Line> createConnection() override
    {
        return Create<TransitionView>();
    }

    SharedReference<UI::Line> connect(const SharedReference<UI::NodeView> &sourceNode, const SharedReference<UI::NodeView> &destinationNode, const UI::Connection &connection) override
    {
        SharedReference<TransitionView> line = Super::connect(sourceNode, destinationNode, connection).as<TransitionView>();
        line->setImage(::Line);
        line->sourceAnchor.alignments[0] = Core::Alignment::Center;
        line->sourceAnchor.alignments[1] = Core::Alignment::Center;
        line->sourceAnchor.view = sourceNode;
        line->destinationAnchor.alignments[0] = Core::Alignment::Center;
        line->destinationAnchor.alignments[1] = Core::Alignment::Center;
        line->destinationAnchor.view = destinationNode;

        line->connection = connection;
        line->data.deserialize(connection.Data);

        return line;
    }

    //UI::SizeType getCountItems(const AObject &sender) const override { return objects.size(); }
    //SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override
    //{
    //    SharedReference<UI::Label> label = CreateShared<UI::Label>();
    //    String name;
    //    if (objects[index].asObject().read("Name", name))
    //    {
    //        label->setText(name);
    //    }
    //    else
    //    {
    //        label->setText("Undefined");
    //    }
    //    label->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped);
    //    return label;
    //}
    //
    //void onItemSelected(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType index) override
    //{
    //    //objectSelected(*this, index);
    //}
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
