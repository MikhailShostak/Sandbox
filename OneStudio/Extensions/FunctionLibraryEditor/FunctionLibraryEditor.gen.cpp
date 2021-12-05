//CLASSGEN GENERATED REGION: Includes
#include "FunctionLibraryEditor.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
FunctionLibraryEditor::FunctionLibraryEditor()
{
    UI::SplitViewLayoutData item_34_0;
    UI::SplitViewLayoutData item_35_1;
    (*this).setData({item_34_0,item_35_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FunctionLibraryEditor::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void FunctionLibraryEditor::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void FunctionLibraryEditor::onHierarchyCreate()
{
    outlinerView = CreateShared<UI::ListView>([this](UI::ListView *v)
    {
    }
);
    (*outlinerView).setName("OutlinerView");
    {
    }
    (*this).addView(outlinerView);
    Super::onHierarchyCreate();
    setName("FunctionLibraryEditor");
}
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
