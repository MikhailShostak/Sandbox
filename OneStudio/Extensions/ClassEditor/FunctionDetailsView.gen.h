#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Experimental"

#include "Foundation"
#include "Experimental"

//CLASSGEN END REGION
#include "Includes/Parameter.gen.h"
#include "Includes/FunctionInfo.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class FunctionDetailsView : public UI::FlexBox
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef FunctionDetailsView This;
    typedef UI::FlexBox Super;
    typedef void Interfaces;
protected:
    LegacyClassGen::FunctionInfo Function;
public:
    FunctionDetailsView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    LegacyClassGen::FunctionInfo getFunction() const;
    void setFunction(LegacyClassGen::FunctionInfo const &Function);
    void setFunction(LegacyClassGen::FunctionInfo &&Function);
    SharedReference<UI::TextField> nameView;
    SharedReference<UI::TextButton> inputArgumentsAddButton;
    SharedReference<UI::ListView> inputArgumentsView;
    SharedReference<UI::TextButton> outputArgumentsAddButton;
    SharedReference<UI::ListView> outputArgumentsView;
    void onHierarchyCreate();
//CLASSGEN END REGION
    ADelegate<bool(const String &oldName, const String &newName)> onNameChanged;
    ADelegate<void(const FunctionInfo &function)> onChanged;
    void onLoad(ALoadEvent &event);
    void setFunctionInfo(const LegacyClassGen::FunctionInfo &data);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
