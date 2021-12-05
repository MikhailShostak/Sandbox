#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "FlexBox.gen.h"

#include "Foundation"
#include "TextField.gen.h"
#include "TextButton.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class PathField : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef PathField This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    PathField();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::TextField> pathField;
    SharedReference<UI::TextButton> selectButton;
    void onHierarchyCreate();
//CLASSGEN END REGION
String dialogTitle = "Open File";
Array<String> filter = { "All Files (*.*)", "*.*" };
void onLoad(ALoadEvent &event) override;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
