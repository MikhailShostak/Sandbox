#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"
#include "ClassGenLibraryDebug"

#include "Foundation"
#include "ClassGenExtensions"
#include "ExperimentalDebug"

//CLASSGEN END REGION
#include "Includes/TypeInfo.gen.h"
#include "ViewPropertiesEditor.gen.h"
#include "ClassEditor.gen.h"
#include "ObjectEditor.gen.h"
#include "ViewNode.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ViewEditorView : public UI::SplitView, public LegacyClassGen::Editor, public UI::ItemAdapter, public UI::TreeAdapter<LegacyClassGen::ViewNode>
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ViewEditorView This;
    typedef UI::SplitView Super;
    typedef std::tuple<LegacyClassGen::Editor, UI::ItemAdapter, UI::TreeAdapter<LegacyClassGen::ViewNode>> Interfaces;
public:
    ViewEditorView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::GroupPanel> viewsGroupPanel;
        SharedReference<UI::TreeView<LegacyClassGen::ViewNode>> outliner;
    SharedReference<UI::TextButton> testButton;
    SharedReference<UI::TextButton> snapToGridSwitcher;
    SharedReference<UI::TextButton> gridSwitcher;
    SharedReference<UI::TextButton> checkSwitcher;
    SharedReference<UI::GridView> gridView;
        SharedReference<UI::ScrollView> graph;
    SharedReference<LegacyClassGen::ViewPropertiesEditor> propertiesView;
    SharedReference<LegacyClassGen::ClassEditor> classEditor;
    void onHierarchyCreate();
//CLASSGEN END REGION
    SharedReference<UI::TextButton> generateButton;

    ViewNode *currentNode = nullptr;

    SharedReference<UI::ResizeGestureRecognizer> resizeRecognizer = CreateShared<UI::ResizeGestureRecognizer>();
    UI::View *currentView = nullptr;

    SharedReference<ViewNode> rootNode = CreateShared<ViewNode>("Root");
