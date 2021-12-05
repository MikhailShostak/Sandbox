//CLASSGEN GENERATED REGION: Includes
#include "Button.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"
#include "BorderImageView.gen.h"
#include "Math"
#include "SizePolicy.gen.h"
#include "Visibility.gen.h"
#include <Graphics>

//CLASSGEN END REGION
#include "UITouchGestureRecognizer.h"
#include <UIDarkTheme>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
Button::Button()
{
    (*this).setHorizontalSizePolicy(UI::SizePolicy::ContentWrapped);
    (*this).setVerticalSizePolicy(UI::SizePolicy::ContentWrapped);
    UI::OverlayData item_324_0;
    item_324_0.HorizontalAlignment = Core::Alignment::Center;
    item_324_0.VerticalAlignment = Core::Alignment::Center;
    UI::OverlayData item_327_1;
    Math::Offsets padding_328;
    padding_328.Top = 2.000000;
    padding_328.Right = 4.000000;
    padding_328.Bottom = 2.000000;
    padding_328.Left = 4.000000;
    item_327_1.Padding = padding_328;
    item_327_1.HorizontalAlignment = Core::Alignment::Center;
    item_327_1.VerticalAlignment = Core::Alignment::Center;
    (*this).setData({item_324_0,item_327_1,});
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void Button::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("BackgroundImage", toJSONValue(BackgroundImage));
}
void Button::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("BackgroundImage", value);
    fromJSONValue(value, BackgroundImage);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SharedReference<Legacy::Graphics::Texture> Button::getBackgroundImage() const
{
    return this->BackgroundImage;
}
void Button::setBackgroundImage(SharedReference<Legacy::Graphics::Texture> const &BackgroundImage)
{
    this->BackgroundImage = BackgroundImage;
    updateTexture();
}
void Button::setBackgroundImage(SharedReference<Legacy::Graphics::Texture> &&BackgroundImage)
{
    this->BackgroundImage = std::move(BackgroundImage);
    updateTexture();
}
void Button::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("Button");
    if (background)
    {
        (*this).addView(background);
    }
    else
    {
        SharedReference<UI::BorderImageView> defaultBackground = SharedReference<UI::BorderImageView>(Create<UI::BorderImageView>([this](UI::BorderImageView *v)
        {
        }
));
        (*defaultBackground).setName("DefaultBackground");
        {
        }
        (*defaultBackground).setHorizontalSizePolicy(UI::SizePolicy::Expanded);
        (*defaultBackground).setVerticalSizePolicy(UI::SizePolicy::Expanded);
        (*defaultBackground).setImage(ButtonBackground);
        Math::Offsets border_316;
        border_316.Top = 2.000000;
        border_316.Right = 2.000000;
        border_316.Bottom = 2.000000;
        border_316.Left = 2.000000;
        (*defaultBackground).setBorder(border_316);
        (*this).addView(defaultBackground);
        background = defaultBackground;
    }
}
//CLASSGEN END REGION
void Button::onLoad(ALoadEvent &event)
{
    Super::onLoad(event);

    if (!initialized) //TODO: improve
    {
        addGestureRecognizer(std::make_shared<TouchGestureRecognizer>());
        eventChannel.registerDelegate([&](TouchDownGestureEvent &event) {
            if (!touched && event.isInside())
            {
                touched = true;
                background->setColor(background->getColor() - AColor(0.1f, 0.1f, 0.1f, 0.0f));
            }
        });
        eventChannel.registerDelegate([&](TouchUpGestureEvent &event) {
            if (touched)
            {
                background->setColor(background->getColor() + AColor(0.1f, 0.1f, 0.1f, 0.0f));
                touched = false;
            }
        });
        eventChannel.registerDelegate([&](TapGestureEvent &event) {
            if (OnClick)
            {
                OnClick();
            }
        });
        initialized = true;
    }
}

void Button::updateTexture()
{
    this->background->setImage(this->BackgroundImage);
}
//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
