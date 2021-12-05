//CLASSGEN GENERATED REGION: Includes
#include "DockView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION
#include "TabView.gen.h"//TODO: temp include
#include "SplitView.gen.h"//TODO: temp include
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

class DockGestureRecognizer : public GestureRecognizer
{
    enum DockState
    {
        Attached,
        Touched,
        Detach,
        DraggingFromWindow,
        DraggingAsWindow,
        Detached,
        Canceled,
    };
    String stateNames[7] =
    {
        "Attached",
        "Touched",
        "Detach",
        "DraggingFromWindow",
        "DraggingAsWindow",
        "Detached",
        "Canceled",
    };
    DockState currentState = Attached;
    Math::IntegerVector startPosition;
    AWindow* previousWindow = nullptr;
    Window* window = nullptr;

    void changeState(DockState state, const String &debugTag)
    {
        currentState = state;
    }

public:

    enum AttachSide
    {
        Top = SplitView::Up,
        Right = SplitView::Right,
        Bottom = SplitView::Down,
        Left = SplitView::Left,
        Center,
        Undefined,
    };

    AttachSide attachSide = Undefined;

    using GestureRecognizer::GestureRecognizer;

    DockView* dockView = nullptr;
    WeakReference<DockView::InternalNode> currentAttachmentNode;
    ADelegate<void(Window &window)> onDetach;
    ADelegate<void(Window &window, const WeakReference<DockView::InternalNode> &currentNode, const WeakReference<DockView::InternalNode> &previousNode, AttachSide side)> onAttachSideChanged;
    ADelegate<void(Window &window, const WeakReference<DockView::InternalNode> &node, AttachSide side)> onAttach;
    
    void setAttachSide(const WeakReference<DockView::InternalNode> &node, AttachSide attachSide)
    {
        if (this->attachSide == attachSide && currentAttachmentNode.lock().get() == node.lock().get())
        {
            return;
        }

        this->attachSide = attachSide;
        auto previousAttachmentNode = this->currentAttachmentNode;
        this->currentAttachmentNode = node;
        onAttachSideChanged(*window, currentAttachmentNode, previousAttachmentNode, attachSide);
    }

    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        if (!isInside)
        {
            return;
        }

