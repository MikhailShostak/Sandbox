//CLASSGEN GENERATED REGION: Includes
#include "SettingsView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Experimental"
#include "Math"

//CLASSGEN END REGION
#include "ApplicationManager.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
SettingsView::SettingsView()
{
    Math::Transform transform_722;
    Math::Vector position_723;
    position_723.X = 0.000000;
    position_723.Y = 0.000000;
    position_723.Z = 0.000000;
    position_723.W = 0.000000;
    transform_722.Position = position_723;
    Math::Quaternion rotation_728;
    rotation_728.X = 0.000000;
    rotation_728.Y = 0.000000;
    rotation_728.Z = 0.000000;
    rotation_728.W = 1.000000;
    transform_722.Rotation = rotation_728;
    (*this).setTransform(transform_722);
    Math::IntegerVector size_733;
    size_733.X = 0.000000;
    size_733.Y = 0.000000;
    size_733.Z = 0.000000;
    size_733.W = 0.000000;
    (*this).setSize(size_733);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_746_0;
    item_746_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_748_1;
    item_748_1.Alignment = Core::Alignment::Start;
    (*this).setData({item_746_0,item_748_1,});
    (*this).setDirection(UI::Direction::Horizontal);
    (*this).setSpacing(0.000000);
    Math::Offsets padding_752;
    padding_752.Top = 0.000000;
    padding_752.Right = 0.000000;
    padding_752.Bottom = 0.000000;
    padding_752.Left = 0.000000;
    (*this).setPadding(padding_752);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void SettingsView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void SettingsView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void SettingsView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("SettingsView");
    SharedReference<UI::ListView> categoriesView = CreateShared<UI::ListView>();
    (*categoriesView).setName("CategoriesView");
    Math::Transform transform_675;
    Math::Vector position_676;
    position_676.X = 0.000000;
    position_676.Y = 0.000000;
    position_676.Z = 0.000000;
    position_676.W = 0.000000;
    transform_675.Position = position_676;
    Math::Quaternion rotation_681;
    rotation_681.X = 0.000000;
    rotation_681.Y = 0.000000;
    rotation_681.Z = 0.000000;
    rotation_681.W = 1.000000;
    transform_675.Rotation = rotation_681;
    (*categoriesView).setTransform(transform_675);
    Math::IntegerVector size_686;
    size_686.X = 200.000000;
    size_686.Y = 0.000000;
    size_686.Z = 0.000000;
    size_686.W = 0.000000;
    (*categoriesView).setSize(size_686);
    (*categoriesView).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*categoriesView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*categoriesView).setAffectsParentLayout(false);
    (*this).addView(categoriesView);
    SharedReference<UI::Overlay> contentView = CreateShared<UI::Overlay>();
    (*contentView).setName("ContentView");
    Math::Transform transform_694;
    Math::Vector position_695;
    position_695.X = 0.000000;
    position_695.Y = 0.000000;
    position_695.Z = 0.000000;
    position_695.W = 0.000000;
    transform_694.Position = position_695;
    Math::Quaternion rotation_700;
    rotation_700.X = 0.000000;
    rotation_700.Y = 0.000000;
    rotation_700.Z = 0.000000;
    rotation_700.W = 1.000000;
    transform_694.Rotation = rotation_700;
    (*contentView).setTransform(transform_694);
    Math::IntegerVector size_705;
    size_705.X = 0.000000;
    size_705.Y = 0.000000;
    size_705.Z = 0.000000;
    size_705.W = 0.000000;
    (*contentView).setSize(size_705);
    (*contentView).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*contentView).setAffectsParentLayout(false);
    UI::OverlayData item_714_0;
    Math::Offsets padding_715;
    padding_715.Top = 0.000000;
    padding_715.Right = 0.000000;
    padding_715.Bottom = 0.000000;
    padding_715.Left = 0.000000;
    item_714_0.Padding = padding_715;
    item_714_0.HorizontalAlignment = Core::Alignment::Start;
    item_714_0.VerticalAlignment = Core::Alignment::Start;
    (*contentView).setData({item_714_0,});
    (*this).addView(contentView);
}
//CLASSGEN END REGION

void SettingsView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    auto list = StaticCast<UI::ListView>(getViews()[0]);
    list->setAdapter(this);
    auto content = StaticCast<UI::Overlay>(getViews()[1]);
    content->setData({ {} });
}

UI::SizeType SettingsView::getCountItems(const AObject &sender) const
{
    return OneStudio::ApplicationManager::getThisInstance().getEntries().size();
}

SharedReference<UI::View> SettingsView::provideViewForItem(const AObject &sender, UI::SizeType index)
{
    auto v = CreateShared<UI::DefaultTextItemView>();
    v->setText(OneStudio::ApplicationManager::getThisInstance().getEntries()[index].Title);
    return v;
}

void SettingsView::onItemSelected(const AObject &sender, UI::TapGestureEvent &event, UI::SizeType index)
{
    auto content = StaticCast<UI::Overlay>(getViews()[1]);
    content->removeAllViews();
    auto contentView = OneStudio::ApplicationManager::getThisInstance().getEntries()[index].ContentView;
    contentView->setSizePolicy(UI::SizePolicy::Expanded, UI::SizePolicy::ContentWrapped); //TODO: Can be customized?
    content->addView(contentView);
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
