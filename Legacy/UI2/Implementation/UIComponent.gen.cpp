//CLASSGEN GENERATED REGION: Includes
#include "UIComponent.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassImplementation
UIComponent::UIComponent()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void UIComponent::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("MainView", toJSONValue(MainView));
}
void UIComponent::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("MainView", value);
    fromJSONValue(value, MainView);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
SharedReference<UI::View> UIComponent::getMainView() const
{
    return this->MainView;
}
void UIComponent::setMainView(SharedReference<UI::View> const &MainView)
{
    this->MainView = MainView;
}
void UIComponent::setMainView(SharedReference<UI::View> &&MainView)
{
    this->MainView = std::move(MainView);
}
//CLASSGEN END REGION
void UIComponent::onCreate()
{
    ExecuteGlobalCalls();

    if (!UI::Component::getSprite()->isLoaded())
    {
        UI::Component::getSprite()->load();
    }
    if (!UI::Component::getPlaceholderImage()->isLoaded())
    {
        UI::Component::getPlaceholderImage()->load();
    }

    //Need to load fonts
    UI::Component *c = nullptr;
    c->loadDefaultStyle();
    //Core::FontEngine::getInstance().load(getAsset("NotoSansUI_Regular"));
    //Core::Font DefaultFont("Noto Sans UI", "Regular", 12);
}

void UIComponent::onLoad()
{

}

void UIComponent::onUnload()
{
}

void UIComponent::onUpdate()
{
    
}

//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION
