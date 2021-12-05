#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "ExperimentalDebug"

#include "Foundation"
#include "ExperimentalDebug"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class ClassPicker : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ClassPicker This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
public:
    ClassPicker();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void showClass();
    void openClass();
    SharedReference<UI::TextField> textField;
    SharedReference<UI::TextButton> navigateButton;
    SharedReference<UI::TextButton> openButton;
    void onHierarchyCreate();
//CLASSGEN END REGION
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
