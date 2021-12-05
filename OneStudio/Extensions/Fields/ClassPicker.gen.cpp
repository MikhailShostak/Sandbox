//CLASSGEN GENERATED REGION: Includes
#include "ClassPicker.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ExperimentalDebug"
#include "MathClasses"
#include "Math"

//CLASSGEN END REGION
#include <ClassGenLibrary>
//CLASSGEN GENERATED REGION: Namespace
namespace LegacyClassGen
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
ClassPicker::ClassPicker()
{
    UI::FlexBoxData item_12_0;
    UI::FlexBoxData item_13_1;
    UI::FlexBoxData item_14_2;
    (*this).setData({item_12_0,item_13_1,item_14_2,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ClassPicker::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void ClassPicker::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void ClassPicker::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("ClassPicker");
    textField = CreateShared<UI::TextField>([this](UI::TextField *v)
    {
    }
);
    (*textField).setName("TextField");
    {
    }
    (*textField).setPlaceholder("Class Type");
    (*this).addView(textField);
    navigateButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*navigateButton).setName("NavigateButton");
    {
        (*navigateButton).OnClick = [this]()        {
            return showClass();
        };
;
    }
    (*navigateButton).setText("Show");
    (*this).addView(navigateButton);
    openButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*openButton).setName("OpenButton");
    {
        (*openButton).OnClick = [this]()        {
            return openClass();
        };
;
    }
    (*openButton).setText("Open");
    (*this).addView(openButton);
}
//CLASSGEN END REGION
void ClassPicker::showClass()
{
    String typeName = textField->getText();

    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeName);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        Console::getInstance().applyCommand("Show " + typeIt->second->path.toString());
    }
}

void ClassPicker::openClass()
{
    String typeName = textField->getText();

    auto typeIt = LegacyClassGen::ClassManager::getInstance().getLoadedTypes().find(typeName);
    if (typeIt != LegacyClassGen::ClassManager::getInstance().getLoadedTypes().end())
    {
        Console::getInstance().applyCommand("Open " + typeIt->second->path.toString());
    }
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
