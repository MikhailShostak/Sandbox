//CLASSGEN GENERATED REGION: Includes
#include "TypesView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
#include "ApplicationManager.gen.h"
#include "FileManager.gen.h"
#include "TypeData.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TypesView::TypesView()
{
    Math::Transform transform_974;
    Math::Vector position_975;
    position_975.X = 0.000000;
    position_975.Y = 0.000000;
    position_975.Z = 0.000000;
    position_975.W = 0.000000;
    transform_974.Position = position_975;
    Math::Quaternion rotation_980;
    rotation_980.X = 0.000000;
    rotation_980.Y = 0.000000;
    rotation_980.Z = 0.000000;
    rotation_980.W = 1.000000;
    transform_974.Rotation = rotation_980;
    (*this).setTransform(transform_974);
    Math::IntegerVector size_985;
    size_985.X = 200.000000;
    size_985.Y = 200.000000;
    size_985.Z = 0.000000;
    size_985.W = 0.000000;
    (*this).setSize(size_985);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_998_0;
    item_998_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_1000_1;
    item_1000_1.Alignment = Core::Alignment::Start;
    (*this).setData({item_998_0,item_1000_1,});
    (*this).setDirection(UI::Direction::Vertical);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_1004;
    padding_1004.Top = 8.000000;
    padding_1004.Right = 8.000000;
    padding_1004.Bottom = 8.000000;
    padding_1004.Left = 8.000000;
    (*this).setPadding(padding_1004);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TypesView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TypesView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TypesView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TypesView");
    typesList = CreateShared<UI::ListView>();
    (*typesList).setName("TypesList");
    Math::Transform transform_936;
    Math::Vector position_937;
    position_937.X = 0.000000;
    position_937.Y = 0.000000;
    position_937.Z = 0.000000;
    position_937.W = 0.000000;
    transform_936.Position = position_937;
    Math::Quaternion rotation_942;
    rotation_942.X = 0.000000;
    rotation_942.Y = 0.000000;
    rotation_942.Z = 0.000000;
    rotation_942.W = 1.000000;
    transform_936.Rotation = rotation_942;
    (*typesList).setTransform(transform_936);
    Math::IntegerVector size_947;
    size_947.X = 0.000000;
    size_947.Y = 0.000000;
    size_947.Z = 0.000000;
    size_947.W = 0.000000;
    (*typesList).setSize(size_947);
    (*typesList).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*typesList).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*typesList).setAffectsParentLayout(false);
    (*this).addView(typesList);
    editorsList = CreateShared<UI::ListView>();
    (*editorsList).setName("EditorsList");
    Math::Transform transform_955;
    Math::Vector position_956;
    position_956.X = 0.000000;
    position_956.Y = 0.000000;
    position_956.Z = 0.000000;
    position_956.W = 0.000000;
    transform_955.Position = position_956;
    Math::Quaternion rotation_961;
    rotation_961.X = 0.000000;
    rotation_961.Y = 0.000000;
    rotation_961.Z = 0.000000;
    rotation_961.W = 1.000000;
    transform_955.Rotation = rotation_961;
    (*editorsList).setTransform(transform_955);
    Math::IntegerVector size_966;
    size_966.X = 0.000000;
    size_966.Y = 0.000000;
    size_966.Z = 0.000000;
    size_966.W = 0.000000;
    (*editorsList).setSize(size_966);
    (*editorsList).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*editorsList).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*editorsList).setAffectsParentLayout(false);
    (*this).addView(editorsList);
}
//CLASSGEN END REGION
void TypesView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    typesList->setAdapter(this);
    editorsList->setAdapter(this);

    OneStudio::FileManager::getThisInstance().onTypesUpdated = [this]() {
        typesList->notifyUpdateAllItems();
    };

    OneStudio::FileManager::getThisInstance().onEditorsUpdated = [this]() {
        editorsList->notifyUpdateAllItems();
    };
}

UI::SizeType TypesView::getCountItems(const AObject &sender) const
{
    if (&sender == typesList.get())
    {
        auto types = OneStudio::FileManager::getThisInstance().getTypes();
        return types.size();
    }
    else
    {
        auto editors = OneStudio::FileManager::getThisInstance().getEditors();
        return editors.size();
    }
}

SharedReference<UI::View> TypesView::provideViewForItem(const AObject &sender, UI::SizeType index)
{
    if (&sender == typesList.get())
    {
        auto types = OneStudio::FileManager::getThisInstance().getTypes();
        OneStudio::TypeData &type = types[index];
        auto v = CreateShared<UI::DefaultTextItemView>();
        v->setText(type.Type + " (" + boost::join(type.Extensions, ", ") + ") : " + type.AssociatedEditor);
        return v;
    }
    else
    {
        auto editors = OneStudio::FileManager::getThisInstance().getEditors();
        OneStudioPlatform::EditorData &editor = editors[index];
        auto v = CreateShared<UI::DefaultTextItemView>();
        v->setText(editor.Identifier + "(" + boost::join(editor.SuppoertedTypes, ", ") + ")");
        return v;
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
