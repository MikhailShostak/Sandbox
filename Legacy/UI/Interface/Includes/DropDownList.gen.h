#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "DropDown.gen.h"
#include "Foundation"
#include "Math"

//CLASSGEN END REGION
#include <Data>
#include "Includes/View.gen.h"
#include "Includes/TextButton.gen.h"
#include "UI/Views/UIMenu.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class DropDownList : public UI::DropDown
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DropDownList This;
    typedef UI::DropDown Super;
    typedef void Interfaces;
protected:
    Array<String> Elements;
SizeInteger CurrentIndex = -1;
public:
    DropDownList();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Array<String> getElements() const;
    void setElements(Array<String> const &Elements);
    void setElements(Array<String> &&Elements);
    SizeInteger getCurrentIndex() const;
    void setCurrentIndex(SizeInteger const &CurrentIndex);
    void setCurrentIndex(SizeInteger &&CurrentIndex);
//CLASSGEN END REGION

    void onLoad(ALoadEvent &event);
    void onLayout(AUpdateEvent &event);

    void updateMenuActions();
    void updateCurrentItem();

    SharedReference<UI::MenuView> menu;
};

class CurrentIndexChangedEvent : public UIPropertyChangeEvent<size_t>
{
public:
    using Super = UIPropertyChangeEvent<size_t>;
    using Super::Super;
};

class CurrentIndexSetEvent : public UIPropertyChangeEvent<size_t>
{
public:
    using Super = UIPropertyChangeEvent<size_t>;
    using Super::Super;
};
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
