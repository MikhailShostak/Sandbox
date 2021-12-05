//CLASSGEN GENERATED REGION: Includes
#include "ScriptEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Algorithm.h"
#include "Foundation"
#include "Experimental"
#include "Math"
#include "PropertyDetailsView.gen.h"
#include "EventDetailsView.gen.h"
#include "FunctionDetailsView.gen.h"
#include "EmbeddedObjectFieldEditor.gen.h"

//CLASSGEN END REGION
#include <ClassGenLibrary>
#include <range/v3/algorithm.hpp>
#include "FunctionManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

class FunctionNode : public UI::PinNodeView, public UI::PinNodeAdapter
{
public:
    using Super = UI::PinNodeView;

    ADelegate<void(const String &name, const String &type)> onTemplateTypeChanged;
    ADelegate<void(const String &name, const String &value)> onValueChanged;

    LegacyClassGen::FunctionInfo f;

    AJSONObject templateValues;
    AJSONObject values;

    FunctionNode()
    {
        adapter = this;
    }

    bool graphEntryPoint = false;
    bool graphReturnPoint = false;
    bool inverted = false;

    const Array<LegacyClassGen::Parameter> &getNodeInputArguments() const { return inverted ? f.OutputArguments : f.InputArguments; }
    const Array<LegacyClassGen::Parameter> &getNodeOutputArguments() const { return inverted ? f.InputArguments : f.OutputArguments; }

    bool isValid() const { return f.Identifier.size(); }
    bool isEntryPoint() const { return graphEntryPoint; }
    bool isReturnPoint() const { return graphReturnPoint; }
    bool isCallable() const { return !graphEntryPoint && f.Callable; }

    virtual size_t getCountInputPins() const { return f.TemplateParameters.size() + (graphEntryPoint ? 0 : ((isCallable() ? 1 : 0) + getNodeInputArguments().size())); }
    virtual SharedReference<View> getInputPin(size_t index)
    {
        PinNodeView::Pin *pin = Create<PinNodeView::Pin>();
        pin->setType(UI::PinType::Input);
        if (f.Callable)
        {
            if (index == 0)
            {
                return pin;
            }
            index -= 1;
        }

        if (index < f.TemplateParameters.size())
        {
            SharedReference<UI::FlexBox> box = CreateShared<UI::FlexBox>();
            box->setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
            box->setAffectsParentLayout(true);

            SharedReference<UI::Label> label = CreateShared<UI::Label>();
            label->setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
            label->setText(f.TemplateParameters[index]);

            SharedReference<UI::TextField> field = CreateShared<UI::TextField>();
            String v;
            if (templateValues.read(f.TemplateParameters[index], v))
            {
                field->setText(v);
            }
            field->setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
            field->setAffectsParentLayout(true);
            field->eventChannel.registerDelegate([this, label](UI::TextEditFinishedEvent &event) {
                onTemplateTypeChanged(label->getText(), event.getText());
            });

            box->addView(field);
            box->addView(label);
            box->setData({ {}, {} });
            return box;
        }
        index -= f.TemplateParameters.size();

        pin->label->setText(getNodeInputArguments()[index].Name);
        pin->setConnectionSource(true);
        return pin;
    }
    virtual size_t getCountOutputPins() const
    {
        return Math::getMax<size_t>(f.ExecutionBranches.size(), f.Callable ? 1 : 0) + getNodeOutputArguments().size();
    }
    virtual SharedReference<View> getOutputPin(size_t index)
    {
        PinNodeView::Pin *pin = Create<PinNodeView::Pin>();
        pin->setType(UI::PinType::Output);

        //HACK: replace with layout inversion
        pin->socket->removeFromParent();
        pin->addView(pin->socket);
        //HACK

        if(f.Callable && f.ExecutionBranches.size() == 0)
        {
            pin->setConnectionSource(true);
        }
        else if (index < f.ExecutionBranches.size())
        {
            pin->label->setText(f.ExecutionBranches[index]);
            pin->setConnectionSource(true);
        }
        else
        {
            pin->label->setText(getNodeOutputArguments()[index - f.ExecutionBranches.size()].Name);
        }
        return pin;
    }
    virtual SharedReference<View> getContent() { nullptr; }
};

