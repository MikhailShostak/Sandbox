//CLASSGEN GENERATED REGION: Includes
#include "PageView.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PageView::PageView()
{
    Math::Transform transform_16;
    Math::Vector position_17;
    position_17.X = 0.000000;
    position_17.Y = 0.000000;
    position_17.Z = 0.000000;
    position_17.W = 0.000000;
    transform_16.Position = position_17;
    Math::Quaternion rotation_22;
    rotation_22.X = 0.000000;
    rotation_22.Y = 0.000000;
    rotation_22.Z = 0.000000;
    rotation_22.W = 1.000000;
    transform_16.Rotation = rotation_22;
    (*this).setTransform(transform_16);
    Math::IntegerVector size_27;
    size_27.X = 0.000000;
    size_27.Y = 0.000000;
    size_27.Z = 0.000000;
    size_27.W = 0.000000;
    (*this).setSize(size_27);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    (*this).setCurrentPage(-1);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PageView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("CurrentPage", toJSONValue(CurrentPage));
}
void PageView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("CurrentPage", value);
    fromJSONValue(value, CurrentPage);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SizeInteger PageView::getCurrentPage() const
{
    return this->CurrentPage;
}
void PageView::setCurrentPage(SizeInteger const &CurrentPage)
{
    this->CurrentPage = CurrentPage;
    UpdateContent();
}
void PageView::setCurrentPage(SizeInteger &&CurrentPage)
{
    this->CurrentPage = std::move(CurrentPage);
    UpdateContent();
}
//CLASSGEN END REGION

void PageView::setCurrentView(const UI::View &view)
{
    const auto &views = getViews();
    auto it = std::find_if(views.begin(), views.end(), [&](auto &v){ return v.get() == &view; });
    if(it != views.end())
    {
        setCurrentPage(std::distance(views.begin(), it));
    }
    else
    {
        setCurrentPage(-1);
    }
}

void PageView::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);
    UpdateContent();
}

void PageView::UpdateContent()
{
    if (getViews().empty())
    {
        return;
    }

    for (auto &view : getViews())
    {
        view->collapse();
    }

    if(getCurrentPage() != -1)
    {
        getViews()[getCurrentPage()]->expand();
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
