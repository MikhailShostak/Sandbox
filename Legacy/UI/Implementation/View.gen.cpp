//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

#include "UIComponent.h"
#include <Graphics>

#include "Includes/RelativeLayout.gen.h"

#include "Includes/FlexBox.gen.h"
#include "Includes/FlexBoxData.gen.h"
#include "Includes/TreeView.gen.h"//TODO:temp include
#include "Includes/DefaultExpandableItemView.gen.h"
#include "Includes/ViewWindow.gen.h"
#include "UIApplication.h"
#include "Core/AFreeCameraInputController.h"

UnorderedDictionary<void *, Stack<Math::IntegerRectangle>> CullingData;

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
View::View()
{
    Math::Transform transform_759;
    Math::Vector position_760;
    position_760.X = 0.000000;
    position_760.Y = 0.000000;
    position_760.Z = 0.000000;
    position_760.W = 0.000000;
    transform_759.Position = position_760;
    Math::Quaternion rotation_765;
    rotation_765.X = 0.000000;
    rotation_765.Y = 0.000000;
    rotation_765.Z = 0.000000;
    rotation_765.W = 1.000000;
    transform_759.Rotation = rotation_765;
    (*this).setTransform(transform_759);
    Math::IntegerVector size_770;
    size_770.X = 0.000000;
    size_770.Y = 0.000000;
    size_770.Z = 0.000000;
    size_770.W = 0.000000;
    (*this).setSize(size_770);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void View::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Transform", toJSONValue(Transform));
    object.insert("Size", toJSONValue(Size));
    object.insert("HorizontalSizePolicy", toJSONValue(HorizontalSizePolicy));
    object.insert("VerticalSizePolicy", toJSONValue(VerticalSizePolicy));
    object.insert("Visibility", toJSONValue(Visibility));
    object.insert("AffectsParentLayout", toJSONValue(AffectsParentLayout));
}
void View::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Transform", value);
    fromJSONValue(value, Transform);
    value = AJSONValue();
    object.read("Size", value);
    fromJSONValue(value, Size);
    value = AJSONValue();
    object.read("HorizontalSizePolicy", value);
    fromJSONValue(value, HorizontalSizePolicy);
    value = AJSONValue();
    object.read("VerticalSizePolicy", value);
    fromJSONValue(value, VerticalSizePolicy);
    value = AJSONValue();
    object.read("Visibility", value);
    fromJSONValue(value, Visibility);
    value = AJSONValue();
    object.read("AffectsParentLayout", value);
    fromJSONValue(value, AffectsParentLayout);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Math::Transform View::getTransform() const
{
    return this->Transform;
}
void View::setTransform(Math::Transform const &Transform)
{
    this->Transform = Transform;
}
void View::setTransform(Math::Transform &&Transform)
{
    this->Transform = std::move(Transform);
}
Math::IntegerVector View::getSize() const
{
    return this->Size;
}
void View::setSize(Math::IntegerVector const &Size)
{
    this->Size = Size;
}
void View::setSize(Math::IntegerVector &&Size)
{
    this->Size = std::move(Size);
}
UI::SizePolicy View::getHorizontalSizePolicy() const
{
    return this->HorizontalSizePolicy;
}
void View::setHorizontalSizePolicy(UI::SizePolicy const &HorizontalSizePolicy)
{
    this->HorizontalSizePolicy = HorizontalSizePolicy;
}
void View::setHorizontalSizePolicy(UI::SizePolicy &&HorizontalSizePolicy)
{
    this->HorizontalSizePolicy = std::move(HorizontalSizePolicy);
}
UI::SizePolicy View::getVerticalSizePolicy() const
{
    return this->VerticalSizePolicy;
}
void View::setVerticalSizePolicy(UI::SizePolicy const &VerticalSizePolicy)
{
    this->VerticalSizePolicy = VerticalSizePolicy;
}
void View::setVerticalSizePolicy(UI::SizePolicy &&VerticalSizePolicy)
{
    this->VerticalSizePolicy = std::move(VerticalSizePolicy);
}
UI::Visibility View::getVisibility() const
{
    return this->Visibility;
}
void View::setVisibility(UI::Visibility const &Visibility)
{
    this->Visibility = Visibility;
}
void View::setVisibility(UI::Visibility &&Visibility)
{
    this->Visibility = std::move(Visibility);
}
Boolean View::getAffectsParentLayout() const
{
    return this->AffectsParentLayout;
}
void View::setAffectsParentLayout(Boolean const &AffectsParentLayout)
{
    this->AffectsParentLayout = AffectsParentLayout;
}
void View::setAffectsParentLayout(Boolean &&AffectsParentLayout)
{
    this->AffectsParentLayout = std::move(AffectsParentLayout);
}
Math::IntegerVector View::getContentSize() const
{
    return this->ContentSize;
}
Math::IntegerVector View::getMinimalSize() const
{
    return this->MinimalSize;
}
Math::Matrix View::getGlobalMatrix() const
{
    return this->GlobalMatrix;
}
Math::Matrix View::getGraphicsMatrix() const
{
    return this->GraphicsMatrix;
}
Array<UI::View> View::getViews() const
{
    return this->Views;
}
void View::setViews(Array<UI::View> const &Views)
{
    this->Views = Views;
}
void View::setViews(Array<UI::View> &&Views)
{
    this->Views = std::move(Views);
}
Array<Boolean> View::getGestureRecognizers() const
{
    return this->GestureRecognizers;
}
void View::setGestureRecognizers(Array<Boolean> const &GestureRecognizers)
{
    this->GestureRecognizers = GestureRecognizers;
}
void View::setGestureRecognizers(Array<Boolean> &&GestureRecognizers)
{
    this->GestureRecognizers = std::move(GestureRecognizers);
}
PlainReference<UI::ViewComponent> View::getOwner() const
{
    return this->Owner;
}
void View::setOwner(PlainReference<UI::ViewComponent> const &Owner)
{
    this->Owner = Owner;
}
void View::setOwner(PlainReference<UI::ViewComponent> &&Owner)
{
    this->Owner = std::move(Owner);
}
PlainReference<UI::View> View::getParent() const
{
    return this->Parent;
}
void View::setParent(PlainReference<UI::View> const &Parent)
{
    this->Parent = Parent;
}
void View::setParent(PlainReference<UI::View> &&Parent)
{
    this->Parent = std::move(Parent);
}
Boolean View::getNeededLayoutUpdate() const
{
    return this->NeededLayoutUpdate;
}
void View::setNeededLayoutUpdate(Boolean const &NeededLayoutUpdate)
{
    this->NeededLayoutUpdate = NeededLayoutUpdate;
}
void View::setNeededLayoutUpdate(Boolean &&NeededLayoutUpdate)
{
    this->NeededLayoutUpdate = std::move(NeededLayoutUpdate);
}
Boolean View::getNeededGraphicsUpdate() const
{
    return this->NeededGraphicsUpdate;
}
void View::setNeededGraphicsUpdate(Boolean const &NeededGraphicsUpdate)
{
    this->NeededGraphicsUpdate = NeededGraphicsUpdate;
}
void View::setNeededGraphicsUpdate(Boolean &&NeededGraphicsUpdate)
{
    this->NeededGraphicsUpdate = std::move(NeededGraphicsUpdate);
}
Boolean View::getNeededGlobalMatrixUpdate() const
{
    return this->NeededGlobalMatrixUpdate;
}
void View::setNeededGlobalMatrixUpdate(Boolean const &NeededGlobalMatrixUpdate)
{
    this->NeededGlobalMatrixUpdate = NeededGlobalMatrixUpdate;
}
void View::setNeededGlobalMatrixUpdate(Boolean &&NeededGlobalMatrixUpdate)
{
    this->NeededGlobalMatrixUpdate = std::move(NeededGlobalMatrixUpdate);
}
Boolean View::getNeededGraphicsMatrixUpdate() const
{
    return this->NeededGraphicsMatrixUpdate;
}
void View::setNeededGraphicsMatrixUpdate(Boolean const &NeededGraphicsMatrixUpdate)
{
    this->NeededGraphicsMatrixUpdate = NeededGraphicsMatrixUpdate;
}
void View::setNeededGraphicsMatrixUpdate(Boolean &&NeededGraphicsMatrixUpdate)
{
    this->NeededGraphicsMatrixUpdate = std::move(NeededGraphicsMatrixUpdate);
}
//CLASSGEN END REGION
*/