//CLASSGEN GENERATED REGION: ClassImplementation
ScriptEditor::ScriptEditor()
{
    UI::SplitViewLayoutData item_90_0;
    UI::SplitViewLayoutData item_91_1;
    (*this).setData({item_90_0,item_91_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ScriptEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ScriptEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SharedReference<UI::NodeSearchView> ScriptEditor::getNodeSearchView() const
{
    return this->NodeSearchView;
}
void ScriptEditor::setNodeSearchView(SharedReference<UI::NodeSearchView> const &NodeSearchView)
{
    this->NodeSearchView = NodeSearchView;
}
void ScriptEditor::setNodeSearchView(SharedReference<UI::NodeSearchView> &&NodeSearchView)
{
    this->NodeSearchView = std::move(NodeSearchView);
}
void ScriptEditor::onHierarchyCreate()
{
    SharedReference<UI::FlexBox> uIFlexBox = CreateShared<UI::FlexBox>([this](UI::FlexBox *v)
    {
    }
);
    (*uIFlexBox).setName("UIFlexBox");
    {
    }
    (*uIFlexBox).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    UI::FlexBoxData item_57_0;
    UI::FlexBoxData item_58_1;
    UI::FlexBoxData item_59_2;
    UI::FlexBoxData item_60_3;
    UI::FlexBoxData item_61_4;
    UI::FlexBoxData item_62_5;
    UI::FlexBoxData item_63_6;
    UI::FlexBoxData item_64_7;
    UI::FlexBoxData item_65_8;
    UI::FlexBoxData item_66_9;
    (*uIFlexBox).setData({item_57_0,item_58_1,item_59_2,item_60_3,item_61_4,item_62_5,item_63_6,item_64_7,item_65_8,item_66_9,});
    (*uIFlexBox).setDirection(UI::Direction::Vertical);
    (*uIFlexBox).setSpacing(8.000000);
    currentGraphLabel = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*currentGraphLabel).setName("CurrentGraphLabel");
    {
    }
    (*currentGraphLabel).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
    (*currentGraphLabel).setAffectsParentLayout(true);
    (*uIFlexBox).addView(currentGraphLabel);
    mainGraphButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*mainGraphButton).setName("MainGraphButton");
    {
    }
    (*mainGraphButton).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*mainGraphButton).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
    (*mainGraphButton).setText("Show Main Graph");
    (*uIFlexBox).addView(mainGraphButton);
    runButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*runButton).setName("RunButton");
    {
    }
    (*runButton).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*runButton).setText("Run");
    (*uIFlexBox).addView(runButton);
    detailsView = CreateShared<UI::GroupView>([this](UI::GroupView *v)
    {
    }
);
    (*detailsView).setName("DetailsView");
    {
        (*detailsView).CountGroupItems = [this](SizeInteger const& GroupIndex)        {
            return Items[GroupIndex].Size;
        };
;
        (*detailsView).CountGroups = [this]()        {
            return Items.size();
        };
;
        (*detailsView).Group = [this](SizeInteger const& GroupIndex)        {
            return Items[GroupIndex].CreateGroup();
        };
;
        (*detailsView).GroupItem = [this](SizeInteger const& GroupIndex, SizeInteger const& Index)        {
            return Items[GroupIndex].CreateItem(Index);
        };
;
    }
    (*detailsView).setAffectsParentLayout(true);
    (*uIFlexBox).addView(detailsView);
    detailsHeader = CreateShared<UI::GroupHeader>([this](UI::GroupHeader *v)
    {
    }
);
    (*detailsHeader).setName("DetailsHeader");
    {
    }
    (*detailsHeader).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*detailsHeader).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
    (*detailsHeader).setAffectsParentLayout(true);
    (*uIFlexBox).addView(detailsHeader);
    propertyDetails = Create<LegacyClassGen::PropertyDetailsView>([this](LegacyClassGen::PropertyDetailsView *v)
    {
    }
);
    (*propertyDetails).setName("PropertyDetails");
    {
    }
    (*propertyDetails).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
    (*propertyDetails).setAffectsParentLayout(true);
    (*uIFlexBox).addView(propertyDetails);
    eventDetails = Create<LegacyClassGen::EventDetailsView>([this](LegacyClassGen::EventDetailsView *v)
    {
    }
);
    (*eventDetails).setName("EventDetails");
    {
    }
    (*eventDetails).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
    (*eventDetails).setAffectsParentLayout(true);
    (*uIFlexBox).addView(eventDetails);
    functionDetails = Create<LegacyClassGen::FunctionDetailsView>([this](LegacyClassGen::FunctionDetailsView *v)
    {
    }
);
    (*functionDetails).setName("FunctionDetails");
    {
    }
    (*functionDetails).setVisibility(UI::Visibility::SelfCollapsed|UI::Visibility::ChildrenCollapsed);
    (*functionDetails).setAffectsParentLayout(true);
    (*uIFlexBox).addView(functionDetails);
    valuesHeader = CreateShared<UI::GroupHeader>([this](UI::GroupHeader *v)
    {
    }
);
    (*valuesHeader).setName("ValuesHeader");
    {
    }
    (*valuesHeader).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*valuesHeader).setAffectsParentLayout(true);
    (*uIFlexBox).addView(valuesHeader);
    propertiesTree = Create<LegacyClassGen::EmbeddedObjectFieldEditor>([this](LegacyClassGen::EmbeddedObjectFieldEditor *v)
    {
    }
);
    (*propertiesTree).setName("PropertiesTree");
    {
    }
    (*propertiesTree).setAffectsParentLayout(true);
    (*uIFlexBox).addView(propertiesTree);
    (*this).addView(uIFlexBox);
    Super::onHierarchyCreate();
    setName("ScriptEditor");
}
//CLASSGEN END REGION


