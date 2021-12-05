#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Foundation"
#include "ExperimentalDebug"
#include "ClassGenExtensions"

//CLASSGEN END REGION
#include "GraphEditor.gen.h"
#include "ObjectEditor.gen.h"

#include "ApplicationObjectView.gen.h"
#include "TransitionView.gen.h"
#include "ApplicationStateView.gen.h"
#include "ApplicationViewStateView.gen.h"
#include "ApplicationWindowStateView.gen.h"
#include "ApplicationStateProperties.gen.h"
#include "ApplicationFlowProperties.gen.h"
#include "ApplicationTransitionProperties.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ApplicationFlowEditor : public LegacyClassGen::GraphEditor
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ApplicationFlowEditor This;
    typedef LegacyClassGen::GraphEditor Super;
    typedef void Interfaces;
public:
    ApplicationFlowEditor();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::PageView> sidebarPages;
    SharedReference<LegacyClassGen::ApplicationFlowProperties> flowProperties;
    SharedReference<LegacyClassGen::ApplicationStateProperties> stateProperties;
    SharedReference<LegacyClassGen::ApplicationTransitionProperties> transitionProperties;
    SharedReference<LegacyClassGen::ObjectEditor> objectEditor;
    void onHierarchyCreate();
//CLASSGEN END REGION
public:
    AJSONObject data;

    /*static APathInfo getNextPath(const APath &directory, const String &name)
    {
        APathInfo pathInfo(directory + name);
        if (!pathInfo.isExists())
        {
            return pathInfo;
        }

        for (size_t i = 2; i < std::numeric_limits<size_t>::max(); ++i)
        {
            APathInfo pathInfo(directory + (name + String::number(i)));
            if (!pathInfo.isExists())
            {
                return pathInfo;
            }
        }

        return directory + (name + String::number(std::numeric_limits<size_t>::max()));
    };*/

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        
        singleSelection->predicate = [this](const SharedReference<UI::View> &view) {
            return view.cast<TransitionView>() || nodes.find_first_of(view.as<UI::NodeView>()) != UI::InvalidIndex;
        };

        singleSelection->selectionUpdated = [this](const SharedReference<UI::View> &view, AWindowTouchDownEvent &event) {
            updateSelection({ view });
            if (view.cast<TransitionView>())
            {
                event.accept();
            }
        };

        flowProperties->entryPointChanged = [this](const String &entryPoint) {
            data.insert("EntryPoint", entryPoint);
        };

        flowProperties->entryPointTypeChanged = [this](const String &entryPointType) {
            data.insert("EntryPointType", entryPointType);
        };
        flowProperties->setSizePolicy(UI::SizePolicy::Expanded);

        stateProperties->identifierChanged = [this](const String &identifier) {
            SharedReference<UI::NamedNodeView> selectedNode = getSelectedNodes()[0].as<UI::NamedNodeView>();
            selectedNode->identifier = identifier;
            selectedNode->title->setText(identifier);
            UI::SizeType index = graphView->getNodeIndexForItemView(*selectedNode);
            CurrentGraph.second.Nodes[index].Identifier = identifier;
        };
        stateProperties->setSizePolicy(UI::SizePolicy::Expanded);
        stateProperties->onChanged = [this]() {
            ALogMessage("", "Object changed");
        };

        transitionProperties->setSizePolicy(UI::SizePolicy::Expanded);

        objectEditor->setSizePolicy(UI::SizePolicy::Expanded);
        objectEditor->onChanged = [this]() {
            ALogMessage("", "Object changed");
        };

        auto data = getData();
        data.insert(data.begin(), {});
        setData(data);

        SharedReference<UI::MenuView> menuView = CreateShared<UI::MenuView>();
        menuView->addAction(UI::MenuAction{ "Add state...", [this](UI::TapGestureEvent &event) {
            LegacyClassGen::NodeData data;
            data.Identifier = getNextName("State", [&](const String &name) {
                return std::find_if(CurrentGraph.second.Nodes.begin(), CurrentGraph.second.Nodes.end(), [&](const LegacyClassGen::NodeData &value) { return name == value.Identifier; }) == CurrentGraph.second.Nodes.end();
            });
            data.Type = "State";
            nodes.append(createNode(data));
            CurrentGraph.second.Nodes.append(std::move(data));
            graphView->notifyInsertNodes(CurrentGraph.second.Nodes.size() - 1);
        } });

        menuView->addAction(UI::MenuAction{ "Add object...", [this](UI::TapGestureEvent &event) {
            LegacyClassGen::NodeData data;
            data.Identifier = getNextName("Object", [&](const String &name) {
                return std::find_if(CurrentGraph.second.Nodes.begin(), CurrentGraph.second.Nodes.end(), [&](const LegacyClassGen::NodeData &value) { return name == value.Identifier; }) == CurrentGraph.second.Nodes.end();
            });
            data.Type = "Object";
            nodes.append(createNode(data));
            CurrentGraph.second.Nodes.append(std::move(data));
            graphView->notifyInsertNodes(CurrentGraph.second.Nodes.size() - 1);
        } });
        AttachMenuToView(graphView, menuView);
    }
    void updateSelection(const Array<SharedReference<UI::View>> &views) override
    {
        if (groupMovement->views.size() == 1)
        {
            size_t index = graphView->getNodeIndexForItemView(*groupMovement->views[0]);
            if (SharedReference<ApplicationStateView> view = groupMovement->views[0].cast<ApplicationStateView>())
            {
                stateProperties->onSave(CurrentGraph.second.Nodes[index].Data);
            }
            else if (SharedReference<ApplicationObjectView> view = groupMovement->views[0].cast<ApplicationObjectView>())
            {
                objectEditor->onSave(CurrentGraph.second.Nodes[index].Data);
            }
        }

        Super::updateSelection(views);

        if (views.size() == 1)
        {
            if (auto nodeView = views[0].cast<UI::NodeView>())
            {
                size_t index = graphView->getNodeIndexForItemView(*nodeView);
                UIApplication::getOperationDispatcher().addDelegate([this, index]() {
                    if (CurrentGraph.second.Nodes[index].Type == "State")
                    {
                        stateProperties->setData(CurrentGraph.second.Nodes[index]);
                        sidebarPages->setCurrentPage(1); //StateProperties
                    }
                    else
                    {
                        objectEditor->onLoad(CurrentGraph.second.Nodes[index].Data);
                        sidebarPages->setCurrentPage(3); //ObjectEditor
                    }
                    return AError();
                }, true);
            }
            else if (SharedReference<TransitionView> transitionView = views[0].cast<TransitionView>())
            {
                sidebarPages->setCurrentPage(2); //TransitionProperties
                transitionProperties->transition = transitionView;
                transitionProperties->notifyUpdateAllItems();
            }
        }
        else if (views.size() == 0)
        {
            UIApplication::getOperationDispatcher().addDelegate([this]() {
                sidebarPages->setCurrentPage(0); //FlowProperties
                return AError();
            }, true);
        }
        else
        {
            sidebarPages->setCurrentPage(0); //FlowProperties
        }
    }

    SharedReference<UI::NodeView> createNode(const LegacyClassGen::NodeData &data) override
    {
        SharedReference<UI::MenuView> menuView = CreateShared<UI::MenuView>();
        SharedReference<UI::NamedNodeView> nodeView;
        if (data.Type == "State")
        {
            SharedReference<ApplicationStateView> stateView = Create<ApplicationStateView>();
            stateView->setData(data.Data);
            stateView->objectSelected = [this](ApplicationStateView &state, size_t index) {
                AJSONObject &data = state.objects[index].asObject();
                objectEditor->onLoad(data);
                sidebarPages->setCurrentPage(3); //ObjectEditor
            };

            nodeView = stateView;
            AWeakPointer<ApplicationStateView> stateViewHandle = stateView;
            menuView->addAction(UI::MenuAction{ "Add object", [this, stateViewHandle](UI::TapGestureEvent &event) {
                stateViewHandle->objects.append(getNextName("NewObject", [&](const String &value)
                {
                    return std::find_if(
                        stateViewHandle->objects.begin(),
                        stateViewHandle->objects.end(),
                        [&](auto &&data) { return data.asObject().at("Name").asString() == value; }
                    ) == stateViewHandle->objects.end();
                }));
                stateViewHandle->listView->notifyUpdateAllItems();
                stateViewHandle->setSize(stateViewHandle->getContentSize());
            } });
            /*menuView->addAction(MenuAction{ "Remove object", [this, nodeViewHandle](TapGestureEvent &event) {
                nodes.remove(nodeViewHandle.shared());
                graphView->notifyUpdateAllItems();
            } });*/
        }
        else
        {
            SharedReference<ApplicationObjectView> objectView = Create<ApplicationObjectView>();
            nodeView = objectView;
        }

        nodeView->setSizePolicy(UI::SizePolicy::ContentWrapped);
        nodeView->title->setText(data.Identifier);
        nodeView->setSize(nodeView->getContentSize());

        AWeakPointer<UI::NodeView> nodeViewHandle = nodeView;
        menuView->addAction(UI::MenuAction{ "Remove", [this, nodeViewHandle](UI::TapGestureEvent &event) {
            nodes.remove(nodeViewHandle.shared());
            graphView->notifyUpdateAllItems();
        } });
        AttachMenuToView(nodeView, menuView);

        return nodeView;
    }

    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override
    {
        data.read("Properties", this->data);
        Super::onLoad(data, type);
    }

    void onSave(AJSONObject &data) override
    {
        size_t connectionIndex = 0;
        for (auto &connection : connections)
        {
            SharedReference<TransitionView> transition = connection.as<TransitionView>();
            size_t i = nodes.find_first_of(transition->sourceAnchor.view.as<UI::NodeView>());
            LegacyClassGen::NodeData &data = CurrentGraph.second.Nodes[i];
            auto it = std::find_if(data.Connections.begin(), data.Connections.end(), [&](UI::Connection &v) {
                return v.Source == transition->connection.Source && v.Target == transition->connection.Target;
            });
            if (it != data.Connections.end())
            {
                transition->data.serialize(it->Data);
                
            }
        }

        Super::onSave(data);
        data.insert("Properties", this->data);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