Math::Matrix PerspectiveCamera::getViewMatrix() const
{
    Math::Matrix viewMatrix = APerspectiveCamera::getViewMatrix();
    return viewMatrix;
}

Math::Matrix PerspectiveCamera::getProjectionMatrix() const
{
    Math::Matrix perspectiveMatrix = APerspectiveCamera::getProjectionMatrix();
    auto inverseHalfHeightResolution = 1 / resolution.getHalfY();
    auto aspectRatio = resolution.getXYAspectRatio();

    Math::Matrix yAxisInversion = Math::Matrix::getScale2({ 1.0f, -1.0f });
    Math::Matrix perspectiveScreenFit = Math::Matrix::getTranslation({ -aspectRatio, -1.0f, -perspectiveMatrix[1][1] });
    Math::Matrix scaleFit = Math::Matrix::getScale3({ inverseHalfHeightResolution, inverseHalfHeightResolution, inverseHalfHeightResolution });

    Math::Matrix viewMatrix = APerspectiveCamera::getViewMatrix();

    return viewMatrix.getInversed() * scaleFit * perspectiveScreenFit * viewMatrix * perspectiveMatrix * yAxisInversion;
}

ConsoleVariable<bool> UILayoutCalls{ false, "UI.LayoutCalls" };
ConsoleVariable<bool> UIDrawCalls{ false, "UI.DrawCalls" };
ConsoleVariable<float> UIDepth{ false, "UI.Depth" };
ConsoleVariable<bool> UIForceUpdate{ false, "UI.ForceUpdate" };