void ScriptEditor::onLinkPins(
    const SharedReference<UI::PinNodeView> &sourceNodeView, const SharedReference<UI::PinNodeView::Pin> &sourcePinView,
    const SharedReference<UI::PinNodeView> &targetNodeView, const SharedReference<UI::PinNodeView::Pin> &targetPinView
)
{
    size_t i = graphView->getNodeIndexForItemView(*sourceNodeView);
    size_t j = graphView->getNodeIndexForItemView(*targetNodeView);
    if (i == UI::InvalidIndex || j == UI::InvalidIndex)
    {
        return;
    }

    LegacyClassGen::NodeData &sourceNodeData = CurrentGraph.second.Nodes[i];
    LegacyClassGen::NodeData &targetNodeData = CurrentGraph.second.Nodes[j];

    bool isExecution = sourcePinView->getType() == UI::PinType::Output;
    Array<UI::Connection> &connectionData = isExecution ? sourceNodeData.ExecutionBranches : sourceNodeData.Connections;
    UI::Connection connection;
    connection.Reversed = !isExecution;
    connection.Source = sourcePinView->getIdentifier();
    connection.Target = targetNodeView->getIdentifier();
    if (targetPinView->getIdentifier())
    {
        connection.Target += "/" + targetPinView->getIdentifier();
    }
    connectionData.append(connection);
    connections.append(sourceNodeView->connect(sourceNodeView, targetNodeView, connection));

    ALogMessage("", "Source Node %s/%s", sourceNodeView->getIdentifier(), sourcePinView->getIdentifier());
    ALogMessage("", "Target Node %s/%s", targetNodeView->getIdentifier(), targetPinView->getIdentifier());

    //graphView->notifyInsertConnections(connections.size());
    graphView->notifyUpdateAllItems();
}

SharedReference<UI::NodeView> ScriptEditor::createNode(const LegacyClassGen::NodeData &data)
{
    SharedReference<FunctionNode> nodeView = Create<FunctionNode>();
    nodeView->title->setText(data.Identifier);
    nodeView->graphEntryPoint = data.Identifier == "EntryPoint";
    nodeView->graphReturnPoint = data.Identifier == "ReturnPoint";

    data.Data.read("Values", nodeView->templateValues);

    nodeView->onTemplateTypeChanged = [this, data](const String &name, const String &type) {
        auto it = rng::find_if(CurrentGraph.second.Nodes, [this, data](const auto &v) { return v.Identifier == data.Identifier; });
        if (it != CurrentGraph.second.Nodes.end())
        {
            AJSONObject &d = it->Data;
            if (!d.hasKey("Values"))
            {
                d.insert("Values", AJSONObject(), false);
            }
            d.at("Values").asObject().insert(name, type);
            ALogMessage("", "Template Value Changed: %s = %s", name, type);
        }
    };
    /*String functionIdentifier;
    if (data.Data.read("Function", functionIdentifier))
    {
        auto it = functions.find(functionIdentifier);// std::find_if(functions.begin(), functions.end(), [&](const LegacyClassGen::MaterialFunction &function) { return function.Identifier == functionIdentifier; });
        if (it != functions.end())
        {
            nodeView->setData(data, it->second);
        }
    }*/
    bool isEntryPoint = nodeView->isEntryPoint();
    bool isReturnPoint = nodeView->isReturnPoint();
    nodeView->inverted = CurrentGraph.first && (isEntryPoint || isReturnPoint);

    size_t index = data.Identifier.lastfind_first_of(".");
    bool isMethod = index != size_t(-1);
    auto it = [&]() -> LegacyClassGen::FunctionInfo* {
        LegacyClassGen::FunctionManager::getInstance().Index();
        auto predicate = [&](const auto &f) { return f.Identifier == data.Identifier; };
        auto &AvailableFunctions = LegacyClassGen::FunctionManager::getInstance().Cache;
        auto r = ranges::views::all(rngv::concat(Functions, AvailableFunctions));
        auto i = rng::find_if(r, predicate);
        return i != r.end() ? &*i : nullptr;
        
        /*auto typeName = nodeView->f.Identifier.left(index);

        Array<LegacyClassGen::FunctionInfo> functions;

        const Map<String, SharedReference<LegacyClassGen::BaseCGType>> &types = LegacyClassGen::ClassManager::getInstance().getLoadedTypes();
        for (const APair<String, SharedReference<LegacyClassGen::BaseCGType>> &pair : types)
        {
            String name = pair.second->getDefaultType();
            if (name != typeName)
            {
                continue;
            }
        }
        auto functionName = nodeView->f.Identifier.mid(index + 1);*/
    }();
    
    if (!(isEntryPoint || isReturnPoint) && it == nullptr && !isMethod)
    {
        nodeView->baseColor.setGreen(0.3f);
        nodeView->baseColor.setBlue(0.3f);
        nodeView->highlightedColor.setGreen(0.3f);
        nodeView->highlightedColor.setBlue(0.3f);
    }
    else
    {
        if (CurrentGraph.first)
        {
            if (isEntryPoint || isReturnPoint)
            {
                auto i = rng::find_if(Functions, [&](const auto &f) { return f.Identifier == CurrentGraph.first; });
                it = &*i;
                nodeView->f = *it;
            }

            if (isEntryPoint)
            {
                //Hack
                nodeView->f.Callable = false;
                nodeView->f.ExecutionBranches = { String() };
                nodeView->f.OutputArguments.clear();
                //Hack
                nodeView->inverted = true;
            }
            else if (isReturnPoint)
            {
                //Hack
                nodeView->f.Callable = true;
                nodeView->f.ExecutionBranches.clear();
                nodeView->f.InputArguments.clear();
                //Hack
                nodeView->inverted = true;
            }
        }
        else
        {
            if (isEntryPoint)
            {
                nodeView->f.ExecutionBranches.append(String());
            }
            else if (isReturnPoint)
            {
                nodeView->f.Callable = true;
                LegacyClassGen::Parameter p;
                p.Name = "ErrorCode";
                p.Type.Name = "SignedInteger";
                nodeView->f.InputArguments.append(p);
            }
        }

        if (!(isEntryPoint || isReturnPoint))
        {
            nodeView->f = *it;
            if (isMethod)
            {
                LegacyClassGen::Parameter p;
                p.Name = "Object";
                p.Type.Name = "Object";
                nodeView->f.InputArguments.insert(nodeView->f.InputArguments.begin(), p);
            }
        }
    }

    nodeView->updateData();
    nodeView->setSize(nodeView->getContentSize());

    //nodeView->setSizePolicy(SizePolicy::Fixed);
    //nodeView->setSize({ 200, 80 });

    /*DraggingGestureRecognizer *recognizer = new DraggingGestureRecognizer();
    recognizer->moveViewToFront = false;
    recognizer->gridSize = 1;
    nodeView->addGestureRecognizer(recognizer);*/

    AttachMenuToView(nodeView, createMenu(nodeView));

    return nodeView;
}

