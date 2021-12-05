#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "GraphEditor.gen.h"
#include "Foundation"
#include "NodeSearchView.gen.h"

#include "Foundation"
#include "Experimental"
#include "PropertyDetailsView.gen.h"
#include "EventDetailsView.gen.h"
#include "FunctionDetailsView.gen.h"
#include "EmbeddedObjectFieldEditor.gen.h"

//CLASSGEN END REGION
#include "EmbeddedObjectFieldEditor.gen.h"
#include "NodeSearchView.gen.h"
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ScriptEditor : public LegacyClassGen::GraphEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ScriptEditor This;
    typedef LegacyClassGen::GraphEditor Super;
    typedef void Interfaces;
protected:
    SharedReference<UI::NodeSearchView> NodeSearchView;
public:
    ScriptEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::NodeSearchView> getNodeSearchView() const;
    void setNodeSearchView(SharedReference<UI::NodeSearchView> const &NodeSearchView);
    void setNodeSearchView(SharedReference<UI::NodeSearchView> &&NodeSearchView);
    SharedReference<UI::Label> currentGraphLabel;
    SharedReference<UI::TextButton> mainGraphButton;
    SharedReference<UI::TextButton> runButton;
    SharedReference<UI::GroupView> detailsView;
    SharedReference<UI::GroupHeader> detailsHeader;
    SharedReference<LegacyClassGen::PropertyDetailsView> propertyDetails;
    SharedReference<LegacyClassGen::EventDetailsView> eventDetails;
    SharedReference<LegacyClassGen::FunctionDetailsView> functionDetails;
    SharedReference<UI::GroupHeader> valuesHeader;
    SharedReference<LegacyClassGen::EmbeddedObjectFieldEditor> propertiesTree;
    void onHierarchyCreate();
