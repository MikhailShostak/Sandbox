#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"
#include "Includes/Editor.gen.h"
#include "Foundation"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class GraphEditor : public UI::SplitView, public LegacyClassGen::Editor, public UI::GraphAdapter
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GraphEditor This;
    typedef UI::SplitView Super;
    typedef std::tuple<LegacyClassGen::Editor, UI::GraphAdapter> Interfaces;
protected:
    UnorderedDictionary<String, LegacyClassGen::GraphData> Graphs;
APair<String, LegacyClassGen::GraphData> CurrentGraph;
public:
    GraphEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    UnorderedDictionary<String, LegacyClassGen::GraphData> getGraphs() const;
    void setGraphs(UnorderedDictionary<String, LegacyClassGen::GraphData> const &Graphs);
    void setGraphs(UnorderedDictionary<String, LegacyClassGen::GraphData> &&Graphs);
    APair<String, LegacyClassGen::GraphData> getCurrentGraph() const;
    void setCurrentGraph(APair<String, LegacyClassGen::GraphData> const &CurrentGraph);
    void setCurrentGraph(APair<String, LegacyClassGen::GraphData> &&CurrentGraph);
    SharedReference<UI::GridView> gridView;
    void onHierarchyCreate();
//CLASSGEN END REGION
protected:
    Array<SharedReference<UI::NodeView>> nodes;
    Array<SharedReference<UI::Line>> connections;

    Array<LegacyClassGen::NodeData> nodesData;

    SharedReference<UI::SignleSelection> singleSelection = CreateShared<UI::SignleSelection>();
    SharedReference<UI::GroupMovement> groupMovement = CreateShared<UI::GroupMovement>();
    SharedReference<UI::Linking> linking = CreateShared<UI::Linking>();
