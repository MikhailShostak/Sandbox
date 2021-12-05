#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "Foundation"
#include "ViewComponent.gen.h"

//CLASSGEN END REGION
#include "MetaObjectSerializationHelper.h"

#include "Core/ACommonEvents.h"
#include "UI/UILayout.h"
#include "UI/GestureRecognizers/UIGestureRecognizer.h"

#include "Includes/SizePolicy.gen.h"
#include "Includes/Visibility.gen.h"

/*class UILayoutRule
{
ADelegate<bool(UILayoutRule &rule, const Array<SharedReference<UIView>> &views)> condition;
ADelegate<void(UILayoutRule &rule, const Array<SharedReference<UIView>> &views)> logic;
const Array<SharedReference<UIView>> &views;
public:

UILayoutRule(const ADelegate<void(UILayoutRule &rule, const Array<SharedReference<UIView>> &views)> &logic, const Array<SharedReference<UIView>> &views = Array<SharedReference<UIView>>::EmptyArray()):
logic(logic),
views(views){}

UILayoutRule(const ADelegate<bool(UILayoutRule &rule, const Array<SharedReference<UIView>> &views)> &condition, const ADelegate<void(UILayoutRule &rule, const Array<SharedReference<UIView>> &views)> &logic, const Array<SharedReference<UIView>> &views = Array<SharedReference<UIView>>::EmptyArray()):
condition(condition),
logic(logic),
views(views)
{}

void apply()
{
AAssert(logic, "Invalid layout rule, logic is not set");
if(condition)
{
if(condition(*this, views))
{
logic(*this, views);
}
}
else
{
logic(*this, views);
}
}
};*/

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
class ViewComponent; //TODO: implement generation of implicit declaration
/*
//CLASSGEN GENERATED REGION: ClassHeader
class View : public AObject
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef View This;
    typedef AObject Super;
    typedef void Interfaces;
protected:
    Math::Transform Transform;
Math::IntegerVector Size;
UI::SizePolicy HorizontalSizePolicy;
UI::SizePolicy VerticalSizePolicy;
UI::Visibility Visibility;
Boolean AffectsParentLayout;
Math::IntegerVector ContentSize;
Math::IntegerVector MinimalSize;
Math::Matrix GlobalMatrix;
Math::Matrix GraphicsMatrix;
Array<UI::View> Views;
Array<Boolean> GestureRecognizers;
PlainReference<UI::ViewComponent> Owner;
PlainReference<UI::View> Parent;
Boolean NeededLayoutUpdate;
Boolean NeededGraphicsUpdate;
Boolean NeededGlobalMatrixUpdate;
Boolean NeededGraphicsMatrixUpdate;
public:
    View();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Math::Transform getTransform() const;
    void setTransform(Math::Transform const &Transform);
    void setTransform(Math::Transform &&Transform);
    Math::IntegerVector getSize() const;
    void setSize(Math::IntegerVector const &Size);
    void setSize(Math::IntegerVector &&Size);
    UI::SizePolicy getHorizontalSizePolicy() const;
    void setHorizontalSizePolicy(UI::SizePolicy const &HorizontalSizePolicy);
    void setHorizontalSizePolicy(UI::SizePolicy &&HorizontalSizePolicy);
    UI::SizePolicy getVerticalSizePolicy() const;
    void setVerticalSizePolicy(UI::SizePolicy const &VerticalSizePolicy);
    void setVerticalSizePolicy(UI::SizePolicy &&VerticalSizePolicy);
    UI::Visibility getVisibility() const;
    void setVisibility(UI::Visibility const &Visibility);
    void setVisibility(UI::Visibility &&Visibility);
    Boolean getAffectsParentLayout() const;
    void setAffectsParentLayout(Boolean const &AffectsParentLayout);
    void setAffectsParentLayout(Boolean &&AffectsParentLayout);
    Math::IntegerVector getContentSize() const;
    Math::IntegerVector getMinimalSize() const;
    Math::Matrix getGlobalMatrix() const;
    Math::Matrix getGraphicsMatrix() const;
    Array<UI::View> getViews() const;
    void setViews(Array<UI::View> const &Views);
    void setViews(Array<UI::View> &&Views);
    Array<Boolean> getGestureRecognizers() const;
    void setGestureRecognizers(Array<Boolean> const &GestureRecognizers);
    void setGestureRecognizers(Array<Boolean> &&GestureRecognizers);
    PlainReference<UI::ViewComponent> getOwner() const;
    void setOwner(PlainReference<UI::ViewComponent> const &Owner);
    void setOwner(PlainReference<UI::ViewComponent> &&Owner);
    PlainReference<UI::View> getParent() const;
    void setParent(PlainReference<UI::View> const &Parent);
    void setParent(PlainReference<UI::View> &&Parent);
    Boolean getNeededLayoutUpdate() const;
    void setNeededLayoutUpdate(Boolean const &NeededLayoutUpdate);
    void setNeededLayoutUpdate(Boolean &&NeededLayoutUpdate);
    Boolean getNeededGraphicsUpdate() const;
    void setNeededGraphicsUpdate(Boolean const &NeededGraphicsUpdate);
    void setNeededGraphicsUpdate(Boolean &&NeededGraphicsUpdate);
    Boolean getNeededGlobalMatrixUpdate() const;
    void setNeededGlobalMatrixUpdate(Boolean const &NeededGlobalMatrixUpdate);
    void setNeededGlobalMatrixUpdate(Boolean &&NeededGlobalMatrixUpdate);
    Boolean getNeededGraphicsMatrixUpdate() const;
    void setNeededGraphicsMatrixUpdate(Boolean const &NeededGraphicsMatrixUpdate);
    void setNeededGraphicsMatrixUpdate(Boolean &&NeededGraphicsMatrixUpdate);
//CLASSGEN END REGION
*/
class Component;
class View;

