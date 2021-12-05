//CLASSGEN GENERATED REGION: Includes
#include "TextButton.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "Label.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"

//CLASSGEN END REGION
#include <Graphics>
#include <UIDarkTheme>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
TextButton::TextButton()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TextButton::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Text", toJSONValue(Text));
}
void TextButton::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Text", value);
    fromJSONValue(value, Text);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
String TextButton::getText() const
{
    return this->Text;
}
void TextButton::setText(String const &Text)
{
    this->Text = Text;
    updateText();
}
void TextButton::setText(String &&Text)
{
    this->Text = std::move(Text);
    updateText();
}
void TextButton::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("TextButton");
    title = CreateShared<UI::Label>([this](UI::Label *v)
    {
    }
);
    (*title).setName("Title");
    {
    }
    (*title).setTextAlign(Core::TextAlign::Center);
    (*this).addView(title);
}
//CLASSGEN END REGION
void TextButton::updateText()
{
    title->setText(this->Text);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