        if (currentState == Attached)
        {
            startPosition = getView().getOwner()->getWindow()->getGeometry().position - point;
            changeState(Touched, "Down");
        }
        else if (currentState == Detached)
        {
            startPosition = event.getPosition();
            changeState(DraggingAsWindow, "Down");
            event.accept();//HACK
        }
        else
        {
            return;
        }
    }

    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        switch (currentState)
        {
        case Touched:
        {
            if (!isInside)
            {
                changeState(Detach, "Move");
                Math::IntegerRectangle geometry = Math::IntegerRectangle{ startPosition + event.getPosition(), getView().getSize() };
                UIApplication::getOperationDispatcher().addDelegate([this, geometry]() {
                    if (currentState == Canceled)
                    {
                        changeState(Attached, "Detach");
                        return AError::getEmptyError();
                    }

                    if (currentState == Attached)
                    {
                        return AError::getEmptyError();
                    }

                    previousWindow = getView().getOwner()->getWindow();

                    if (!window)
                    {
                        window = new Window();
                    }
                    window->setGeometry(geometry);
                    onDetach(*window);

                    //we still need to get events from previous window when the view is detached first time
                    previousWindow->inputEventChannel.registerObserver(*getView().getOwner());
                    changeState(DraggingFromWindow, "Move Request");

                    return AError::getEmptyError();
                }, true);
            }
        }
        break;
        case DraggingFromWindow:
            window->setGeometry(Math::IntegerRectangle{ startPosition + event.getPosition(), window->getGeometry().size });
            processMovement(event.getPosition());
            event.accept();
            break;
        case DraggingAsWindow:
            window->setGeometry(Math::IntegerRectangle{ window->getGeometry().position + event.getPosition() - startPosition, window->getGeometry().size });
            processMovement(window->getGeometry().position + event.getPosition() - dockView->getOwner()->getWindow()->getGeometry().position);
            event.accept();
            break;
        default:
            break;
        }
    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views)
    {
        switch (currentState)
        {
        case DraggingFromWindow:
            previousWindow->inputEventChannel.unregisterObserver(*getView().getOwner());
            previousWindow = nullptr;
        case DraggingAsWindow:
            changeState(Detached, "Up");
            processAttach();
            event.accept();
            break;
        case Detach:
            changeState(Canceled, "Up");
            break;
        case Touched:
            changeState(Attached, "Up");
            break;
        default:
            break;
        }
    }

    void processMovement(const Math::IntegerVector &position)
    {
        setAttachSide(WeakReference<DockView::InternalNode>(), Undefined);

        Math::IntegerVector s = dockView->getOwner()->getWindow()->getGeometry().size;
        if (!(0 <= position.x && position.x <= s.x && 0 <= position.y && position.y <= s.y))
        {
            return;
        }

        ADelegate<bool(const SharedReference<View> &node)> processNode = [this, &position, &processNode](const SharedReference<View> &node) -> bool {
            if (SharedReference<SplitView> splitNode = DynamicCast<SplitView>(node))
            {
                for (auto &view : splitNode->getViews())
                {
                    if (processNode(view))
                    {
                        return true;
                    }
                }
            }
            else if (SharedReference<DockView::InternalNode> tabNode = DynamicCast<DockView::InternalNode>(node))
            {
                const auto &&start = mapFromScreenSpaceToWorldSpace(*tabNode->getOwner()->getSpace(), position, 1.0f);
                const auto &&end = mapFromScreenSpaceToWorldSpace(*tabNode->getOwner()->getSpace(), position, -1.0f);

                const Math::Vector planePosition = Math::Vector{ 0, 0, 0 };
                const Math::Vector planeNormal = Math::Vector{ 0, 0, -1 };

                Math::Vector contactPoint;
                if (Math::intersectRayWithPlane(mapFromWorldSpaceToLocalSpace(*tabNode, start), mapFromWorldSpaceToLocalSpace(*tabNode, end), planePosition, planeNormal, contactPoint))
                {
                    if (0.0f <= contactPoint.x && contactPoint.x <= 1.0f && 0.0f <= contactPoint.y && contactPoint.y <= 1.0f)
                    {
                        if (contactPoint.x < 0.33f)
                        {
                            setAttachSide(tabNode, Left);
                        }
                        else if (contactPoint.x > 0.66f)
                        {
                            setAttachSide(tabNode, Right);
                        }
                        else if (contactPoint.y < 0.33f)
                        {
                            setAttachSide(tabNode, Top);
                        }
                        else if (contactPoint.y > 0.66f)
                        {
                            setAttachSide(tabNode, Bottom);
                        }
                        else
                        {
                            setAttachSide(tabNode, Center);
                        }
                        return true;
                    }
                }
            }
            return false;
        };

        for (auto &view : dockView->getViews())
        {
            if (processNode(view))
            {
                break;
            }
        }
        //ALogMessage("", "Is %s (%d %d)", isReadyForAttach ? "inside" : "outside", position.x, position.y);
    }

    void processAttach()
    {
        if (attachSide == Undefined)
        {
            return;
        }

        UIApplication::getOperationDispatcher().addDelegate([this]() {
            onAttach(*window, currentAttachmentNode, attachSide);
            window->hide(); //TODO: destroy window
            changeState(Attached, "Attach");
            return AError::getEmptyError();
        }, true);
    }
};

class DockViewGestureRecognizer : public GestureRecognizer
{
public:
    DockView *owner = nullptr;

    void onTouchDown(AWindowTouchDownEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {

    }

    void onTouchMove(AWindowTouchMoveEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {

    }

    void onTouchUp(AWindowTouchUpEvent &event, const Math::IntegerVector &point, bool isInside, const Array<APair<SharedReference<View>, Math::IntegerVector>> &views) override
    {

    }
};

//CLASSGEN GENERATED REGION: ClassImplementation
DockView::DockView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void DockView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Areas", toJSONValue(Areas));
}
void DockView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Areas", value);
    fromJSONValue(value, Areas);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Array<UI::DockViewArea> DockView::getAreas() const
{
    return this->Areas;
}
void DockView::setAreas(Array<UI::DockViewArea> const &Areas)
{
    this->Areas = Areas;
    UpdateAreas();
}
void DockView::setAreas(Array<UI::DockViewArea> &&Areas)
{
    this->Areas = std::move(Areas);
    UpdateAreas();
}
void DockView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("DockView");
}
//CLASSGEN END REGION

void DockView::UpdateAreas()
{
    removeAllViews();

    Array<SplitViewLayoutData> data;
    data.resize(this->Areas.size());
    setData(data);

    for (const DockViewArea &area : this->Areas)
    {
        if (area.Tabs.size() == 0)
        {
            continue;
        }

        SharedReference<InternalNode> node = CreateShared<InternalNode>();
        node->owner = this;
        node->setSizePolicy(SizePolicy::Expanded);
        Array<String> titles;
        for (const DockViewTab &tab : area.Tabs)
        {
            node->tabView->addView(tab.ContentView);
            titles.push_back(tab.Title);

            auto sharedTab = node->createSharedTab(tab);
            sharedTab->parentNode = node.get();
            node->tabView->tabViews.push_back(sharedTab);
        }
        node->tabView->setTabs(titles);

        Array<UI::OverlayData> d;
        d.resize(area.Tabs.size());
        node->tabView->pages->setData(d);

        addView(node);
    }
}

void moveTab(DockView::InternalNode &targetNode, const WeakReference<DockView::InternalNode::SharedTab> &tabWeak)
{
    auto tab = tabWeak.lock();
    size_t i = tab->parentNode->tabView->tabs->getIndexForItemView(*tab);
    targetNode.tabView->tabViews.push_back(tab);

    auto tabs = targetNode.tabView->getTabs();
    tabs.push_back(tab->parentNode->tabView->getTabs()[i]);
    targetNode.tabView->setTabs(tabs);

    auto contentView = tab->parentNode->tabView->pages->getViews()[i];
    targetNode.tabView->pages->addView(contentView);
    targetNode.tabView->pages->setCurrentPage(tabs.size() - 1);

    Array<UI::OverlayData> d;
    d.resize(tabs.size());
    targetNode.tabView->pages->setData(d);

    auto layoutData = targetNode.getData();
    layoutData.push_back({});
    targetNode.setData(layoutData);

    auto currentTabs = tab->parentNode->tabView->getTabs();
    currentTabs.erase(currentTabs.begin() + i);
    tab->parentNode->tabView->tabViews.erase(tab->parentNode->tabView->tabViews.begin() + i);
    tab->parentNode->tabView->setTabs(currentTabs);
    tab->parentNode->tabView->tabs->notifyRemoveItems(i);
    tab->parentNode->tabView->pages->setCurrentPage(tab->parentNode->tabView->pages->getViews().size() > 0 ? Math::getMin(tab->parentNode->tabView->pages->getViews().size() - 1, tab->parentNode->tabView->pages->getCurrentPage()) : 0);
    tab->parentNode = &targetNode;

    targetNode.tabView->tabs->notifyUpdateAllItems();//TODO: optimize. replace with insertion 
}
    