void CaptureViewHierarchy()
{
    struct Controller : public UI::FlexBox, public UI::TreeAdapter<UI::View>
    {
        struct DebugView : public View
        {
            using Super = View;
            View *view = nullptr;
            void onDraw(AUpdateEvent &event) override
            {
                Super::onDraw(event);
                UIVisualDebug().drawMeshWireframe(view->getGraphicsMatrix(), UI::Component::getSprite(), AColor(AColorName::Magenta));
            }
        };

        Array<View *> views;
        SharedReference<UI::Window> window;
        SharedReference<UI::Window> window2;

        SharedReference<UI::TreeView<UI::View>> hierarchy;

        struct PropertyController : public UI::ListView, public UI::ItemAdapter
        {
            Array<String> data;
            UI::SizeType getCountItems(const AObject &sender) const override { return data.size(); }
            SharedReference<View> provideViewForItem(const AObject &sender, UI::SizeType index) override { return CreateShared<UI::Label>(data[index]); }
        };

        SharedReference<PropertyController> propertyController = CreateShared<PropertyController>();

        SharedReference<DebugView> debugView = CreateShared<DebugView>();

        void onLoad(ALoadEvent &event)
        {
            Super::onLoad(event);

            hierarchy = CreateShared<UI::TreeView<UI::View>>();

            setSizePolicy(SizePolicy::Expanded);
            hierarchy->setSizePolicy(SizePolicy::Expanded);
            propertyController->setSizePolicy(SizePolicy::Expanded);

            setData({ {}, {} });

            addView(hierarchy);
            addView(propertyController);

            propertyController->setAdapter(propertyController.get());
            hierarchy->setProxyAdapter(this);
        }

        SharedReference<UI::View> dummy = CreateShared<UI::View>();

        UI::SizeType getCountRootItems() const override
        {
            auto windows = AWindow::getWindows();
            return windows.size();
        }
        UI::View *getRootItem(UI::SizeType index) override
        {
            auto windows = AWindow::getWindows();
            UI::Window *uiWindow = dynamic_cast<UI::Window *>(windows[index]);
            return uiWindow ? uiWindow->getView().get() : dummy.get();
        }
        UI::SizeType getCountChildItems(UI::View *parentItem) const override
        {
            return parentItem->debug_Expanded ? parentItem->getViews().size() : 0;
        }

        UI::View *getChildItem(UI::View *parentItem, UI::SizeType index) override
        {
            return parentItem->getViews()[index].get();
        }

        SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType depth, UI::View *item) override
        {
            String title = item->getName() + " : " + AMeta::getDynamicTypeName(*item);

            UI::DefaultExpandableItemView *itemView = Create<UI::DefaultExpandableItemView>();
            itemView->applyParameters(depth, title, item->getViews().size());
            SharedReference<UI::DefaultExpandableItemView> sharedView = SharedReference<UI::DefaultExpandableItemView>(itemView);
            itemView->setItemExpanded(item->debug_Expanded);
            itemView->expandButton->eventChannel.registerDelegate<UI::TapGestureEvent>([this, itemView, item](UI::TapGestureEvent &event) {
                item->debug_Expanded = !item->debug_Expanded;
                itemView->setItemExpanded(item->debug_Expanded);
                UIApplication::getOperationDispatcher().addDelegate([this, item]() {
                    hierarchy->notifyUpdateChildren(item);
                    return AError::getEmptyError();
                }, true);
            });
            return sharedView;
        }

        void onItemTapped(const AObject &sender, UI::TapGestureEvent &event, UI::View *item) override
        {
            debugView->removeFromParent();
            debugView->view = item;
            debugView->view->getOwner()->getView()->addView(debugView);

            AJSONObject data;
            debugView->view->serialize(data);
            propertyController->data.clear();
            for (const APair<String, AJSONValue> &value : data)
            {
                String text = value.first + ": " + value.second.toString(AJSONWriteOption::Comapct);
                boost::replace_all(text, "\n", ""); //TODO: remove
                boost::replace_all(text, "\t", ""); //TODO: remove
                propertyController->data.push_back(text);
            }

            propertyController->notifyUpdateAllItems();
        }
    };

    static SharedReference<Controller> controller = CreateShared<Controller>();
    controller->window = nullptr;

    auto windows = AWindow::getWindows();
    controller->views.clear();
    controller->views.resize(windows.size());

    Math::IntegerRectangle geometry = Math::getCenteredRectangle(Math::IntegerVector{ 1920, 1080 }, Math::IntegerVector{ 1800, 1000 });

    controller->window = CreateShared<UI::Window>();
    controller->window->setBackgroundColor(AColor(0.15));
    controller->window->setGeometry(geometry);
    controller->window->setView(controller);
    controller->window->show();

    geometry.Position.X += 1800;
    controller->window2 = CreateShared<UI::Window>();
    controller->window2->setGeometry(geometry);

    auto root = CreateShared<UI::View>();
    root->setPosition(controller->window2->getGeometry().Size.getHalf2());

    class ViewProxy : public UI::View 
    {
    public:
        using Super = UI::View;

        UI::View* Target = nullptr;

        void onDraw(AUpdateEvent &event) override
        {
            float d = UIDepth;
            UIDepth = 100.0f;
            bool drawCalls = UIDrawCalls;
            UIDrawCalls = true;
            Super::onDraw(event);
            Target->sendEvent(event);
            UIDrawCalls = drawCalls;
            UIDepth = d;
        }
    };
    UIForceUpdate = true;

    AWindow *w = AWindow::getWindows()[0];
    if (UI::Window *uiw = dynamic_cast<UI::Window*>(w))
    {
        auto proxy = CreateShared<ViewProxy>();
        proxy->Target = StaticCast<UI::Component>(uiw->getRootComponent())->getView().get();
        root->addView(proxy);
    }

    controller->window2->setView(root);
    controller->window2->show();

    static APerspectiveCamera camera;
    static AFreeCameraInputController freeCameraController(*controller->window2, controller->window2->getRootCamera());
    freeCameraController.xAxisSensetivity *= -1;
}