class View : public AObject
{
    CLASSGEN_GENERATED_REGION_OBJECT
public:
    typedef View This;
    typedef AObject Super;
private:
    Component * owner = nullptr;
    View * parent = nullptr;
    SharedReference<Layout> layout;
public:
    AEventChannel eventChannel;
private:
    Math::Transform transform;
    Math::IntegerVector size;
    Math::IntegerVector contentSize;
    Math::IntegerVector minimalSize;
    int32_t baseLine;
    bool loaded = false;
    bool enabled = true;
    bool visible = true;
    bool expanded = true;
    bool neededLayoutUpdate = true;
    bool neededGraphicsUpdate = true;
    mutable bool neededGlobalMatrixUpdate = true;
    mutable bool neededGraphicsMatrixUpdate = true;
protected:
    bool CullViews = false;
private:
    mutable bool isOutside = false;
    mutable Math::Matrix globalMatrix;
    mutable Math::Matrix graphicsMatrix;
    SizePolicy horizontalSizePolicy = SizePolicy::Expanded;
    SizePolicy verticalSizePolicy = SizePolicy::ContentWrapped;
    Array<SharedReference<View>> views;
    Array<SharedReference<GestureRecognizer>> gestureRecognizers;
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
    virtual Component * getOwner() const;
    virtual View * getParent() const;
    virtual SharedReference<Layout> const &getLayout() const;
    virtual void setLayout(SharedReference<Layout> const &layout);
    virtual Math::Vector const &getPosition() const;
    virtual void setPosition(Math::Vector const &position);
    virtual Math::Quaternion const &getRotation() const;
    virtual void setRotation(Math::Quaternion const &rotation);
    virtual Math::Transform getTransform() const;
    virtual void setTransform(Math::Transform const &transform);
    virtual Math::IntegerVector const &getSize() const;
    virtual void setSize(Math::IntegerVector const &size);
    virtual Math::IntegerVector getContentSize() const;
    virtual Math::IntegerVector getMinimalSize() const;
    virtual int32_t getBaseLine() const;
    virtual bool isLoaded() const;
    virtual bool isNeededLayoutUpdate() const;
    virtual bool isNeededGraphicsUpdate() const;
    virtual Math::Matrix const &getGlobalMatrix() const;
    virtual void setGlobalMatrix(Math::Matrix const &globalMatrix);
    virtual Math::Matrix const &getGraphicsMatrix() const;
    virtual void setGraphicsMatrix(Math::Matrix const &graphicsMatrix);
    virtual SizePolicy getHorizontalSizePolicy() const;
    virtual void setHorizontalSizePolicy(SizePolicy const &horizontalSizePolicy);
    virtual SizePolicy getVerticalSizePolicy() const;
    virtual void setVerticalSizePolicy(SizePolicy const &verticalSizePolicy);
    virtual Array<SharedReference<View>> const &getViews() const;
    virtual Array<SharedReference<GestureRecognizer>> const &getGestureRecognizers() const;
    CLASSGEN_END_REGION
        Visibility visibility;
    uint8_t layoutCount = 0;
public:
    bool debug_Expanded = false;
    bool getNeededLayoutUpdate() const { return neededLayoutUpdate; }
    void setNeededLayoutUpdate(bool value) { neededLayoutUpdate = value; }
    bool getNeededGraphicsUpdate() const { return neededGraphicsUpdate; }
    void setNeededGraphicsUpdate(bool value) { neededGraphicsUpdate = value; }
    bool getNeededGlobalMatrixUpdate() const { return neededGlobalMatrixUpdate; }
    void setNeededGlobalMatrixUpdate(bool value) { neededGlobalMatrixUpdate = value; }
    bool getNeededGraphicsMatrixUpdate() const { return neededGraphicsMatrixUpdate; }
    void setNeededGraphicsMatrixUpdate(bool value) { neededGraphicsMatrixUpdate = value; }

    Visibility getVisibility() const { return visibility; }
    void setVisibility(Visibility visibility)
    {
        if (this->visibility.value == visibility.value) //TODO: remove value
        {
            return;
        }

        this->visibility = visibility;

        if (parent)
        {
            if (isNeededUpdateParentLayout())
            {
                parent->requestLayoutUpdate();
            }
            parent->requestGraphicsUpdate();
        }
    }

    void addVisibility(Visibility visibility)
    {
        setVisibility(this->visibility | visibility);
    }

    void removeVisibility(Visibility visibility)
    {
        setVisibility(this->visibility & ~visibility);
    }

    bool affectsParentLayout = true;

    void setAffectsParentLayout(bool affectsParentLayout)
    {
        this->affectsParentLayout = affectsParentLayout;
    }

    bool getAffectsParentLayout() const
    {
        return affectsParentLayout;
    }

    bool isNeededUpdateParentLayout() const
    {
        AAssert(this->parent, "Parent is not set");
        return affectsParentLayout;
    }

    Math::IntegerRectangle getGeometry() const
    {
        return Math::IntegerRectangle{
            transform.Position.getXY<Math::IntegerVector>(),
            size
        };
    }

    void setGeometry(const Math::IntegerRectangle &rectangle)
    {
        transform.Position.x = rectangle.Position.x;
        transform.Position.y = rectangle.Position.y;
        size = rectangle.size;
    }

    SizePolicy getSizePolicyAt(size_t index) const { return index == 0 ? getHorizontalSizePolicy() : getVerticalSizePolicy(); }
    void setSizePolicyAt(size_t index, SizePolicy sizePolicy) { index == 0 ? setHorizontalSizePolicy(sizePolicy) : setVerticalSizePolicy(sizePolicy); }

    void setSizePolicy(SizePolicy sizePolicy)
    {
        if (sizePolicy == horizontalSizePolicy && sizePolicy == verticalSizePolicy)
        {
            return;
        }
        horizontalSizePolicy = sizePolicy;
        verticalSizePolicy = sizePolicy;
        requestLayoutUpdate();
    }

    void setSizePolicy(SizePolicy horizontal, SizePolicy vertical)
    {
        if (horizontal == horizontalSizePolicy && vertical == verticalSizePolicy)
        {
            return;
        }
        horizontalSizePolicy = horizontal;
        verticalSizePolicy = vertical;
        requestLayoutUpdate();
    }

    void show() { removeVisibility(Visibility::Hidden); }
    void hide() { addVisibility(Visibility::Hidden); }
    void activate() { removeVisibility(Visibility::Inactive); }
    void deactivate() { addVisibility(Visibility::Inactive); }
    void enable() { removeVisibility(Visibility::Disabled); }
    void disable() { addVisibility(Visibility::Disabled); }
    void expand() { removeVisibility(Visibility::Collapsed); }
    void collapse() { addVisibility(Visibility::Collapsed); }

    bool isVisible() const { return !(visibility & Visibility::Hidden); }
    void setVisible(bool visible) { !visible ? addVisibility(Visibility::Hidden) : removeVisibility(Visibility::Hidden); }
    bool isActive() const { return !(visibility & Visibility::Inactive); }
    void setActive(bool active) { !active ? addVisibility(Visibility::Inactive) : removeVisibility(Visibility::Inactive); }
    bool isEnabled() const { return !(visibility & Visibility::Disabled); }
    void setEnabled(bool enabled) { !enabled ? addVisibility(Visibility::Disabled) : removeVisibility(Visibility::Disabled); }
    bool isExpanded() const { return !(visibility & Visibility::Collapsed); }
    void setExpanded(bool expanded) { !expanded ? addVisibility(Visibility::Collapsed) : removeVisibility(Visibility::Collapsed); }

    void requestMatrixUpdate()
    {
        neededGlobalMatrixUpdate = true;
        neededGraphicsMatrixUpdate = true;
        for (auto &view : views)
        {
            view->requestMatrixUpdate();
        }
    }

    void requestGraphicsUpdate()
    {
        neededGraphicsUpdate = true;
        if (this->parent)
        {
            this->parent->requestGraphicsUpdate();
        }
    }

    void requestLayoutUpdate()
    {
        neededLayoutUpdate = true;
        if (this->parent && isNeededUpdateParentLayout())
        {
            this->parent->requestLayoutUpdate();
        }
    }

    void requestUpdate()
    {
        neededLayoutUpdate = true;
        neededGraphicsUpdate = true;
        if (this->parent)
        {
            if (isNeededUpdateParentLayout())
            {
                this->parent->requestUpdate();
            }
            else
            {
                this->parent->requestGraphicsUpdate();
            }
        }
    }

    void requestGraphicsUpdateRecursive()
    {
        for (SharedReference<UI::View> &view : views)
        {
            view->neededGraphicsUpdate = true;
            view->requestGraphicsUpdateRecursive();
        }
    }

    void requestLayoutUpdateRecursive()
    {
        for (SharedReference<UI::View> &view : views)
        {
            view->neededLayoutUpdate = true;
            view->requestLayoutUpdateRecursive();
        }
    }

    void requestUpdateRecursive()
    {
        for (SharedReference<UI::View> &view : views)
        {
            view->neededLayoutUpdate = true;
            view->neededGraphicsUpdate = true;
            view->requestUpdateRecursive();
        }
    }
    
    void resetMatericesRecursive()
    {
        for (SharedReference<UI::View> &view : views)
        {
            view->neededGraphicsMatrixUpdate = true;
            view->neededGlobalMatrixUpdate = true;
            view->resetMatericesRecursive();
        }
    }

    Math::IntegerVector getPreferedSize(const Math::IntegerVector &size) const;

    virtual void addView(const SharedReference<UI::View> &view)
    {
        This::insertView(views.size(), view);
    }

    virtual void insertView(size_t index, const SharedReference<UI::View> &view)
    {
        AAssert(view->parent != this, "View is already added");

        if (view->parent)
        {
            view->parent->removeView(view);
        }
        views.insert(views.begin() + index, view);
        view->parent = this;
        if (getOwner())
        {
            view->updateOwners(getOwner());
        }

        view->requestUpdate();
        view->requestMatrixUpdate();
    }

    virtual void replaceView(size_t viewIndex, const SharedReference<View> &otherView)
    {
        auto &v = views[viewIndex];
        v->updateOwners(nullptr);
        v->parent = nullptr;

        if (otherView->parent)
        {
            otherView->parent->removeView(otherView);
        }
        views[viewIndex] = otherView;
        otherView->parent = this;
        if (getOwner())
        {
            otherView->updateOwners(getOwner());
        }

        otherView->requestUpdate();
        otherView->requestMatrixUpdate();
    }

    virtual void replaceView(const SharedReference<View> &view, const SharedReference<View> &otherView)
    {
        replaceView(*view, otherView);
    }

    virtual void replaceView(const View &view, const SharedReference<View> &otherView)
    {
        auto it = ranges::find_if(views, [&view](const SharedReference<UI::View> &item) { return &view == item.get(); });
        if (it == views.end())
        {
            return;
        }

        auto &v = *it;
        v->updateOwners(nullptr);
        v->parent = nullptr;

        if (otherView->parent)
        {
            otherView->parent->removeView(otherView);
        }
        *it = otherView;
        otherView->parent = this;
        if (getOwner())
        {
            otherView->updateOwners(getOwner());
        }

        otherView->requestUpdate();
        otherView->requestMatrixUpdate();
    }

    virtual void wrapView(const SharedReference<View> &view, const SharedReference<View> &otherView)
    {
        wrapView(view, otherView);
    }

    virtual void wrapView(const View &view, const SharedReference<View> &otherView)
    {
        auto it = ranges::find_if(views, [&view](const SharedReference<UI::View> &item) { return &view == item.get(); });
        if (it == views.end())
        {
            return;
        }

        auto &v = *it;
        v->updateOwners(nullptr);
        v->parent = nullptr;

        if (otherView->parent)
        {
            otherView->parent->removeView(otherView);
        }
        SharedReference<View> wrappedView = *it;
        *it = otherView;
        otherView->addView(wrappedView);
        otherView->parent = this;
        if (getOwner())
        {
            otherView->updateOwners(getOwner());
        }

        otherView->requestUpdate();
        otherView->requestMatrixUpdate();
    }

    virtual void removeView(const SharedReference<UI::View> &view)
    {
        AAssert(view->parent == this, "This view is not a parent of the view is being removed");

        auto it = ranges::find_if(views, [view](const SharedReference<UI::View> &item) { return view == item; });
        if (it == views.end())
        {
            return;
        }

        view->updateOwners(nullptr);
        view->parent = nullptr;
        views.erase(it);
        requestUpdate();
        requestMatrixUpdate();
    }

    virtual void removeAllViews()
    {
        for (auto &view : views)
        {
            view->updateOwners(nullptr);
            view->parent = nullptr;
        }
        views.clear();
        requestUpdate();
        requestMatrixUpdate();
    }

    void removeFromParent()
    {
        if (!parent)
        {
            return;
        }

        auto &parentViews = this->parent->views;
        for (auto it = parentViews.begin(); it != parentViews.end(); ++it)
        {
            if (it->get() == this)
            {
                updateOwners(nullptr);
                this->parent->requestUpdate();
                this->parent->requestMatrixUpdate();
                this->parent = nullptr;
                parentViews.erase(it);
                break;
            }
        }
    }

    void moveFront()
    {
        if (!this->parent)
        {
            return;
        }

        auto &parentViews = this->parent->views;
        for (auto it = parentViews.begin(); it != parentViews.end(); ++it)
        {
            if (it->get() == this)
            {
                SharedReference<View> thisView = *it;
                parentViews.erase(it);
                parentViews.push_back(thisView);
                break;
            }
        }
    }

    void moveBack()
    {
        if (!this->parent)
        {
            return;
        }

        auto &parentViews = this->parent->views;
        for (auto it = parentViews.begin(); it != parentViews.end(); ++it)
        {
            if (it->get() == this)
            {
                SharedReference<View> thisView = *it;
                parentViews.erase(it);
                ArrayUtils::Insert(parentViews, 0, thisView); //TODO: prepend
                break;
            }
        }
    }

    void addGestureRecognizer(const SharedReference<GestureRecognizer> &recognizer)
    {
        gestureRecognizers.push_back(recognizer);
        if (loaded)
        {
            recognizer->load(*this);
        }
    }

    void insertGestureRecognizer(size_t index, const SharedReference<GestureRecognizer> &recognizer)
    {
        ArrayUtils::Insert(gestureRecognizers, index, recognizer);
        if (loaded)
        {
            recognizer->load(*this);
        }
    }

    void removeGestureRecognizer(const SharedReference<GestureRecognizer> &recognizer)
    {
        if (loaded)
        {
            recognizer->unload();
        }
        ArrayUtils::Remove(gestureRecognizers, recognizer);
    }

    void reserve(size_t size)
    {
        views.reserve(size);
    }

    void updateOwners(Component *owner);
    void processOwners(Component *owner);

    View()
    {
        ARegisterEventCallback(onLoad);
        ARegisterEventCallback(onUnload);
        ARegisterEventCallback(onUpdate);
    }

    virtual ~View()
    {
        unload();

        for (auto &view : views)
        {
            view->updateOwners(nullptr);
            view->parent = nullptr;
        }

        AUnregisterEventCallback(onUpdate);
        AUnregisterEventCallback(onUnload);
        AUnregisterEventCallback(onLoad);
    }

    void constructHierarchy()
    {
        onHierarchyCreate();
    }

    void destroyHierarchy()
    {
        onHierarchyDestroy();
        removeAllViews();
    }

protected:

    void load();
    void unload();

    virtual void onHierarchyCreate() {}
    virtual void onHierarchyDestroy() {}

    void updateViews(AUpdateEvent &event);

    virtual void onLoad(ALoadEvent &event);
    virtual void onUnload(AUnloadEvent &event);
    virtual void onUpdate(AUpdateEvent &event);
    virtual void onLayout(AUpdateEvent &event);
    virtual void onDraw(AUpdateEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION

namespace Memory
{

template<typename Type>
struct Constructor<Type, UI::View>
{
    inline static Type *Create()
    {
        Type *view = Constructor<Type, UI::View::Super>::Create();
        view->constructHierarchy();
        return view;
    }

    template<typename DelegateType, typename ...Arguments>
    inline static Type *Create(DelegateType &&preConstructCallback, Arguments &&...arguments)
    {
        Type *view;
        if constexpr (std::is_invocable<DelegateType, Type *>::value)
        {
            view = Constructor<Type, UI::View::Super>::Create(std::forward<Arguments>(arguments)...);
            preConstructCallback(view);
        }
        else
        {
            view = Constructor<Type, UI::View::Super>::Create(preConstructCallback, std::forward<Arguments>(arguments)...);
        }
        view->constructHierarchy();
        return view;
    }
};

}