SharedReference<DockView::InternalNode::SharedTab> DockView::InternalNode::createSharedTab(const DockViewTab &data)
{
    SharedReference<SharedTab> t = owner->SharedTabAllocator ? owner->SharedTabAllocator(data) : SharedReference<SharedTab>(new SharedTab());
    WeakReference<SharedTab> tabWeak = t;
    t->title->setText(data.Title);
    DockGestureRecognizer* recognizer = new DockGestureRecognizer();
    recognizer->dockView = owner;
    recognizer->onDetach = [tabWeak](Window &window) {
        auto tab = tabWeak.lock();
        window.setFlags(WindowFlags::Borderless);
        window.setGeometry(Math::IntegerRectangle{ window.getGeometry().position, tab->parentNode->getSize() });

        SharedReference<InternalNode> newNode = CreateShared<InternalNode>();
        newNode->owner = tab->parentNode->owner;
        moveTab(*newNode, tab);

        window.setView(newNode);
        //window.setTitle(Tabs[i]);
        //t->setHorizontalSizePolicy(SizePolicy::Expanded);
        //c->show();
        window.show();
    };
    recognizer->onAttachSideChanged = [this](Window &window, const WeakReference<DockView::InternalNode> &currentNodeWeak, const WeakReference<DockView::InternalNode> &previousNodeWeak, DockGestureRecognizer::AttachSide side) {
        auto previousNode = previousNodeWeak.lock();
        if (previousNode)
        {
            previousNode->area->collapse();
        }

        auto currentNode = currentNodeWeak.lock();
        if (!currentNode)
        {
            return;
        }

        currentNode->area->expand();
        currentNode->area->setSize(currentNode->getSize() / 2);
        Array<OverlayData> layoutData = getData();
        switch (side)
        {
        case DockGestureRecognizer::Top:
            layoutData[1].horizontalAlignment = Core::Alignment::Start;
            layoutData[1].verticalAlignment = Core::Alignment::Start;
            currentNode->area->setSizePolicy(SizePolicy::Expanded, SizePolicy::Fixed);
            break;
        case DockGestureRecognizer::Right:
            layoutData[1].horizontalAlignment = Core::Alignment::End;
            layoutData[1].verticalAlignment = Core::Alignment::Start;
            currentNode->area->setSizePolicy(SizePolicy::Fixed, SizePolicy::Expanded);
            break;
        case DockGestureRecognizer::Bottom:
            layoutData[1].horizontalAlignment = Core::Alignment::Start;
            layoutData[1].verticalAlignment = Core::Alignment::End;
            currentNode->area->setSizePolicy(SizePolicy::Expanded, SizePolicy::Fixed);
            break;
        case DockGestureRecognizer::Left:
            layoutData[1].horizontalAlignment = Core::Alignment::Start;
            layoutData[1].verticalAlignment = Core::Alignment::Start;
            currentNode->area->setSizePolicy(SizePolicy::Fixed, SizePolicy::Expanded);
            break;
        case DockGestureRecognizer::Center:
            layoutData[1].horizontalAlignment = Core::Alignment::Start;
            layoutData[1].verticalAlignment = Core::Alignment::Start;
            currentNode->area->setSizePolicy(SizePolicy::Expanded);
            break;
        default:
            return;
        }
        setData(layoutData);
    };
    recognizer->onAttach = [this, tabWeak](Window &window, const WeakReference<DockView::InternalNode> &nodeWeak, DockGestureRecognizer::AttachSide side) {
        auto tab = tabWeak.lock();
        auto node = nodeWeak.lock();
        node->area->collapse();

        if (side == DockGestureRecognizer::Center)
        {
            moveTab(*node, tab);
            //node->attachedWindows.append(DockWindow{ item.title, v, item.view });
            //node->notifyInsertItems(node->attachedWindows.size() - 1);
            return;
        }

        UI::Direction targetDirection = side == DockGestureRecognizer::Top || side == DockGestureRecognizer::Bottom ? UI::Direction::Vertical : UI::Direction::Horizontal;

        auto parentSplitView = static_cast<UI::SplitView*>(node->getParent());
        size_t index = std::distance(parentSplitView->getViews().begin(), std::find_if(parentSplitView->getViews().begin(), parentSplitView->getViews().end(), [&](auto &i) { return i.get() == node.get(); }));

        size_t targetIndex = side == DockGestureRecognizer::Top || side == DockGestureRecognizer::Left ? index : index + 1;

        if (parentSplitView->getData().size() == 1) //Just set wanted direction
        {
            parentSplitView->setDirection(targetDirection);

            SharedReference<InternalNode> newNode = CreateShared<InternalNode>();
            newNode->owner = tab->parentNode->owner;
            newNode->setSizePolicy(SizePolicy::Expanded);
            moveTab(*newNode, tab);
            parentSplitView->insertView(targetIndex, newNode);

            Array<SplitViewLayoutData> layoutData;
            layoutData.resize(parentSplitView->getViews().size());
            parentSplitView->setData(layoutData);
            auto halfSize = parentSplitView->getSize()[size_t(targetDirection)] / 2;
            parentSplitView->primaryNodes[index].currentSize = halfSize;
            parentSplitView->primaryNodes.insert(parentSplitView->primaryNodes.begin(), { halfSize });
        }
        else if (parentSplitView->getDirection() == targetDirection) //Append node
        {
            SharedReference<InternalNode> newNode = SharedReference<InternalNode>();
            newNode->owner = tab->parentNode->owner;
            newNode->setSizePolicy(SizePolicy::Expanded);
            moveTab(*newNode, tab);
            parentSplitView->insertView(targetIndex, newNode);

            Array<SplitViewLayoutData> layoutData;
            layoutData.resize(parentSplitView->getViews().size());
            parentSplitView->setData(layoutData);

            parentSplitView->primaryNodes[index].currentSize /= 2;
        }
        else //Need to create opposite split view
        {
            SharedReference<UI::SplitView> newSplitView = CreateShared<SplitView>();
            newSplitView->setSizePolicy(SizePolicy::Expanded);
            parentSplitView->wrapView(*node, newSplitView);

            newSplitView->setDirection(targetDirection);

            SharedReference<InternalNode> newNode = CreateShared<InternalNode>();
            newNode->owner = tab->parentNode->owner;
            newNode->setSizePolicy(SizePolicy::Expanded);
            moveTab(*newNode, tab);
            newSplitView->insertView(index == targetIndex ? 0 : 1, newNode);

            Array<SplitViewLayoutData> layoutData;
            layoutData.resize(newSplitView->getViews().size());
            newSplitView->setData(layoutData);

            auto halfSize = parentSplitView->getSize()[size_t(targetDirection)] / 2;
            newSplitView->primaryNodes.push_back({ halfSize });
            newSplitView->primaryNodes.push_back({ halfSize });
        }

    };
    t->addGestureRecognizer(SharedReference<DockGestureRecognizer>(recognizer));
    return t;
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