AStaticRun(ViewMetaObject)
{
    CLASSGEN_GENERATED_REGION_META_OBJECT
        MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<View>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const View&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<View&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<AObject>();
    object.registerMetaProperty<View, Component *>("Owner", &View::getOwner, static_cast<void(View::*)(Component * const &)>(nullptr), false);
    object.registerMetaProperty<View, View *>("Parent", &View::getParent, static_cast<void(View::*)(View * const &)>(nullptr), false);
    object.registerMetaProperty<View, SharedReference<Layout>>("Layout", &View::getLayout, &View::setLayout, false);
    object.registerMetaProperty<View, Math::Vector>("Position", &View::getPosition, &View::setPosition, true);
    object.registerMetaProperty<View, Math::Quaternion>("Rotation", &View::getRotation, &View::setRotation, true);
    object.registerMetaProperty<View, Math::Transform>("Transform", &View::getTransform, &View::setTransform, false);
    object.registerMetaProperty<View, Math::IntegerVector>("Size", &View::getSize, &View::setSize, true);
    object.registerMetaProperty<View, Math::IntegerVector>("ContentSize", &View::getContentSize, static_cast<void(View::*)(Math::IntegerVector const &)>(nullptr), false);
    object.registerMetaProperty<View, Math::IntegerVector>("MinimalSize", &View::getMinimalSize, static_cast<void(View::*)(Math::IntegerVector const &)>(nullptr), true);
    object.registerMetaProperty<View, int32_t>("BaseLine", &View::getBaseLine, static_cast<void(View::*)(int32_t)>(nullptr), false);
    object.registerMetaProperty<View, bool>("Loaded", &View::isLoaded, static_cast<void(View::*)(bool)>(nullptr), false);
    object.registerMetaProperty<View, Visibility>("Visibility", &View::getVisibility, &View::setVisibility, true);
    object.registerMetaProperty<View, bool>("AffectsParentLayout", &View::getAffectsParentLayout, &View::setAffectsParentLayout, false);
    object.registerMetaProperty<View, bool>("NeededUpdateParentLayout", &View::isNeededUpdateParentLayout, static_cast<void(View::*)(bool)>(nullptr), false);
    object.registerMetaProperty<View, bool>("NeededLayoutUpdate", &View::isNeededLayoutUpdate, static_cast<void(View::*)(bool)>(nullptr), false);
    object.registerMetaProperty<View, bool>("NeededGraphicsUpdate", &View::isNeededGraphicsUpdate, static_cast<void(View::*)(bool)>(nullptr), false);
    object.registerMetaProperty<View, Math::Matrix>("GlobalMatrix", &View::getGlobalMatrix, &View::setGlobalMatrix, false);
    object.registerMetaProperty<View, Math::Matrix>("GraphicsMatrix", &View::getGraphicsMatrix, &View::setGraphicsMatrix, false);
    object.registerMetaProperty<View, SizePolicy>("HorizontalSizePolicy", &View::getHorizontalSizePolicy, &View::setHorizontalSizePolicy, true);
    object.registerMetaProperty<View, SizePolicy>("VerticalSizePolicy", &View::getVerticalSizePolicy, &View::setVerticalSizePolicy, true);
    object.registerMetaProperty<View, Array<SharedReference<View>>>("Views", &View::getViews, static_cast<void(View::*)(Array<SharedReference<View>> const &)>(nullptr), false);
    object.registerMetaProperty<View, Array<SharedReference<GestureRecognizer>>>("GestureRecognizers", &View::getGestureRecognizers, static_cast<void(View::*)(Array<SharedReference<GestureRecognizer>> const &)>(nullptr), false);
    manager.registerMetaObject("UI.View", object);
    CLASSGEN_END_REGION

        manager.enums[AMeta::getStaticTypeHash<SizePolicy>()] = {
        "Fixed",
        "Expanded",
        "ContentWrapped"
    };

    Console::getInstance().addCommand("Debug.CaptureViewHierarchy", [](const Array<String> &arguments) {
        CaptureViewHierarchy();
    });

    Console::getInstance().addCommand("Debug.CountObjects", [](const Array<String> &args) {
        Map<size_t, APair<String, size_t>> objs;
        fmt::print("Allocated Objects: {}\r\n", MetaObjectInformation::getInstance().allocatedObjects.size());
        for (Serializable *serializable : MetaObjectInformation::getInstance().allocatedObjects)
        {
            auto &typeData = objs[typeid(*serializable).hash_code()];
            if (typeData.first.empty())
            {
                typeData.first = typeid(*serializable).name();
            }
            ++typeData.second;
        }
        for (auto &pair : objs)
        {
            fmt::print("{} {}\r\n", pair.second.first.data(), pair.second.second);
        }
    });

    Console::getInstance().addCommand("Debug.ViewObjects", [](const Array<String> &args) {
        class TreeStringItem
        {
        public:
            Array<SharedReference<TreeStringItem>> items;
            String title;
            bool isExpanded = false;
        };

        struct TreeViewController : public UI::TreeView<TreeStringItem>, public UI::TreeAdapter<TreeStringItem>
        {
        public:

            TreeViewController()
            {
                setProxyAdapter(this);
            }

            Array<SharedReference<TreeStringItem>> items;

            UI::SizeType getCountRootItems() const override
            {
                return items.size();
            }

            TreeStringItem *getRootItem(UI::SizeType index) override
            {
                return items[index].get();
            }

            UI::SizeType getCountChildItems(TreeStringItem *parentItem) const override
            {
                return parentItem->isExpanded ? parentItem->items.size() : 0;
            }

            TreeStringItem *getChildItem(TreeStringItem *parentItem, UI::SizeType index) override
            {
                return parentItem->items[index].get();
            }

            SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType depth, TreeStringItem *item) override
            {
                UI::DefaultTreeItemView *itemView = new UI::DefaultTreeItemView(depth, item->title, item->items.size());
                SharedReference<UI::DefaultTreeItemView> sharedView = SharedReference<UI::DefaultTreeItemView>(itemView);
                itemView->expandButton->setText(item->isExpanded ? "-" : "+");
                itemView->expandButton->eventChannel.registerDelegate<UI::TapGestureEvent>([this, itemView, item](UI::TapGestureEvent &event) {
                    if (item->isExpanded)
                    {
                        item->isExpanded = false;
                        itemView->expandButton->setText("+");
                    }
                    else
                    {
                        item->isExpanded = true;
                        itemView->expandButton->setText("-");
                    }
                    UIApplication::getOperationDispatcher().addDelegate([this, item]() {
                        notifyUpdateChildren(item);
                        return AError::getEmptyError();
                    }, true);
                });
                return sharedView;
            }
        };

        Map<size_t, SharedReference<TreeStringItem>> classes;
        //printf("Allocated Objects: %d\r\n", MetaObjectInformation::getInstance().allocatedObjects.size());
        for (Serializable *serializable : MetaObjectInformation::getInstance().allocatedObjects)
        {
            auto &classItem = classes[typeid(*serializable).hash_code()];
            if (!classItem)
            {
                classItem = CreateShared<TreeStringItem>();
            }
            if (classItem->title.empty())
            {
                classItem->title = typeid(*serializable).name();
            }
            SharedReference<TreeStringItem> objectItem = CreateShared<TreeStringItem>();
            objectItem->title = fmt::format("{}", fmt::ptr(serializable));
            classItem->items.push_back(objectItem);
        }

        static SharedReference<UI::Window> window = CreateShared<UI::Window>();
        SharedReference<TreeViewController> tree = CreateShared<TreeViewController>();
        size_t j = 0;
        for (auto &pair : classes)
        {
            pair.second->title = fmt::format("{} ({})", pair.second->title, pair.second->items.size());
            tree->items.push_back(pair.second);
        }
        tree->notifyUpdateAllItems();
        tree->setSize({ 200, 800 });
        window->setView(tree);
        window->setGeometry(Math::IntegerRectangle{ { 100, 100 }, { 200, 800 } });
        window->show();
    });
}

