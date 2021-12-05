//CLASSGEN GENERATED REGION: Includes
#include "PathField.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "TextField.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include "TextButton.gen.h"

//CLASSGEN END REGION
#include "UITouchGestureRecognizer.h"
#include <commdlg.h>
//#include <Windows.h>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
PathField::PathField()
{
    Math::Transform transform_228;
    Math::Vector position_229;
    position_229.X = 0.000000;
    position_229.Y = 0.000000;
    position_229.Z = 0.000000;
    position_229.W = 0.000000;
    transform_228.Position = position_229;
    Math::Quaternion rotation_234;
    rotation_234.X = 0.000000;
    rotation_234.Y = 0.000000;
    rotation_234.Z = 0.000000;
    rotation_234.W = 1.000000;
    transform_228.Rotation = rotation_234;
    (*this).setTransform(transform_228);
    Math::IntegerVector size_239;
    size_239.X = 0.000000;
    size_239.Y = 0.000000;
    size_239.Z = 0.000000;
    size_239.W = 0.000000;
    (*this).setSize(size_239);
    (*this).setHorizontalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setVerticalSizePolicy(UI::SizePolicy::Fixed);
    (*this).setAffectsParentLayout(false);
    (*this).setNeededLayoutUpdate(false);
    (*this).setNeededGraphicsUpdate(false);
    (*this).setNeededGlobalMatrixUpdate(false);
    (*this).setNeededGraphicsMatrixUpdate(false);
    UI::FlexBoxData item_252_0;
    item_252_0.Alignment = Core::Alignment::Start;
    UI::FlexBoxData item_254_1;
    item_254_1.Alignment = Core::Alignment::Start;
    (*this).setData({item_252_0,item_254_1,});
    (*this).setDirection(UI::Direction::Horizontal);
    (*this).setSpacing(8.000000);
    Math::Offsets padding_258;
    padding_258.Top = 0.000000;
    padding_258.Right = 0.000000;
    padding_258.Bottom = 0.000000;
    padding_258.Left = 0.000000;
    (*this).setPadding(padding_258);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PathField::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void PathField::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void PathField::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("PathField");
    pathField = SharedReference<UI::TextField>(Create<UI::TextField>([this](UI::TextField *v)
    {
    }
));
    (*pathField).setName("PathField");
    {
    }
    Math::Transform transform_189;
    Math::Vector position_190;
    position_190.X = 0.000000;
    position_190.Y = 0.000000;
    position_190.Z = 0.000000;
    position_190.W = 0.000000;
    transform_189.Position = position_190;
    Math::Quaternion rotation_195;
    rotation_195.X = 0.000000;
    rotation_195.Y = 0.000000;
    rotation_195.Z = 0.000000;
    rotation_195.W = 1.000000;
    transform_189.Rotation = rotation_195;
    (*pathField).setTransform(transform_189);
    Math::IntegerVector size_200;
    size_200.X = 0.000000;
    size_200.Y = 0.000000;
    size_200.Z = 0.000000;
    size_200.W = 0.000000;
    (*pathField).setSize(size_200);
    (*pathField).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
    (*pathField).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*pathField).setAffectsParentLayout(false);
    (*this).addView(pathField);
    selectButton = CreateShared<UI::TextButton>([this](UI::TextButton *v)
    {
    }
);
    (*selectButton).setName("SelectButton");
    {
    }
    Math::Transform transform_208;
    Math::Vector position_209;
    position_209.X = 0.000000;
    position_209.Y = 0.000000;
    position_209.Z = 0.000000;
    position_209.W = 0.000000;
    transform_208.Position = position_209;
    Math::Quaternion rotation_214;
    rotation_214.X = 0.000000;
    rotation_214.Y = 0.000000;
    rotation_214.Z = 0.000000;
    rotation_214.W = 1.000000;
    transform_208.Rotation = rotation_214;
    (*selectButton).setTransform(transform_208);
    Math::IntegerVector size_219;
    size_219.X = 0.000000;
    size_219.Y = 0.000000;
    size_219.Z = 0.000000;
    size_219.W = 0.000000;
    (*selectButton).setSize(size_219);
    (*selectButton).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*selectButton).setVerticalSizePolicy(UI::SizePolicy::Expanded);
    (*selectButton).setAffectsParentLayout(false);
    (*selectButton).setText("...");
    (*this).addView(selectButton);
}
//CLASSGEN END REGION

void PathField::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    selectButton->eventChannel.registerDelegate([this](UI::TapGestureEvent &event) {

        constexpr size_t MaxPath = UNICODE ? 32768 : MAX_PATH;

        static char outputBuffer[MaxPath + 1];

        OPENFILENAMEA dialogData;
        ZeroMemory(&dialogData, sizeof(dialogData));
        dialogData.lStructSize = sizeof(dialogData);

        dialogData.hwndOwner = GetActiveWindow();

        dialogData.lpstrFile = (char*)outputBuffer;
        dialogData.nMaxFile = MaxPath;

        if (!dialogTitle.empty())
        {
            dialogData.lpstrTitle = (char*)dialogTitle.data();
        }

        dialogData.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        if (!filter.empty())
        {
            dialogData.lpstrFilter = /*(wchar_t*)filter[0].data();*/"All Files (*.*)\0*.*\0";
        }

        if (GetOpenFileNameA(&dialogData))
        {
            pathField->setText(outputBuffer);
        }
    });
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
