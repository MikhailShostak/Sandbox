//CLASSGEN GENERATED REGION: Includes
#include "Pin.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "ImageView.gen.h"
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
Pin::Pin()
{
    UI::FlexBoxData item_458_0;
    item_458_0.Alignment = Core::Alignment::Center;
    UI::FlexBoxData item_460_1;
    item_460_1.Alignment = Core::Alignment::Center;
    (*this).setData({item_458_0,item_460_1,});
    (*this).setSpacing(4.000000);
    Math::Offsets padding_463;
    padding_463.Top = 4.000000;
    padding_463.Right = 4.000000;
    padding_463.Bottom = 4.000000;
    padding_463.Left = 4.000000;
    (*this).setPadding(padding_463);
    (*this).setConnectionSource(false);
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Pin::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void Pin::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
UI::PinType Pin::getType() const
{
    return this->Type;
}
void Pin::setType(UI::PinType const &Type)
{
    this->Type = Type;
    requestLayoutUpdate();
}
void Pin::setType(UI::PinType &&Type)
{
    this->Type = std::move(Type);
    requestLayoutUpdate();
}
Boolean Pin::getConnectionSource() const
{
    return this->ConnectionSource;
}
void Pin::setConnectionSource(Boolean const &ConnectionSource)
{
    this->ConnectionSource = ConnectionSource;
}
void Pin::setConnectionSource(Boolean &&ConnectionSource)
{
    this->ConnectionSource = std::move(ConnectionSource);
}
void Pin::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("Pin");
    socket = SharedReference<UI::ImageView>(Create<UI::ImageView>([this](UI::ImageView *v)
    {
    }
));
    (*socket).setName("Socket");
    {
    }
    (*socket).setImage(PinSocket);
    (*this).addView(socket);
    label = SharedReference<UI::Label>(Create<UI::Label>([this](UI::Label *v)
    {
    }
));
    (*label).setName("Label");
    {
    }
    (*this).addView(label);
}
//CLASSGEN END REGION
String Pin::getIdentifier() const
{
    return label->getText();
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
