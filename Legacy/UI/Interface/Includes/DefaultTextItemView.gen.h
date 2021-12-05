#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "FlexBox.gen.h"

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
class DefaultTextItemView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef DefaultTextItemView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    DefaultTextItemView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::Label> title;
    void onHierarchyCreate();
//CLASSGEN END REGION
const String &getText() const { return title->getText(); }
void setText(const String &text) { title->setText(text); }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
