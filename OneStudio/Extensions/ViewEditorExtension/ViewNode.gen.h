#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
#include "Foundation"

//CLASSGEN END REGION
#include "PreviewNodeView.gen.h"
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

enum class ViewPlacement
{
    View,
    Background,
    Content
};
//CLASSGEN GENERATED REGION: ClassHeader
struct ViewNode : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ViewNode This;
    typedef Serializable Super;
    typedef void Interfaces;
public:
    String Name;
    SharedReference<LegacyClassGen::PreviewNodeView> View;
    Array<SharedReference<ViewNode>> Items;
    WeakReference<UI::DefaultExpandableItemView> TreeItem;
    LegacyClassGen::TypeInfo Type;
    AJSONObject Data;
public:
    ViewNode();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
//CLASSGEN END REGION
    ViewNode *Parent = nullptr;
    bool isExpanded = true;
    bool isVariable = false;
    Array<SharedReference<ViewNode>> GetItems() const { return Items; }

    ViewPlacement Placement = ViewPlacement::View;

    ViewNode(const String &name):Name(name) {}

    void updateInstance()
    {
        if (View->getInstance())
        {
            View->getInstance()->removeFromParent();
        }
        MetaObject *metaObject = MetaObjectManager::getInstance().findMetaObject(Type.Name);
        if (metaObject)
        {
            View->setInstance(SharedReference<UI::View>(StaticCast<UI::View>(metaObject->constructor())));
            //View->getInstance()->setEnabled(false); TODO: should input be blocked?
            View->requestLayoutUpdate();
        }
        else
        {
            View->setInstance(CreateShared<UI::View>());
            View->requestLayoutUpdate();
        }
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