CLASSGEN_GENERATED_REGION_OBJECT
void View::serialize(AJSONObject &object) const
{
    object.insert("Transform", toJSONValue(getTransform()));
    object.insert("Size", toJSONValue(size));
    object.insert("MinimalSize", toJSONValue(minimalSize));
    object.insert("Enabled", toJSONValue(enabled));
    object.insert("Visible", toJSONValue(visible));
    object.insert("Expanded", toJSONValue(expanded));
    object.insert("VerticalSizePolicy", toJSONValue(verticalSizePolicy));
    object.insert("HorizontalSizePolicy", toJSONValue(horizontalSizePolicy));
    object.insert("AffectsParentLayout", toJSONValue(affectsParentLayout));
}
void View::deserialize(const AJSONObject &object)
{
    AJSONValue value;

    value = AJSONValue();
    object.read("Transform", value);
    Math::Transform transform;
    fromJSONValue(value, transform);
    setTransform(transform);

    value = AJSONValue();
    object.read("Size", value);
    fromJSONValue(value, size);

    value = AJSONValue();
    object.read("MinimalSize", value);
    fromJSONValue(value, minimalSize);

    value = AJSONValue();
    object.read("Enabled", value);
    fromJSONValue(value, enabled);

    value = AJSONValue();
    object.read("Visible", value);
    fromJSONValue(value, visible);

    value = AJSONValue();
    object.read("Expanded", value);
    fromJSONValue(value, expanded);

    value = AJSONValue();
    object.read("VerticalSizePolicy", value);
    fromJSONValue(value, verticalSizePolicy);

    value = AJSONValue();
    object.read("HorizontalSizePolicy", value);
    fromJSONValue(value, horizontalSizePolicy);

    value = AJSONValue();
    object.read("AffectsParentLayout", value);
    fromJSONValue(value, affectsParentLayout);

}
Component * View::getOwner() const
{
    return this->owner;
}
View * View::getParent() const
{
    return this->parent;
}
SharedReference<Layout> const &View::getLayout() const
{
    return this->layout;
}
Math::Transform View::getTransform() const
{
    return this->transform;
}
void View::setTransform(Math::Transform const &transform)
{
    this->transform = transform;
    requestMatrixUpdate();
    requestLayoutUpdate();
}
Math::IntegerVector const &View::getSize() const
{
    return this->size;
}
bool View::isLoaded() const
{
    return this->loaded;
}
bool View::isNeededLayoutUpdate() const
{
    return this->neededLayoutUpdate;
}
bool View::isNeededGraphicsUpdate() const
{
    return this->neededGraphicsUpdate;
}
void View::setGlobalMatrix(Math::Matrix const &globalMatrix)
{
    this->globalMatrix = globalMatrix;
}
void View::setGraphicsMatrix(Math::Matrix const &graphicsMatrix)
{
    this->graphicsMatrix = graphicsMatrix;
}
SizePolicy View::getHorizontalSizePolicy() const
{
    return this->horizontalSizePolicy;
}
void View::setHorizontalSizePolicy(SizePolicy const &horizontalSizePolicy)
{
    this->horizontalSizePolicy = horizontalSizePolicy;
    requestLayoutUpdate();
}
SizePolicy View::getVerticalSizePolicy() const
{
    return this->verticalSizePolicy;
}
void View::setVerticalSizePolicy(SizePolicy const &verticalSizePolicy)
{
    this->verticalSizePolicy = verticalSizePolicy;
    requestLayoutUpdate();
}
Array<SharedReference<View>> const &View::getViews() const
{
    return this->views;
}
Array<SharedReference<GestureRecognizer>> const &View::getGestureRecognizers() const
{
    return this->gestureRecognizers;
}
CLASSGEN_END_REGION

const Math::Vector &View::getPosition() const
{
    return this->transform.Position;
}

void View::setPosition(const Math::Vector &position)
{
    if (this->transform.Position.x == position.x &&
        this->transform.Position.y == position.y &&
        this->transform.Position.z == position.z)
    {
        return;
    }
    this->transform.Position = position;
    requestMatrixUpdate();
    if (parent)
    {
        if (isNeededUpdateParentLayout())
        {
            parent->requestLayoutUpdate();
        }
        parent->requestGraphicsUpdate();
    }
}

const Math::Quaternion &View::getRotation() const
{
    return this->transform.Rotation;
}

void View::setRotation(const Math::Quaternion &rotation)
{
    this->transform.Rotation = rotation;
    requestMatrixUpdate();
    if (parent)
    {
        if (isNeededUpdateParentLayout())
        {
            parent->requestLayoutUpdate();
        }
        parent->requestGraphicsUpdate();
    }
}

void View::setSize(const Math::IntegerVector &size)
{
    if (this->size.x == size.x && this->size.y == size.y)
    {
        return;
    }
    this->size = size;
    requestLayoutUpdate();
    requestMatrixUpdate();
    requestGraphicsUpdate();
}

void View::setLayout(const SharedReference<Layout> &layout)
{
    AAssert(this->layout != layout, "Layout is already set");
    if (this->layout)
    {
        this->layout->unload();
    }
    this->layout = layout;
    if (this->layout)
    {
        this->layout->load(*this);
    }
    requestUpdate();
}