void ScriptEditor::showDetailsPage(size_t index)
{
    detailsHeader->setExpanded(true);
    propertyDetails->setExpanded(false);
    functionDetails->setExpanded(false);
    eventDetails->setExpanded(false);
    switch (index)
    {
    case 1:
        propertyDetails->setExpanded(true);
        break;
    case 2:
        functionDetails->setExpanded(true);
        break;
    case 3:
        eventDetails->setExpanded(true);
        break;
    default:
        break;
    }
};

void ScriptEditor::onLoad(ALoadEvent &event)
{
    if (!Items[0].CreateItem)
    {

        detailsHeader->title->setText("Details");
        valuesHeader->title->setText("Values");

        propertiesTree->onValueChanged = [&]() {
            onChanged();
        };

        propertyDetails->onNameChanged = [&](const String &oldName, const String &newName) {
            auto it = std::find_if(Properties.begin(), Properties.end(), [&](auto &i) { return i.Name == oldName; });
            if (it == Properties.end())
            {
                return false;
            }

            it->Name = newName;
            return true;
        };
        propertyDetails->onChanged = [&](const LegacyClassGen::PropertyInfo &data) {
            auto it = std::find_if(Properties.begin(), Properties.end(), [&](auto &i) { return i.Name == data.Name; });
            if (it == Properties.end())
            {
                return;
            }

            *it = data;

            propertiesTree->overrideProperty(data, data.Name) = *it;

            UIApplication::getOperationDispatcher().addDelegate([&]() {
                propertiesTree->setType(this->Type, {});
                return AError();
            }, true);

            onChanged();
        };

        functionDetails->onNameChanged = [&](const String &oldName, const String &newName) {
            auto it = std::find_if(Functions.begin(), Functions.end(), [&](auto &i) { return i.Identifier == oldName; });
            if (it == Functions.end())
            {
                return false;
            }

            it->Identifier = newName;
            return true;
        };
        functionDetails->onChanged = [&](const LegacyClassGen::FunctionInfo &data) {
            auto it = std::find_if(Functions.begin(), Functions.end(), [&](auto &i) { return i.Identifier == data.Identifier; });
            if (it == Functions.end())
            {
                return;
            }

            *it = data;

            onChanged();
        };

        eventDetails->onNameChanged = [&](const String &oldName, const String &newName) {
            auto it = std::find_if(Events.begin(), Events.end(), [&](auto &i) { return i.Name == oldName; });
            if (it == Events.end())
            {
                return false;
            }

            it->Name = newName;
            return true;
        };
        eventDetails->onChanged = [&](const LegacyClassGen::EventInfo &data) {
            auto it = std::find_if(Events.begin(), Events.end(), [&](auto &i) { return i.Name == data.Name; });
            if (it == Events.end())
            {
                return;
            }

            *it = data;

            onChanged();
        };

        auto createItem = [](auto &&text, auto &&selectCallback, auto &&callback) {
            auto item = CreateShared<UI::FlexBox>();

            SharedReference<UI::Label> label = CreateShared<UI::Label>();
            label->addGestureRecognizer(CreateShared<UI::TouchGestureRecognizer>());
            label->eventChannel.registerDelegate(selectCallback);
            label->setText(text);
            item->addView(label);

            SharedReference<UI::TextButton> closeButton = CreateShared<UI::TextButton>();
            closeButton->eventChannel.registerDelegate(callback);
            closeButton->background->setImage(::MinusButtonSmall);
            item->addView(closeButton);
            item->setData({ {}, {} });
            return item;
        };

        Items[0] = Item{ []() -> SharedReference<UI::View> {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Script");
            return header;
        }, [](size_t index) -> SharedReference<UI::View> {
            return CreateShared<UI::Label>();
        }, Items[0].Size };

        Items[1] = Item{ [&]() -> SharedReference<UI::View> {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Properties");
            header->addCustomButton(::PlusButtonSmall, [&](UI::TapGestureEvent &event) {
                LegacyClassGen::PropertyInfo p;
                p.Name = getNextName("NewProperty", Properties, [](auto &&item, auto &&name) { return item.Name != name; });
                p.Type = "Boolean";
                Properties.append(p);
                Items[1].Size = Properties.size();
                UIApplication::getOperationDispatcher().addDelegate([&]() {
                    detailsView->notifyInsertItemsInGroup(1, Properties.size() - 1);
                    ALogMessage("", "Script is changed (Properties)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            return header;
        }, [&](size_t index) -> SharedReference<UI::View> {
            String id = Properties[index].Name;
            return createItem(Properties[index].Name, [&, id](UI::TapGestureEvent &event) {
                auto it = std::find_if(Properties.begin(), Properties.end(), [&](auto &i) { return i.Name == id; });
                if (it == Properties.end())
                {
                    return;
                }
                size_t index = std::distance(Properties.begin(), it);
                propertyDetails->setData(*it);
                showDetailsPage(1);
            }, [&, id](UI::TapGestureEvent &event) {
                auto it = std::find_if(Properties.begin(), Properties.end(), [&](auto &i) { return i.Name == id; });
                if (it == Properties.end())
                {
                    return;
                }
                size_t i = std::distance(Properties.begin(), it);
                Properties.erase(it);
                UIApplication::getOperationDispatcher().addDelegate([&, i]() {
                    detailsView->notifyRemoveItemsInGroup(1, i);
                    return AError();
                }, true);
            });
        }, Items[1].Size };

        Items[2] = Item{ [&]() -> SharedReference<UI::View> {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Functions");
            header->addCustomButton(::PlusButtonSmall, [&](UI::TapGestureEvent &event) {
                LegacyClassGen::FunctionInfo f;
                f.Identifier = getNextName("NewFunction", Functions, [](auto &&item, auto &&name) { return item.Identifier != name; });
                //f.Type = "void";
                Functions.append(f);
                Items[2].Size = Functions.size();
                UIApplication::getOperationDispatcher().addDelegate([&]() {
                    detailsView->notifyInsertItemsInGroup(2, Functions.size() - 1);
                    ALogMessage("", "Script is changed (Functions)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            return header;
        }, [&](size_t index) -> SharedReference<UI::View> {
            String id = Functions[index].Identifier;
            return createItem(Functions[index].Identifier, [&, id](UI::TapGestureEvent &event) {
                auto it = std::find_if(Functions.begin(), Functions.end(), [&](auto &i) { return i.Identifier == id; });
                if (it == Functions.end())
                {
                    return;
                }
                size_t i = std::distance(Functions.begin(), it);

                if (CurrentGraph.first != id)
                {
                    setGraph(id);
                }
                size_t index = std::distance(Functions.begin(), it);
                functionDetails->setFunctionInfo(*it);
                showDetailsPage(2);
            }, [&, id](UI::TapGestureEvent &event) {
                auto it = std::find_if(Functions.begin(), Functions.end(), [&](auto &i) { return i.Identifier == id; });
                if (it == Functions.end())
                {
                    return;
                }
                size_t i = std::distance(Functions.begin(), it);
                Functions.erase(it);

                if (CurrentGraph.first == id)
                {
                    setMainGraph();
                }
                Graphs.remove(id);

                UIApplication::getOperationDispatcher().addDelegate([&, i]() {
                    detailsView->notifyRemoveItemsInGroup(2, i);
                    return AError();
                }, true);
            });
        }, Items[2].Size };

        Items[3] = Item{ [&]() -> SharedReference<UI::View> {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Events");
            header->addCustomButton(::PlusButtonSmall, [&](UI::TapGestureEvent &event) {
                LegacyClassGen::EventInfo f;
                f.Name = getNextName("NewEvent", Events, [](auto &&item, auto &&name) { return item.Name != name; });
                Events.append(f);
                Items[3].Size = Events.size();
                UIApplication::getOperationDispatcher().addDelegate([&]() {
                    detailsView->notifyInsertItemsInGroup(3, Events.size() - 1);
                    ALogMessage("", "Script is changed (Events)");
                    this->onChanged();
                    return AError();
                }, true);
            });
            return header;
        }, [&](size_t index) -> SharedReference<UI::View> {
            String id = Events[index].Name;
            return createItem(Events[index].Name, [&, id](UI::TapGestureEvent &event) {
                auto it = std::find_if(Events.begin(), Events.end(), [&](auto &i) { return i.Name == id; });
                if (it == Events.end())
                {
                    return;
                }
                size_t i = std::distance(Events.begin(), it);
                eventDetails->setEventInfo(*it);
                showDetailsPage(3);
            }, [&, id](UI::TapGestureEvent &event) {
                //detailsView->getGroupItemIndexForItemView(*event.getParent());
                auto it = std::find_if(Events.begin(), Events.end(), [&](auto &i) { return i.Name == id; });
                if (it == Events.end())
                {
                    return;
                }
                size_t i = std::distance(Events.begin(), it);
                Events.erase(it);
                UIApplication::getOperationDispatcher().addDelegate([&, i]() {
                    detailsView->notifyRemoveItemsInGroup(3, i);
                    return AError();
                }, true);
            });
        }, Items[3].Size };

       /* Items[4] = Item{ []() -> SharedReference<UI::View> {
            auto header = CreateShared<UI::GroupHeader>();
            header->title->setText("Values");
            return header;
        }, [&](size_t index) -> SharedReference<UI::View> {
            return propertiesTree;
        }, Items[4].Size };*/
        detailsView->notifyUpdateAllItems();

        mainGraphButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
            setMainGraph();
        });

        runButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
            this->Type->generate();
            auto rootPath = this->Type->path.directory();
            auto cachePath = rootPath + "__cache__";
            
            AFile f(this->Type->path.resolveWithExtension("cpp").toUnixPathString());
            if (f.open(AFileOpenMode::WriteBinary))
            {
                f.write(this->Type->generatedBuffer.toUtf8().data(), this->Type->generatedBuffer.size());
                f.close();
            }

            OS::Process::Open(
                ("D:/Projects/OneStudioProjects/BuildTool/BuildTool.exe"
                " -Product=Script"
                " -Root=" + rootPath.toUnixPathString() +
                " -FrameworkDirectory=D:/Projects/Toolchain/Frameworks"
                " -Framework=Experimental"
                " -Framework=UI"
                " -Framework=System"
                " -Framework=Data"
                " -Framework=Foundation"
                " -Framework=Math"
                " -Framework=BuildSystem"
                " -Framework=Assets"
                " -Framework=Console"
                " -Framework=Reflection"
                " -Framework=Graphics"
                " -Framework=ImageFormats"
                " -Framework=UIDarkTheme"
                " -Framework=Fonts"
                " -Framework=Flow"
                " -Framework=Platform"
                " -Framework=freetype"
                " -Framework=glew"
                " -Framework=jpeg"
                " -Framework=png"
                " -Framework=zlib"
                " -Build=" + cachePath.toUnixPathString() +
                " -Output=" + cachePath.toUnixPathString()).toUtf8().data()
            ).wait();
            
            OS::Process::Open((cachePath + "Script.exe").toUnixPathString().toUtf8().data()).wait();

            /*

            struct : public AProcessObserver
            {
                virtual void onOutputMessage(uint8_t *buffer, size_t size)
                {
                    ALogMessage("", String(Array<uint8_t>(buffer, buffer + size)).toUtf8().data());
                }

                virtual void onErrorMessage(uint8_t *buffer, size_t size)
                {
                    ALogMessage("", String(Array<uint8_t>(buffer, buffer + size)).toUtf8().data());
                }
            } observer;

            AProcess p("clang.exe", { "@C:/temp/script.args" });
            p.addObserver(&observer);
            AError e = p.execute([](const AError &error) {
                ALogMessage("", "Building finished with error code %d", error.getErrorCode());
            });

            if (!e)
            {
                AProcess p("C:/temp/script.exe", {});
                p.addObserver(&observer);
                p.execute([](const AError &error) {
                    ALogMessage("", "Script finished with error code %d", error.getErrorCode());
                });
            }*/
        });

        NodeSearchView = CreateShared<UI::NodeSearchView>();
        NodeSearchView->setType(Type);

        NodeSearchView->searchResults->OnItemTapped = [this](UI::TapGestureEvent const &Event, SizeInteger const &Index) {
            auto text = NodeSearchView->FoundFunctions[Index].Identifier;
            addNode(text);
        };
        NodeSearchView->searchField->eventChannel.registerDelegate([&](UI::TextEditedEvent &event) {
            NodeSearchView->FoundFunctions.clear();
            if (NodeSearchView->searchField->getText().size() < 4)
            {
                return;
            }

            std::vector<LegacyClassGen::FunctionInfo> v;
            std::copy_if(
                NodeSearchView->AvailableFunctions.begin(),
                NodeSearchView->AvailableFunctions.end(),
                std::back_inserter(v),
                [&](const auto &i) {
                    return i.Identifier.find_first_of(NodeSearchView->searchField->getText()) != size_t(-1);
            });

            NodeSearchView->FoundFunctions = std::move(v);
            NodeSearchView->searchResults->notifyUpdateAllItems();
        });

        NodeSearchView->addButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
            auto text = NodeSearchView->searchField->getText();
            addNode(text);
        });
        AttachMenuToView(graphView, NodeSearchView);
    }

    Super::onLoad(event);
}

void ScriptEditor::reloadSymbols()
{
    NodeSearchView->setType(Type);
}

void ScriptEditor::addNode(const String &text)
{
    auto it = std::find_if(Functions.begin(), Functions.end(), [&](auto &i) { return i.Identifier == text; });

    if (it == Functions.end())
    {
        auto &AvailableFunctions = LegacyClassGen::FunctionManager::getInstance().Cache;
        it = std::find_if(AvailableFunctions.begin(), AvailableFunctions.end(), [&](const auto &f) { return f.Identifier == text; });
    }

    if (it == Functions.end())
    {
        return;
    }

    ALogMessage("", "Insert %s", text);

    LegacyClassGen::NodeData data;
    //data.Identifier = AStaticInteger64::Random().toHexString();
    data.Identifier = text;

    const auto &nodeView = createNode(data);
    nodeView->setName(data.Identifier);
    nodeView->setPosition(data.Position);
    nodeView->identifier = data.Identifier;

    nodes.append(nodeView);
    CurrentGraph.second.Nodes.append(std::move(data));
    graphView->notifyUpdateAllItems();
    //graphView->notifyInsertNodes(nodesData.size() - 1);
}

void ScriptEditor::onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type)
{
    this->Type = type;
    if (type)
    {
        /*auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find("AObject");
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            typeData = typeIt->second;
        }*/
        propertiesTree->setType(type, {});
    }

    AJSONValue v;
    data.read("Properties", v);
    fromJSONValue(v, Properties);
    v = AJSONValue();
    data.read("Functions", v);
    fromJSONValue(v, Functions);
    v = AJSONValue();
    data.read("BindingContext", v);
    fromJSONValue(v, Events);

    //AJSONValue d;
    //data.read("Graphs", d);
    //fromJSONValue(d, Graphs);

    Items[1].Size = Properties.size();
    Items[2].Size = Functions.size();
    Items[3].Size = Events.size();

    Super::onLoad(data, type);

    AJSONObject propertiesData;
    data.read("Values", propertiesData);

    //propertiesTree->setType();
    propertiesTree->serializeValue(propertiesData);
}

void ScriptEditor::onSave(AJSONObject &data)
{
    data.insert("Values", propertiesTree->deserializeValue());
    data.insert("Properties", toJSONValue(Properties));
    data.insert("Functions", toJSONValue(Functions));
    data.insert("BindingContext", toJSONValue(Events));
    
    /*size_t connectionIndex = 0;
    for (auto &connection : connections)
    {
        SharedReference<TransitionView> transition = connection.as<TransitionView>();
        size_t i = nodes.find_first_of(transition->sourceAnchor.view.as<UI::NodeView>());
        LegacyClassGen::NodeData &data = nodesData[i];
        auto it = std::find_if(data.Connections.begin(), data.Connections.end(), [&](UI::Connection &v) {
            return v.Source == transition->connection.Source && v.Target == transition->connection.Target;
        });
        if (it != data.Connections.end())
        {
            transition->data.serialize(it->Data);

        }
    }*/

    Super::onSave(data);
    //data.insert("Properties", this->data);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
