#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class CreateFileDialog : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef CreateFileDialog This;
    typedef UI::View Super;
    typedef void Interfaces;
public:
    CreateFileDialog();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::DropDownList> typeList;
    SharedReference<UI::TextButton> createButton;
    SharedReference<UI::TextButton> cancelButton;
    SharedReference<UI::TextField> nameTextField;
    SharedReference<UI::TextField> namespaceTextField;
    void onHierarchyCreate();
//CLASSGEN END REGION
};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