public:
    using Super::onLoad;

    void ApplyCurrentGraph()
    {
        updatePositionsInGraph(CurrentGraph.second);
        Graphs[CurrentGraph.first] = CurrentGraph.second;
    }

    SharedReference<UI::GraphView> graphView;

    SharedReference<UI::NodeView> findNode(const String &identifier) const
    {
        auto it = std::find_if(nodes.begin(), nodes.end(), [&](const auto &node) { return node->getIdentifier() == identifier; });
        return it != nodes.end() ? *it : nullptr;
    }

    const Array<SharedReference<View>> &getSelectedNodes() const
    {
        return groupMovement->views;
    }

    virtual void updateSelection(const Array<SharedReference<View>> &views)
    {
        for (auto &node : nodes)
        {
            node->setSelected(false);
        }
        for (auto &view : views)
        {
            if (const SharedReference<UI::NodeView> node = DynamicCast<UI::NodeView>(view))
            {
                node->setSelected(true);
            }
        }
        groupMovement->views = views;
    };

    virtual SharedReference<UI::NodeView> createNode(const LegacyClassGen::NodeData &node) = 0;

    bool AcceptNode(const SharedReference<View> &view) const
    {
        auto node = DynamicCast<UI::NodeView>(view);
        if (!node)
        {
            return false;
        }

        return ArrayUtils::FindFirst(nodes, node) != UI::InvalidIndex;
    };

    bool AcceptPin(const SharedReference<View> &view) const
    {
        auto pin = DynamicCast<UI::PinNodeView::Pin>(view);
        if (!pin)
        {
            return false;
        }

        return true;//nodes.find_first_of(view.as<UI::NodeView>()) != UI::InvalidIndex;
    };

    virtual bool canLinkSource(const SharedReference<View> &view) const
    {
        return AcceptNode(view) || AcceptPin(view);
    }

    virtual bool canLinkTarget(const SharedReference<View> &view) const
    {
        return AcceptNode(view) || AcceptPin(view);
    }

    virtual void onLinkNodes(const SharedReference<View> &sourceView, const SharedReference<View> &targetView)
    {
        ALogMessage("", "Connect Node");
    }

    virtual void onLinkPins(
        const SharedReference<UI::PinNodeView> &sourceNodeView, const SharedReference<UI::PinNodeView::Pin> &sourcePinView,
        const SharedReference<UI::PinNodeView> &targetNodeView, const SharedReference<UI::PinNodeView::Pin> &targetPinView
    )
    {
        ALogMessage("", "Source Node %s", sourceNodeView);
        ALogMessage("", "Target Node %s", targetNodeView);
        ALogMessage("", "Connect Pin");
    }

    virtual void onLink(const SharedReference<View> &sourceView, const SharedReference<View> &targetView)
    {
        if (AcceptNode(sourceView) && AcceptNode(targetView))
        {
            onLinkNodes(sourceView, targetView);
        }
        else if(AcceptPin(sourceView) && AcceptPin(targetView))
        {
            SharedReference<UI::PinNodeView::Pin> sourcePin = StaticCast<UI::PinNodeView::Pin>(sourceView);
            SharedReference<UI::PinNodeView::Pin> targetPin = StaticCast<UI::PinNodeView::Pin>(targetView);
            if (sourcePin->getConnectionSource() == targetPin->getConnectionSource() || sourcePin->getType() == targetPin->getType())
            {
                ALogMessage("", "Pins cannot be connected.");
                return;
            };

            auto isInHirerachy = [this](const auto &container, const auto &item) {
                UI::View *parent = item->getParent();
                while (parent)
                {
                    if (parent == container)
                    {
                        return true;
                    }
                    parent = parent->getParent();
                }
                return false;
            };

            auto getSharedReference = [](UI::PinNodeView *view) -> SharedReference<UI::PinNodeView> {
                auto &views = view->getParent()->getViews();
                return StaticCast<UI::PinNodeView>(*ranges::find_if(views, [&](auto &v) { return v.get() == view; }));
            };

            auto findPinNodeViewParent = [this, &getSharedReference](const auto &item) -> SharedReference<UI::PinNodeView> {
                UI::View *parent = item->getParent();
                UI::PinNodeView *view = nullptr;
                while (parent)
                {
                    if (view = DynamicCast<UI::PinNodeView>(parent))
                    {
                        return getSharedReference(view);
                    }
                    parent = parent->getParent();
                }
                return getSharedReference(view);
            };

            if (isInHirerachy(this, sourceView) && isInHirerachy(this, targetView))
            {
                if (sourcePin->getConnectionSource())
                {
                    onLinkPins(findPinNodeViewParent(sourceView), sourcePin, findPinNodeViewParent(targetView), targetPin);
                }
                else
                {
                    onLinkPins(findPinNodeViewParent(targetView), targetPin, findPinNodeViewParent(sourceView), sourcePin);
                }
            }
        }
    }

    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override
    {
        graphView = StaticCast<UI::GraphView>(gridView->root);

        auto checkNode = [this](const SharedReference<View> &v) { return AcceptNode(v); };

        linking->line->backgroundView->setImage(::Line);
        linking->sourcePredicate = [this](const SharedReference<View> &v) { return canLinkSource(v); };
        linking->targetPredicate = [this](const SharedReference<View> &v) { return canLinkTarget(v); };
        linking->linked = [this](const SharedReference<View> &sourceView, const SharedReference<View> &targetView) {
            onLink(sourceView, targetView);
            /*SharedReference<UI::NodeView> sourceNode = sourceView.as<UI::NodeView>();
            SharedReference<UI::NodeView> targetNode = targetView.as<UI::NodeView>();
            if (sourceNode->connections.find_first_of(targetNode->identifier) != InvalidIndex)
            {
                return;
            }

            connections.append(sourceNode->connect(sourceNode, targetNode, {}, {}));
            graphView->notifyInsertConnections(connections.size() - 1);*/
        };
        linking->setTouchModifier(ATouchModifier::ControlKey);
        linking->useAnyModifier = false;

        singleSelection->predicate = checkNode;
        singleSelection->selectionUpdated = [this](const SharedReference<View> &view, AWindowTouchDownEvent &event) {
            updateSelection({ view });
        };

        auto singleMovement = CreateShared<UI::SingleMovement>();
        singleMovement->predicate = checkNode;
        singleMovement->gridSize = 10;

        groupMovement->gridSize = 10;

        auto multipleSelection = CreateShared<UI::RubberBandSelection>();
        //HACK start
        multipleSelection->requestContentView = [this]() -> View &
        {
            if (!nodes.empty())
            {
                return *nodes[0]->getParent();
            }
            return *graphView;
        };
        //HACK end
        multipleSelection->predicate = checkNode;
        multipleSelection->selectionUpdated = ADelegate<void(const Array<SharedReference<View>> &)>(this, &GraphEditor::updateSelection);

        auto swipe = CreateShared<UI::SwipeGestureRecognizer>();
        swipe->setTouchID(ATouchID::MiddleMouseButton);

        graphView->addGestureRecognizer(swipe);
        graphView->contentView->addGestureRecognizer(multipleSelection);
        graphView->contentView->addGestureRecognizer(singleMovement);
        graphView->contentView->addGestureRecognizer(singleSelection);
        graphView->contentView->addGestureRecognizer(groupMovement);
        graphView->contentView->addGestureRecognizer(linking);
        graphView->setProxyAdapter(this);

        /*nodesData.clear();
        AJSONValue d;
        data.read("Nodes", d);
        fromJSONValue(d, nodesData);*/

        Graphs.clear();
        AJSONValue d;
        data.read("Graphs", d);
        fromJSONValue(d, Graphs);

        if (Graphs.find("") != Graphs.end())
        {
            CurrentGraph.second = Graphs[""];
        }

        resetNodeViews();
    }

    void updatePositionsInGraph(LegacyClassGen::GraphData &graph)
    {
        size_t i = 0;
        for (auto it = nodes.begin(); it != nodes.end(); ++it, ++i)
        {
            LegacyClassGen::NodeData &nodeData = graph.Nodes[i];
            const SharedReference<UI::NodeView> &node = *it;
            nodeData.Position = node->getPosition();
        }
    }

    void onSave(AJSONObject &data) override
    {
        ApplyCurrentGraph();
        data.insert("Graphs", toJSONValue(Graphs));
    }

    virtual void resetNodeViews()
    {
        nodes.clear();
        connections.clear();

        if (std::find_if(
            CurrentGraph.second.Nodes.begin(),
            CurrentGraph.second.Nodes.end(),
            [](auto &i) { return i.Identifier == "EntryPoint"; }
        ) == CurrentGraph.second.Nodes.end())
        {
            LegacyClassGen::NodeData node;
            node.Identifier = "EntryPoint";

            /*UI::Connection connection;
            connection.Target = "ReturnPoint";
            node.ExecutionBranches.append(connection);*/

            CurrentGraph.second.Nodes.insert(CurrentGraph.second.Nodes.begin(), node);
        }

        if (ranges::find_if(
            CurrentGraph.second.Nodes,
            [](auto &i) { return i.Identifier == "ReturnPoint"; }
        ) == CurrentGraph.second.Nodes.end())
        {
            LegacyClassGen::NodeData node;
            node.Identifier = "ReturnPoint";
            node.Position = Math::Vector{ 100, 0 };

            CurrentGraph.second.Nodes.insert(CurrentGraph.second.Nodes.begin(), node);
        }

        for (const LegacyClassGen::NodeData &nodeData : CurrentGraph.second.Nodes)
        {
            const auto &nodeView = createNode(nodeData);
            nodeView->setName(nodeData.Identifier);
            nodeView->setPosition(nodeData.Position);
            nodeView->identifier = nodeData.Identifier;
            nodes.push_back(nodeView);
        }

        size_t i = 0;
        for (auto it = nodes.begin(); it != nodes.end(); ++it, ++i)
        {
            LegacyClassGen::NodeData &nodeData = CurrentGraph.second.Nodes[i];

            const SharedReference<UI::NodeView> &node = *it;

            connections.reserve(nodeData.Connections.size());
            for (const UI::Connection &executionBranch : nodeData.ExecutionBranches)
            {
                auto nodeIt = ranges::find_if(nodes, [&](const auto &node) { return node->getIdentifier() == executionBranch.Target; });
                if (nodeIt == nodes.end())
                {
                    //TODO: node is not found. suggest replace connection
                    continue;
                }

                const SharedReference<UI::NodeView> &targetNode = *nodeIt;
                connections.push_back(node->connect(node, targetNode, executionBranch));
            }
            for (UI::Connection &connectionData : nodeData.Connections)
            {
                connectionData.Reversed = true;

                Array<String> targetPath = Str::Split(connectionData.Target, "/");
                if (targetPath.empty())
                {
                    continue;
                }

                auto nodeIt = ranges::find_if(nodes, [&](const auto &node) { return node->getIdentifier() == targetPath[0]; });
                if (nodeIt == nodes.end())
                {
                    //TODO: node is not found. suggest replace connection
                    continue;
                }

                Array<String> sourcePath = Str::Split(connectionData.Source, "/");

                const SharedReference<UI::NodeView> &targetNode = *nodeIt;
                connections.push_back(node->connect(node, targetNode, connectionData));
            }
        }

        graphView->notifyUpdateAllItems();
    }

    UI::SizeType getCountNodes(const AObject &sender) const override { return nodes.size(); }

    UI::SizeType getCountConnections(const AObject &sender) const override { return connections.size(); }

    SharedReference<View> provideViewForNode(const AObject &sender, UI::SizeType index) override
    {
        return nodes[index];
    }

    SharedReference<View> provideViewForConnection(const AObject &sender, UI::SizeType index) override
    {
        return connections[index];
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