Math::IntegerVector View::getContentSize() const
{
    if (layout)
    {
        return layout->getContentSize();
    }

    if (views.empty())
    {
        return Math::IntegerVector{};
    }

    Math::IntegerVector topLeft = Math::IntegerVector{ std::numeric_limits<int32_t>::max(), std::numeric_limits<int32_t>::max() };
    Math::IntegerVector bottomRight = Math::IntegerVector{ std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::min() };
    for (auto &view : views)
    {
        if (view->getVisibility() & Visibility::Hidden)
        {
            continue;
        }

        const Math::Vector position = view->getPosition();
        const Math::IntegerVector size = view->getMinimalSize();

        topLeft.x = std::min<int32_t>(topLeft.x, position.x);
        topLeft.y = std::min<int32_t>(topLeft.y, position.y);
        bottomRight.x = std::max<int32_t>(bottomRight.x, position.x + size.x);
        bottomRight.y = std::max<int32_t>(bottomRight.y, position.y + size.y);
    }
    return Math::IntegerVector{ bottomRight.x/* - topLeft.x*/, bottomRight.y/* - topLeft.y*/ };
    //TODO: optimize
    /*Math::IntegerVector contentSize;
    for (auto &view : views)
    {
        if (!view->isExpanded())
        {
            continue;
        }

        contentSize.x = std::max<int32_t>(contentSize.x, view->getMinimalSize().x);
        contentSize.y = std::max<int32_t>(contentSize.y, view->getMinimalSize().y);
    }
    return contentSize;*/
}

int32_t View::getBaseLine() const
{
    return getSize().y;
}

Math::IntegerVector View::getMinimalSize() const
{
    Math::IntegerVector minimalSize{};

    if (!isExpanded())
    {
        return minimalSize;
    }

    Math::IntegerVector contentSize = getContentSize();
    switch (horizontalSizePolicy)
    {
    case SizePolicy::ContentWrapped:
    case SizePolicy::Expanded:
        minimalSize.x = contentSize.x;
        break;
    case SizePolicy::Fixed:
        minimalSize.x = getSize().x;
        break;
    }
    switch (verticalSizePolicy)
    {
    case SizePolicy::ContentWrapped:
    case SizePolicy::Expanded:
        minimalSize.y = contentSize.y;
        break;
    case SizePolicy::Fixed:
        minimalSize.y = getSize().y;
        break;
    }
    return minimalSize;
}

Math::IntegerVector View::getPreferedSize(const Math::IntegerVector &size) const
{
    Math::IntegerVector preferedSize = getMinimalSize();

    if (!isExpanded())
    {
        return preferedSize;
    }

    if (horizontalSizePolicy == SizePolicy::Expanded)
    {
        preferedSize.x = std::max<int32_t>(preferedSize.x, size.x);
    }
    if (verticalSizePolicy == SizePolicy::Expanded)
    {
        preferedSize.y = std::max<int32_t>(preferedSize.y, size.y);
    }
    return preferedSize;
}

const Math::Matrix &View::getGlobalMatrix() const
{
    if (neededGlobalMatrixUpdate || UIForceUpdate)
    {
        globalMatrix = transform.getMatrix();
        if (this->parent)
        {
            globalMatrix = globalMatrix * this->parent->getGlobalMatrix();
            if (UIDepth > 0.0f)
            {
                globalMatrix = globalMatrix.getTranslated({ 0, 0, UIDepth });
            }
        }
        neededGlobalMatrixUpdate = false;
    }

    return globalMatrix;
}

