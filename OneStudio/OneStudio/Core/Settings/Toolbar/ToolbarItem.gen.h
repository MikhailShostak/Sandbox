#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Serializable.h"
#include "Math"
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
class ToolbarItem : public Serializable
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ToolbarItem This;
    typedef Serializable Super;
    typedef void Interfaces;
protected:
    Text Identifier;
SharedReference<UI::View> View;
public:
    ToolbarItem();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Text getIdentifier() const;
    void setIdentifier(Text const &Identifier);
    void setIdentifier(Text &&Identifier);
    SharedReference<UI::View> getView() const;
    void setView(SharedReference<UI::View> const &View);
    void setView(SharedReference<UI::View> &&View);
//CLASSGEN END REGION
    ToolbarItem(const Text &Identifier, const SharedReference<UI::View> &View):Identifier(Identifier), View(View) {}
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