//CLASSGEN END REGION

    void setMainGraph()
    {
        setGraph(String());
    }

    void setGraph(const String &name)
    {
        ApplyCurrentGraph();

        CurrentGraph.first = name;
        CurrentGraph.second = Graphs[name];

        currentGraphLabel->setText("Current Graph: " + name);
        currentGraphLabel->setExpanded(bool(CurrentGraph.first));
        mainGraphButton->setExpanded(bool(CurrentGraph.first));
        resetNodeViews();
    }

    void onLinkPins(
        const SharedReference<UI::PinNodeView> &sourceNodeView, const SharedReference<UI::PinNodeView::Pin> &sourcePinView,
        const SharedReference<UI::PinNodeView> &targetNodeView, const SharedReference<UI::PinNodeView::Pin> &targetPinView
    ) override;


    SharedReference<UI::MenuView> createMenu(const AWeakPointer<UI::NodeView> &item)
    {
        SharedReference<UI::MenuView> menuView = CreateShared<UI::MenuView>();
        /*menuView->addAction(MenuAction{ "Add view...", [this, item](TapGestureEvent &event) {

            Node* newItem = new Node{ "NewView" };
            newItem->type = "UI.View";
            newItem->parent = item;

            SharedReference<NodeView> view = createNode(newItem, item->view.data());
            view->setSize(Math::IntegerVector{ 100, 100 });
            newItem->view = view;

            newItem->updateInstance();

            item->items.append(newItem);
            if (item->treeitem)
            {
                if (!item->treeitem->getExpandable())
                {
                    item->treeitem->setExpandable(true);
                }
                if (item->isExpanded)
                {
                    outliner->notifyUpdateChildren(item);
                }
            }
        } });*/
        menuView->addAction(UI::MenuAction{ "Disconnect", [this, item](UI::TapGestureEvent &event) {
            size_t i = graphView->getNodeIndexForItemView(*item);
            LegacyClassGen::NodeData &data = CurrentGraph.second.Nodes[i];

            for (size_t cIndex = 0; cIndex < connections.size(); ++cIndex)
            {
                const SharedReference<UI::Line> &c = connections[cIndex];
                for (const UI::NodeView::ConnectionInfo &ci : item->connections)
                {
                    if (ci.view == c)
                    {
                        ALogMessage("", "Delete connection %s at %d", ci.data.Target, cIndex);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --cIndex;
                        break;
                    }
                }
            }
            item->connections.clear();
            data.Connections.clear();

            size_t j = 0;
            for (const SharedReference<UI::NodeView> &n : nodes)
            {
                for (size_t ni = 0; ni < n->connections.size(); ++ni)
                {
                    const UI::NodeView::ConnectionInfo &ci = n->connections[ni];
                    if (ci.data.Target.split('/')[0] == data.Identifier)
                    {
                        size_t cIndex = graphView->getConnectionIndexForItemView(*ci.view);
                        ALogMessage("", "Delete connection %s from %s at %d", ci.data.Target, n->getIdentifier(), cIndex);
                        CurrentGraph.second.Nodes[j].Connections.erase(CurrentGraph.second.Nodes[j].Connections.begin() + ni);
                        n->connections.erase(n->connections.begin() + ni);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --ni;
                    }
                }
                ++j;
            }
        } });

        menuView->addAction(UI::MenuAction{ "Remove", [this, item](UI::TapGestureEvent &event) {

            size_t i = graphView->getNodeIndexForItemView(*item);
            const LegacyClassGen::NodeData &data = CurrentGraph.second.Nodes[i];

            for (size_t cIndex = 0; cIndex < connections.size(); ++cIndex)
            {
                const SharedReference<UI::Line> &c = connections[cIndex];
                for (const UI::NodeView::ConnectionInfo &ci : item->connections)
                {
                    if (ci.view == c)
                    {
                        ALogMessage("", "Delete connection %s -> %s at %d", item->getIdentifier(), ci.data.Target, cIndex);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --cIndex;
                        break;
                    }
                }
            }

            size_t j = 0;
            for (const SharedReference<UI::NodeView> &n : nodes)
            {
                for (size_t ni = 0; ni < n->connections.size(); ++ni)
                {
                    const UI::NodeView::ConnectionInfo &ci = n->connections[ni];
                    if (ci.data.Target.split('/')[0] == data.Identifier)
                    {
                        size_t cIndex = graphView->getConnectionIndexForItemView(*ci.view);
                        ALogMessage("", "Delete connection %s -> %s at %d", n->getIdentifier(), ci.data.Target, cIndex);
                        auto &anotherNode = CurrentGraph.second.Nodes[j];
                        if (ci.data.Reversed)
                        {
                            auto it = std::find_if(anotherNode.Connections.begin(), anotherNode.Connections.end(), [&](auto &c) {
                                return c.Target == ci.data.Target;
                            });

                            anotherNode.Connections.erase(it);
                        }
                        else
                        {
                            auto it = std::find_if(anotherNode.ExecutionBranches.begin(), anotherNode.ExecutionBranches.end(), [&](auto &c) {
                                return c.Target == ci.data.Target;
                            });

                            anotherNode.ExecutionBranches.erase(it);
                        }
                        n->connections.erase(n->connections.begin() + ni);
                        connections.erase(connections.begin() + cIndex);
                        graphView->notifyRemoveConnections(cIndex);
                        --ni;
                    }
                }
                ++j;
            }

            ALogMessage("", "Delete %s at %d", data.Identifier, i);
            CurrentGraph.second.Nodes.erase(CurrentGraph.second.Nodes.begin() + i);
            nodes.erase(nodes.begin() + i);
            graphView->notifyRemoveNodes(i);
        } });
        /*menuView->addAction(MenuAction{ "Clear", [this, item](TapGestureEvent &event) {
            for (auto &child : item->items)
            {
                child->view->removeFromParent();
            }
            item->items.clear();
            if (item->treeitem)
            {
                item->treeitem->setExpandable(false);
                outliner->notifyUpdateChildren(item);
            }
        } });*/

        return menuView;
    }

    SharedReference<UI::NodeView> createNode(const LegacyClassGen::NodeData &node) override;
    void onLoad(ALoadEvent &event);
    struct Item {
        std::function<SharedReference<UI::View>()> CreateGroup;
        std::function<SharedReference<UI::View>(size_t index)> CreateItem;
        size_t Size = 0;
    };
    StaticArray<Item, 4> Items;
    Array<LegacyClassGen::PropertyInfo> Properties;
    Array<LegacyClassGen::FunctionInfo> Functions;
    Array<LegacyClassGen::EventInfo> Events;

    SharedReference<LegacyClassGen::BaseCGType> Type;
    
    void showDetailsPage(size_t index);
    void reloadSymbols();
    void addNode(const String &text);
    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override;
    void onSave(AJSONObject &data) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