public:

    bool snapToGrid = true;
    bool gridVisibility = true;
    bool checkVisibility = true;

    void updateCurrentNode()
    {
        if (currentNode)
        {
            //TODO: improve updates
            serializeCurrentNode();

            if (currentNode->View->getInstance() && currentNode->Data.hasKey("Values"))
            {
                AJSONObject values = collectValuesRecursivly(currentNode->Data);
                currentNode->View->getInstance()->deserialize(values);
            }
            currentNode->View->setTransform(currentNode->View->getInstance()->getTransform());
            currentNode->View->setSize(currentNode->View->getInstance()->getSize());
            currentNode->View->getInstance()->setTransform({}); //HACK: clear deserialized transform
            currentNode->View->getInstance()->requestUpdate();
        }
    }

    void selectNode(ViewNode *item)
    {
        if (currentNode == item)
        {
            return;
        }

        if (isLoaded())
        {
            //TODO: improve focus logic
            getOwner()->getWindow()->removeFocus();
        }

        //updateCurrentNode();

        currentNode = item;

        UIApplication::getOperationDispatcher().addDelegate([this]() {
            if (currentView)
            {
                currentView->removeGestureRecognizer(resizeRecognizer);
            }

            currentView = currentNode->View.get();

            currentView->addGestureRecognizer(resizeRecognizer);
            
            if (!currentNode->Parent)
            {
                propertiesView->setVisible(false);
                classEditor->setVisible(true);
            }
            else
            {
                propertiesView->setVisible(true);
                classEditor->setVisible(false);
                propertiesView->setNode(currentNode);
                propertiesView->onLoad(currentNode->Data);
            }
        
            if(currentNode->View->getParent())
            {
                currentNode->View->getParent()->requestUpdate();
            }

            return AError::getEmptyError();
        }, true);
    }

    virtual void onItemSelected(const AObject &sender, UI::TapGestureEvent &event, ViewNode *item)
    {
        selectNode(item);
    }

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        viewsGroupPanel->headerLabel->setText("Views");

        classEditor->onChanged = [this]() {
            ALogMessage("", "UI::View is changed");
            updateCurrentNode();
            this->onChanged();
        };

        
        propertiesView->onChanged = [this]() {
            ALogMessage("", "Subview is changed");
            updateCurrentNode();
            this->onChanged();
        };

        if (!outliner->getProxyAdapter())
        {
            outliner->setProxyAdapter(this);
        }

        if (graph->getGestureRecognizers().size() == 1)
        {

            auto swipe = CreateShared<UI::SwipeGestureRecognizer>();
            swipe->setTouchID(ATouchID::MiddleMouseButton);
            graph->addGestureRecognizer(swipe);

            snapToGridSwitcher->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
                gridView->snapToGrid = !gridView->snapToGrid;
                resizeRecognizer->gridSize = snapToGrid ? 10 : 0;
            });

            gridSwitcher->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
                gridView->gridVisibility = !gridView->gridVisibility;
                gridView->updateGrid();
            });

            checkSwitcher->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
                gridView->checkVisibility = !gridView->checkVisibility;
                gridView->updateGrid();
            });

            testButton->eventChannel.registerDelegate([&](UI::TapGestureEvent &event) {
                this->Type->generate();

                OS::Process::Open(
                    "D:/Projects/OneStudioProjects/BuildTool/BuildTool.exe"
                    " -Product=Sandbox"
                    " -Root=D:/Projects/OneStudioProjects/Sandbox/Source"
                    " -FrameworkDirectory=D:/Projects/Toolchain/Frameworks"
                    " -Framework=Experimental"
                    " -Framework=UI"
                    " -Framework=System"
                    " -Framework=Data"
                    " -Framework=Foundation"
                    " -Framework=Math"
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
                    " -Build=D:/Projects/OneStudioProjects/Sandbox/Build"
                    " -Output=D:/Projects/OneStudioProjects/Sandbox/Binary"
                ).wait();
                
                OS::Process::Open("D:/Projects/OneStudioProjects/Sandbox/Binary/Sandbox.exe").wait();
            });
        }

        classEditor->setVisible(false);

        setSizePolicy(UI::SizePolicy::Expanded);

        Node n;
        n.currentSize = 200;
        n.minimalSize = 200;
        primaryNodes.push_back(n);
        n.currentSize = 200;
        n.minimalSize = 200;
        primaryNodes.push_back(n);
        n.currentSize = 400;
        n.minimalSize = 200;
        primaryNodes.push_back(n);

        AttachMenuToView(rootNode->View, createMenu(rootNode.get()));
        resizeRecognizer->gridSize = 10;
    }

    SharedReference<LegacyClassGen::BaseCGType> Type;

    void onLoad(const AJSONObject &data, const SharedReference<LegacyClassGen::BaseCGType> &type = nullptr) override
    {
        this->Type = type;
        const SharedReference<ViewNode> &rootNode = Deserialize(data);
        rootNode->Name = type->path.baseName();
        setRootNode(rootNode);
        selectNode(getRootNode().get());
        classEditor->onLoad(data, type);
        rootNode->View->requestUpdate();
    }

    void onSave(AJSONObject &data) override
    {
        serializeCurrentNode();
        getRootNode()->Data.remove("Name"); //TODO: temp code
        data = Serialize(getRootNode());
    }

    void serializeCurrentNode()
    {
        if (currentNode->Parent)
        {
            propertiesView->onSave(currentNode->Data);
        }
        else
        {
            classEditor->onSave(getRootNode()->Data);
        }
    }

    SharedReference<ViewNode> getRootNode()
    {
        return rootNode;
    }

    void setRootNode(const SharedReference<ViewNode> &rootNode)
    {
        auto oldView = graph->contentView;
        graph->contentView = rootNode->View;
        graph->surface->replaceView(oldView, graph->contentView);
        UIApplication::getOperationDispatcher().addDelegate([=]() {
            graph->horizontalSlider->setHandlePositionRatio(0.5f);
            graph->verticalSlider->setHandlePositionRatio(0.5f);
            return AError();
        }, true);
        this->rootNode = rootNode;

        if (!outliner->getProxyAdapter())
        {
            //This code is required because onLoad happens too late
            outliner->setProxyAdapter(this);
        }
        outliner->notifyUpdateAllItems();
    }

    AJSONObject collectValuesRecursivly(const AJSONObject &object)
    {
        AJSONObject values;
        object.read("Values", values);

        LegacyClassGen::TypeInfo typeInfo;
        String baseType;
        if(object.read("BaseType", baseType))
        {
            readRecursively(baseType, typeInfo);
        }
        else
        {
            typeInfo.Name = "UI.View";
        }
        
        //TODO: base type is not found
        auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeInfo.Name);
        if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
        {
            walkInheritance(typeIt->second, [&](auto &baseTypeData){
                AJSONObject valuesData;
                baseTypeData->data.read("Values", valuesData);
                for (const auto &p : valuesData)
                {
                    if(!values.hasKey(p.first))
                    {
                        values.insert(p.first, p.second);
                    }
                }
            }, [&](auto &){

            });
        }

        return values;
    }

    //TODO: optimize
    SharedReference<ViewNode> Deserialize(const AJSONObject &object, ViewNode *parent = nullptr)
    {
        SharedReference<ViewNode> node = CreateShared<ViewNode>();
        node->Parent = parent;
        node->View = createNode(node.get(), parent ? parent->View.get() : nullptr);
        node->Data = object;
        String baseType;
        if(object.read("BaseType", baseType))
        {
            readRecursively(baseType, node->Type);
        }
        else
        {
            node->Type.Name = "UI.View";
        }
        object.read("Name", node->Name);

        AJSONObject values = collectValuesRecursivly(object);
        node->View->deserialize(values);

        node->updateInstance();
        if (node->View->getInstance())
        {
            node->View->getInstance()->deserialize(values);
            node->View->setName(String("Node - ") + (!node->Name.empty() ? node->Name : node->Type.Name));

            if (parent)
            {
                node->View->setVerticalSizePolicy(node->View->getInstance()->getVerticalSizePolicy());
                node->View->setHorizontalSizePolicy(node->View->getInstance()->getHorizontalSizePolicy());
            }
            else
            {
                node->View->setSize(Math::IntegerVector{ 800, 480 });
                node->View->setSizePolicy(UI::SizePolicy::Fixed);
            }

            if (SharedReference<UI::ImageView> imageView = DynamicCast<UI::ImageView>(node->View->getInstance()))
            {
                String texture;
                if (values.read("Image", texture))
                {
                    imageView->setImage(AssetManager::getInstance().assets.at(texture)().toValue<SharedReference<Graphics::Texture>>());
                }
            }
            else if (SharedReference<UI::BorderImageView> imageView = DynamicCast<UI::BorderImageView>(node->View->getInstance()))
            {
                String texture;
                if (values.read("Image", texture))
                {
                    imageView->setImage(AssetManager::getInstance().assets.at(texture)().toValue<SharedReference<Graphics::Texture>>());
                }
            }
        }

        if (parent)
        {
            object.read("Variable", node->isVariable);
        }

        AJSONArray views;
        if (object.read("PreViews", views))
        {
            for (const AJSONValue &view : views)
            {
                SharedReference<ViewNode> n = Deserialize(view.toObject(), node.get());
                n->Placement = LegacyClassGen::ViewPlacement::Background;
                node->Items.push_back(n);
            }
        }

        AJSONObject content;
        if (object.read("Content", content))
        {
            for (const APair<String, AJSONValue> &p : content)
            {
                SharedReference<ViewNode> n = Deserialize(p.second.toObject(), node.get());
                n->Name = p.first;
                n->Placement = LegacyClassGen::ViewPlacement::Content;
                node->Items.push_back(n);
            }
        }

        views.clear();
        if (object.read("Views", views))
        {
            for (const AJSONValue &view : views)
            {
                SharedReference<ViewNode> n = Deserialize(view.toObject(), node.get());
                n->Placement = LegacyClassGen::ViewPlacement::View;
                node->Items.push_back(n);
            }
        }

        return node;
    }

    //TODO: optimize
    AJSONObject Serialize(const SharedReference<ViewNode> &node)
    {
        AJSONObject object = node->Data;

        AJSONArray backgroundViews;
        AJSONArray views;
        AJSONObject content;
        for (const SharedReference<ViewNode> &item : node->Items)
        {
            switch(item->Placement)
            {
            case ViewPlacement::Content:
            {
                String name = std::move(item->Name);
                content.insert(name, Serialize(item));
                item->Name = std::move(name);
            }
                break;
            case ViewPlacement::Background:
                backgroundViews.push_back(Serialize(item));
                break;
            case ViewPlacement::View:
                views.push_back(Serialize(item));
                break;
            }
        }
        object.insert("PreViews", backgroundViews);
        object.insert("Views", views);
        object.insert("Content", content);

        if (node->Parent)
        {
            object.insert("Variable", node->isVariable);
        }

        return object;
    }

    UI::SizeType getCountItems(const AObject &sender) const override { return 0; }
    SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override { return nullptr; }

    virtual UI::SizeType getCountRootItems() const override { return 1; }
    virtual ViewNode *getRootItem(UI::SizeType index) override { return rootNode.get(); }
    virtual UI::SizeType getCountChildItems(ViewNode *parentItem) const override { return parentItem->isExpanded ? parentItem->GetItems().size() : 0; }
    virtual ViewNode *getChildItem(ViewNode *parentItem, UI::SizeType index) override { return parentItem->GetItems()[index].get(); }

    //virtual bool shouldAddTouchGestureRecognizerToItem(UI::SizeType index) const override { return false; }
    //virtual bool shouldAddTouchGestureRecognizerToItem(const ViewNode *item) override { return false; }

    SharedReference<PreviewNodeView> createNode(ViewNode *node, PreviewNodeView *parent = nullptr)
    {
        SharedReference<PreviewNodeView> nodeView = CreateShared<PreviewNodeView>();

        if (parent)
        {
            auto recognizer = CreateShared<UI::DraggingGestureRecognizer>();
            recognizer->moveViewToFront = false;
            recognizer->gridSize = 10;
            nodeView->addGestureRecognizer(recognizer);

            parent->getInstance()->addView(nodeView);
        }
        else
        {
            nodeView->setPosition(Math::Vector{ 10, 10, 0 });
        }

        nodeView->eventChannel.registerDelegate([this, node](UI::TouchMoveGestureEvent &event) {
            if (!node->Data.hasKey("Values"))
            {
                node->Data.insert("Values", AJSONObject(), false);
            }
            node->Data.at("Values").asObject().insert("Transform", toJSONValue(event.getView().getTransform()));
            propertiesView->setValue("Transform", toJSONValue(event.getView().getTransform()));
        });

        WeakReference<PreviewNodeView> weakView = nodeView;
        nodeView->eventChannel.registerDelegate([this, node, weakView](ATransformEvent &event) {
            if (!node->Data.hasKey("Values"))
            {
                node->Data.insert("Values", AJSONObject(), false);
            }
            auto v = weakView.lock();
            node->Data.at("Values").asObject().insert("Transform", toJSONValue(v->getTransform()));
            node->Data.at("Values").asObject().insert("Size", toJSONValue(v->getSize()));
            propertiesView->setValue("Transform", toJSONValue(v->getTransform()));
            propertiesView->setValue("Size", toJSONValue(v->getSize()));
        });

        nodeView->addGestureRecognizer(CreateShared<UI::TouchGestureRecognizer>());
        nodeView->eventChannel.registerDelegate([this, node](UI::TouchDownGestureEvent &event) {
            if (event.isInside())
            {
                selectNode(node);
            }
        });

        AttachMenuToView(nodeView, createMenu(node));
        return nodeView;
    }

    SharedReference<UI::MenuView> createMenu(ViewNode *item)
    {
        SharedReference<UI::MenuView> menuView = CreateShared<UI::MenuView>();
        menuView->addAction(UI::MenuAction{ "Add view...", [this, item](UI::TapGestureEvent &event) {
            auto newItem = CreateShared<ViewNode>(Str::GetNextAvailableName("NewView", item->Items, [](auto &&item, auto &&name) { return item->Name != name; }));
            newItem->Type.Name = "UI.View";
            newItem->Parent = item;

            SharedReference<PreviewNodeView> view = createNode(newItem.get(), item->View.get());
            view->setSize(Math::IntegerVector{ 100, 100 });
            newItem->View = view;

            newItem->updateInstance();

            item->Items.push_back(newItem);
            if (item->TreeItem.lock())
            {
                if (!item->TreeItem.lock()->getExpandable())
                {
                    item->TreeItem.lock()->setExpandable(true);
                }
                if (item->isExpanded)
                {
                    outliner->notifyUpdateChildren(item);
                }
            }
        } });
        menuView->addAction(UI::MenuAction{ "Wrap view...", [this, item](UI::TapGestureEvent &event) {
            if (!item->Parent)
            {
                return;
            }

            ViewNode *parent = item->Parent;

            auto newItem = CreateShared<ViewNode>(Str::GetNextAvailableName("NewView", parent->Items, [](auto &&item, auto &&name) { return item->Name != name; }));
            newItem->Type.Name = "UI.View";
            newItem->Parent = parent;

            SharedReference<PreviewNodeView> view = createNode(newItem.get(), parent->View.get()); //TODO: need to insert instance to parent at specific position
            view->setSize(Math::IntegerVector{ 100, 100 });
            newItem->View = view;

            newItem->updateInstance();
            newItem->View->getInstance()->addView(item->View);

            auto it = ranges::find_if(
                parent->Items,
                [&](const SharedReference<LegacyClassGen::ViewNode> &i) { return i.get() == item; }
            );
            newItem->Items.push_back(*it);
            item->Parent = newItem.get();
            *it = newItem;

            if (item->TreeItem.lock())
            {
                if (!item->TreeItem.lock()->getExpandable())
                {
                    item->TreeItem.lock()->setExpandable(true);
                }
                if (item->isExpanded)
                {
                    outliner->notifyUpdateChildren(parent);
                }
            }
        } });
        menuView->addAction(UI::MenuAction{ "Replace with children", [this, item](UI::TapGestureEvent &event) {
            if (!item->Parent || item->Items.size() == 0)
            {
                return;
            }

            ViewNode *parent = item->Parent;

            auto it = std::find_if(
                parent->Items.begin(),
                parent->Items.end(),
                [&](const SharedReference<LegacyClassGen::ViewNode> &i) { return i.get() == item; }
            );
            SharedReference<ViewNode> node = *it;
            parent->Items.erase(it);
            parent->Items.insert(it, node->Items.size(), nullptr);
            for (auto &i : item->Items)
            {
                i->Parent = parent;
                parent->View->getInstance()->addView(i->View);
                *it = i;
            }
            item->View->removeFromParent();

            if (item->TreeItem.lock())
            {
                if (!item->TreeItem.lock()->getExpandable())
                {
                    item->TreeItem.lock()->setExpandable(true);
                }
                if (item->isExpanded)
                {
                    outliner->notifyUpdateChildren(parent);
                }
            }
        } });
        menuView->addAction(UI::MenuAction{ "Remove", [this, item](UI::TapGestureEvent &event) {
            if (item->Parent == nullptr)
            {
                item->TreeItem.lock()->setExpandable(false);
                for (auto &child : item->Items)
                {
                    child->View->removeFromParent();
                }
                item->Items.clear();
                outliner->notifyUpdateChildren(item);
                return;
            }
            item->View->removeFromParent();
            auto parent = item->Parent;
            parent->Items.erase(std::remove_if(parent->Items.begin(), parent->Items.end(), [&](auto &i) {
                return item == i.get();
            }), parent->Items.end());
            if (parent->TreeItem.lock())
            {
                if (parent->Items.empty())
                {
                    parent->TreeItem.lock()->setExpandable(false);
                }
                outliner->notifyUpdateChildren(parent);
            }
        } });
        menuView->addAction(UI::MenuAction{ "Clear", [this, item](UI::TapGestureEvent &event) {
            for (auto &child : item->Items)
            {
                child->View->removeFromParent();
            }
            item->Items.clear();
            if (item->TreeItem.lock())
            {
                item->TreeItem.lock()->setExpandable(false);
                outliner->notifyUpdateChildren(item);
            }
        } });
        menuView->addAction(UI::MenuAction{ "Assign to slot", [this, item](UI::TapGestureEvent &event) {
            item->Placement = ViewPlacement::Content;
        } });
        menuView->addAction(UI::MenuAction{ "Move to background", [this, item](UI::TapGestureEvent &event) {
            item->Placement = ViewPlacement::Background;
        } });
        menuView->addAction(UI::MenuAction{ "Move to views", [this, item](UI::TapGestureEvent &event) {
            item->Placement = ViewPlacement::View;
        } });

        return menuView;
    }

    virtual SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType depth, ViewNode *item) override
    {
        SharedReference<UI::DefaultExpandableItemView> sharedTreeItem = CreateShared<UI::DefaultExpandableItemView>();
        WeakReference<UI::DefaultExpandableItemView> treeItem = sharedTreeItem;
        treeItem.lock()->applyParameters(depth, !item->Name.empty() ? item->Name : writeRecursively(item->Type), item->Items.size() > 0);
        treeItem.lock()->setItemExpanded(item->isExpanded);
        treeItem.lock()->expandButton->eventChannel.registerDelegate([this, item, treeItem](UI::TapGestureEvent &event) {
            treeItem.lock()->setItemExpanded(item->isExpanded = !item->isExpanded);
            UIApplication::getOperationDispatcher().addDelegate([this, item]() {
                //loadContent(item);
                outliner->notifyUpdateChildren(item);
                return AError::getEmptyError();
            }, true);
        });
        item->TreeItem = treeItem;

        AttachMenuToView(sharedTreeItem, createMenu(item));
        return sharedTreeItem;
    }

};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
