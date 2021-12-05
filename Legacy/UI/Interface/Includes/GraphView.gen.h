#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ItemView.gen.h"

//CLASSGEN END REGION
#include "GraphProxy.gen.h"
/*
#include "Includes/ItemView.gen.h"
#include "UI/GestureRecognizers/UILinkingGestureRecognizer.h"
#include "Core/AWindow.h"
*/
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

/*
class GraphView : public ItemView<ItemAdapter>
{
CLASSGEN_GENERATED_REGION_OBJECT
CLASSGEN_END_REGION
public:

};

class GraphNode;

class GraphNodesLinkEvent : public AEvent
{
public:
    using AEvent::AEvent;
    GraphNode *sourceNode = nullptr;
    GraphNode *targetNode = nullptr;
    Math::IntegerVector point;
};

class GraphNode : public View, public LinkingSourceGestureAdapter, public LinkingTargetGestureAdapter
{
protected:
    SharedReference<BorderImageView> backgroundView = new BorderImageView();
    SharedReference<BorderImageView> highlightingView = new BorderImageView();
    SharedReference<Label> title = new Label();
public:

    const String &getName() const { return title->getText(); }
    void setName(const String &name) { title->setText(name); }

    GraphNode()
    {
        addGestureRecognizer(new LinkingGestureRecognizer(ATouchModifier::ControlKey));

        backgroundView->setSizePolicy(SizePolicy::Expanded);
        addView(backgroundView);
        highlightingView->setSizePolicy(SizePolicy::Expanded);
        highlightingView->setVisible(false);
        addView(highlightingView);
        addView(title);

        eventChannel.registerDelegate<TouchDownGestureEvent>([this](TouchDownGestureEvent &event) {
            if (event.isInside())
            {
                getOwner()->getWindow()->setFocus(*this);
            }
        });

        SharedReference<RelativeLayout> relativeLayout = new RelativeLayout();
        setLayout(relativeLayout);

        relativeLayout->addConstraints(*backgroundView, *this, 0);
        relativeLayout->addConstraints(*highlightingView, *this, 0);
        relativeLayout->addConstraints(*title, *this, 4);

        ARegisterEventCallback(onFocusIn);
        ARegisterEventCallback(onFocusOut);

        ApplyStyle(*this);
    }

    ~GraphNode()
    {
        AUnregisterEventCallback(onFocusOut);
        AUnregisterEventCallback(onFocusIn);
    }

    const UIOffsets &getBorder() const
    {
        return backgroundView->getBorder();
    }

    void setBorder(const UIOffsets &border)
    {
        backgroundView->setBorder(border);
        highlightingView->setBorder(border);
    }

    const SharedReference<Graphics::Texture> &getImage() const
    {
        return backgroundView->getImage();
    }

    void setImage(const SharedReference<Graphics::Texture> &image)
    {
        backgroundView->setImage(image);
    }

    const SharedReference<Graphics::Texture> &getHighlightingImage() const
    {
        return highlightingView->getImage();
    }

    void setHighlightingImage(const SharedReference<Graphics::Texture> &image)
    {
        highlightingView->setImage(image);
    }

    bool canBeLinkedAsTarget(const View &sourceView, const AVariant &sourceData) override
    {
        const GraphNode *node = dynamic_cast<const GraphNode *>(&sourceView);
        if (!node)
        {
            return false;
        }

        return getParent() == sourceView.getParent();
    }

    void onTargetLink(View &sourceView, const Math::IntegerVector &point, const AVariant &sourceData) override
    {
        GraphNodesLinkEvent event(*this);
        event.sourceNode = static_cast<GraphNode*>(&sourceView);
        event.targetNode = this;
        event.point = point;
        eventChannel.sendEvent(event);
    }

    void onLinkingHighlight() override
    {
        AColor color = backgroundView->getColor();
        backgroundView->setColor(AColor(color.red() + 0.1f, color.green() + 0.1f, color.blue() + 0.1f, color.alpha()));
    }

    void onLinkingUnhighlight() override
    {
        AColor color = backgroundView->getColor();
        backgroundView->setColor(AColor(color.red() - 0.1f, color.green() - 0.1f, color.blue() - 0.1f, color.alpha()));
    }
protected:

    virtual void onFocusIn(AFocusInEvent &event)
    {
        highlightingView->show();
    }

    virtual void onFocusOut(AFocusOutEvent &event)
    {
        highlightingView->hide();
    }
};*/

//CLASSGEN GENERATED REGION: ClassHeader
class GraphView : public UI::ItemView<ItemAdapter>
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GraphView This;
    typedef UI::ItemView<ItemAdapter> Super;
    typedef void Interfaces;
public:
    GraphView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    GraphProxy proxy{ *this };
public:
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        highlightingView->setExpanded(false);
        //setData({ OverlayData{ {}, UI::Alignment::Center, UI::Alignment::Center, }, OverlayData{ {}, UI::Alignment::Center, UI::Alignment::Center, } });
    }

    GraphAdapter *getProxyAdapter() const { return proxy.getAdapter(); }
    void setProxyAdapter(GraphAdapter *adapter)
    {
        proxy.setAdapter(adapter);
        setAdapter(adapter ? &proxy : nullptr);
    }

    SizeType getConnectionIndexForItemView(const View &view) const
    {
        SizeType index = getIndexForItemView(view);
        if (index != InvalidIndex)
        {
            index = proxy.getConnectionIndex(index);
        }
        return index;
    }

    SizeType getNodeIndexForItemView(const View &view) const
    {
        SizeType index = getIndexForItemView(view);
        if (index != InvalidIndex)
        {
            index = proxy.getNodeIndex(index);
        }
        return index;
    }

    void notifyInsertConnections(SizeType index, SizeType size = 1)
    {
        notifyInsertItems(proxy.getItemIndexFromConnectionIndex(index), size);
    }

    void notifyUpdateConnections(SizeType index, SizeType size = 1)
    {
        notifyUpdateItems(proxy.getItemIndexFromConnectionIndex(index), size);
    }

    void notifyRemoveConnections(SizeType index, SizeType size = 1)
    {
        notifyRemoveItems(proxy.getItemIndexFromConnectionIndex(index), size);
    }

    void notifyInsertNodes(SizeType index, SizeType size = 1)
    {
        notifyInsertItems(proxy.getItemIndexFromNodeIndex(index), size);
    }

    void notifyUpdateNodes(SizeType index, SizeType size = 1)
    {
        notifyUpdateItems(proxy.getItemIndexFromNodeIndex(index), size);
    }

    void notifyRemoveNodes(SizeType index, SizeType size = 1)
    {
        notifyRemoveItems(proxy.getItemIndexFromNodeIndex(index), size);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
