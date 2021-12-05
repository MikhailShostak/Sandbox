#include "UIDialog.h"
#include "MetaObject.h"

namespace UI
{

AStaticRun(DialogViewMetaObject)
{
CLASSGEN_GENERATED_REGION_META_OBJECT
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<DialogView>();
    object.serialize = [](const AObject &object, AJSONObject &data){ static_cast<const DialogView&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object){ static_cast<DialogView&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<View>();
    object.registerMetaProperty<DialogView, AColor>("Color", &DialogView::getColor, &DialogView::setColor, false);
    object.registerMetaProperty<DialogView, UIOffsets>("Border", &DialogView::getBorder, &DialogView::setBorder, false);
    object.registerMetaProperty<DialogView, SharedReference<Legacy::Graphics::Texture>>("Image", &DialogView::getImage, &DialogView::setImage, false);
    object.registerMetaProperty<DialogView, String>("Title", &DialogView::getTitle, &DialogView::setTitle, false);
    object.registerMetaProperty<DialogView, Array<String>>("Buttons", &DialogView::getButtons, &DialogView::setButtons, false);
    manager.registerMetaObject("UI.DialogView", object);
CLASSGEN_END_REGION
}
CLASSGEN_GENERATED_REGION_OBJECT
void DialogView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void DialogView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
Array<String> DialogView::getButtons() const
{
    return this->buttons;
}
CLASSGEN_END_REGION


DialogView::DialogView()
{
    setLayout(SharedReference<UI::Layout>(dialogLayout));
}

AColor DialogView::getColor() const
{
    return dialogLayout->backgroundImageView->getColor();
}

void DialogView::setColor(const AColor &color)
{
    dialogLayout->backgroundImageView->setColor(color);
}

UIOffsets DialogView::getBorder() const
{
    return dialogLayout->backgroundImageView->getBorder();
}

void DialogView::setBorder(const UIOffsets &border)
{
    dialogLayout->backgroundImageView->setBorder(border);
}

SharedReference<Legacy::Graphics::Texture> DialogView::getImage() const
{
    return dialogLayout->backgroundImageView->getImage();
}

void DialogView::setImage(const SharedReference<Legacy::Graphics::Texture> &texture)
{
    dialogLayout->backgroundImageView->setImage(texture);
}

String DialogView::getTitle() const
{
    return dialogLayout->titleLabel->getText();
}

void DialogView::setTitle(const String &title)
{
    dialogLayout->titleLabel->setText(title);
}

void DialogView::setButtons(const Array<String> &buttons)
{
    this->buttons = buttons;
    //dialogLayout->buttonGroup->setButtons(buttons);
}

}
