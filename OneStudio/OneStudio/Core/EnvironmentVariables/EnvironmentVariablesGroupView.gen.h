#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"
#include "Foundation"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: Namespace
namespace OneStudio
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class EnvironmentVariablesGroupView : public UI::FlexBox
//CLASSGEN END REGION
, public UI::ItemAdapter
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef EnvironmentVariablesGroupView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
protected:
    Text Title;
public:
    EnvironmentVariablesGroupView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Text getTitle() const;
    void setTitle(Text const &Title);
    void setTitle(Text &&Title);
    SharedReference<UI::Label> title;
    SharedReference<UI::ListView> list;
    void onHierarchyCreate();
//CLASSGEN END REGION

    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);
        list->setAdapter(this);
        title->setText(Title);
    }

    Array<APair<String, String>> variables;

    UI::SizeType getCountItems(const AObject &sender) const override { return variables.size(); }
    SharedReference<UI::View> provideViewForItem(const AObject &sender, UI::SizeType index) override
    {
        auto v = CreateShared<UI::DefaultTextItemView>();
        v->setText(variables[index].first + " = " + variables[index].second);
        return v;
    }

};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