const Math::Matrix &View::getGraphicsMatrix() const
{
    if (neededGraphicsMatrixUpdate || UIForceUpdate)
    {
        graphicsMatrix = Math::Matrix::getScale2(getSize().getXY<Math::Vector>()) * getGlobalMatrix();
        neededGraphicsMatrixUpdate = false;
    }

    return graphicsMatrix;
}

void View::load()
{
    if (!loaded && this->owner && this->owner->getWindow())
    {
        ALoadEvent e(*this);
        sendEvent(e);
    }
}

void View::unload()
{
    if (loaded && this->owner && this->owner->getWindow())
    {
        AUnloadEvent e(*this);
        sendEvent(e);
    }
}

void View::updateOwners(Component *owner)
{
    unload();
    processOwners(owner);
    load();
}

void View::processOwners(Component *owner)
{
    AAssert(!loaded, "View should be unloaded");
    this->owner = owner;
    for (auto &view : views)
    {
        view->processOwners(this->owner);
    }
}

void View::onLoad(ALoadEvent &event)
{
    if (loaded)
    {
        return;
    }

    for (auto &view : views)
    {
        view->sendEvent(event);
    }

    for (auto &gestureRecognizer : gestureRecognizers)
    {
        gestureRecognizer->load(*this);
    }

    loaded = true;
}

void View::onUnload(AUnloadEvent &event)
{
    if (!loaded)
    {
        return;
    }

    for (auto &view : views)
    {
        view->sendEvent(event);
    }

    for (auto &gestureRecognizer : gestureRecognizers)
    {
        gestureRecognizer->unload();
    }

    loaded = false;
}

void View::updateViews(AUpdateEvent &event)
{
    for (auto &view : views)
    {
        view->onUpdate(event);
    }
}

void View::onUpdate(AUpdateEvent &event)
{
    if (isOutside || !(isVisible() && isExpanded()))
    {
        return;
    }

    bool isInside = true;
    if(getOwner())
    {
        if (CullingData[getOwner()->getWindow()].size() > 0)
        {
            auto rect = Math::IntegerRectangle{
                mapFromLocalSpaceToScreenSpace(*this, Math::Vector{}),
                mapFromLocalSpaceToScreenSpace(*this, getSize())
            };

            auto overlapRectangles = [](const Math::IntegerRectangle &r1, const Math::IntegerRectangle &r2) {
                if (r1.getTop() > r2.getBottom() || r1.getBottom() < r2.getTop())
                {
                    return false;
                }
                if (r1.getRight() < r2.getLeft() || r1.getLeft() > r2.getRight())
                {
                    return false;
                }

                return true;
                /*return r1.getLeft() < r2.getRight() && r1.getRight() > r2.getLeft() &&
                    r1.getTop() > r2.getBottom() && r1.getBottom() < r2.getTop();*/
            };

            isInside = overlapRectangles(rect, CullingData[getOwner()->getWindow()].back());
        }

        if (CullViews)
        {
            CullingData[getOwner()->getWindow()].push_back(Math::IntegerRectangle{
                mapFromLocalSpaceToScreenSpace(*this, Math::Vector{}),
                mapFromLocalSpaceToScreenSpace(*this, getSize())
            });
        }
    }
    else
    {
        isInside = true;
    }
    
    if (neededLayoutUpdate)
    {
        if (CullViews)
        {
            auto parentGeometry = Math::IntegerRectangle{ Math::IntegerVector{}, getSize() };
        }
        onLayout(event);
    }

    if (isInside)
    {
        onDraw(event);
    }

    updateViews(event);
    
    if(getOwner())
    {
        if (CullViews)
        {
            CullingData[getOwner()->getWindow()].pop_back();
        }
    }
}

void View::onLayout(AUpdateEvent &event)
{
    if (layout)
    {
        layout->onLayout(*this);
    }
    neededLayoutUpdate = false;
    if (UILayoutCalls)
    {
        UIVisualDebug().drawMeshWireframe(getGraphicsMatrix(), Component::getSprite(), AColor(AColorName::Yellow));
    }
}

void View::onDraw(AUpdateEvent &event)
{
    neededGraphicsUpdate = false;
    if (UIDrawCalls)
    {
        UIVisualDebug().drawMeshSurface(getGraphicsMatrix(), Component::getSprite(), AColor(0.1f, 0.1f, 0.1f, 1.0f));
        UIVisualDebug().drawMeshWireframe(getGraphicsMatrix(), Component::getSprite(), AColor(1.0f, 0.0f, 0.0f, 1.0f));
    }
}


//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
