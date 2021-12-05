#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Button.gen.h"
#include "Foundation"

#include "Foundation"
#include "Label.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class TextButton : public UI::Button
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TextButton This;
    typedef UI::Button Super;
    typedef void Interfaces;
protected:
    String Text;
public:
    TextButton();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    String getText() const;
    void setText(String const &Text);
    void setText(String &&Text);
    void updateText();
    SharedReference<UI::Label> title;
    void onHierarchyCreate();
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
