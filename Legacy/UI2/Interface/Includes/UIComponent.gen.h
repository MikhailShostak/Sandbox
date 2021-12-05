#pragma once

//CLASSGEN GENERATED REGION: Includes
#include <Graphics>

//CLASSGEN END REGION
#include <UI>
//CLASSGEN GENERATED REGION: NamespaceBegin
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: ClassHeader
class UIComponent : public Core::ApplicationComponent2
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef UIComponent This;
    typedef Core::ApplicationComponent2 Super;
    typedef void Interfaces;
protected:
    SharedReference<UI::View> MainView;
public:
    UIComponent();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::View> getMainView() const;
    void setMainView(SharedReference<UI::View> const &MainView);
    void setMainView(SharedReference<UI::View> &&MainView);
    void onCreate();
    void onLoad();
    void onUnload();
    void onUpdate();
//CLASSGEN END REGION
    bool isInitialized = false;
    explicit operator bool() const { return isInitialized; };
};
//CLASSGEN GENERATED REGION: NamespaceEnd
//CLASSGEN END REGION

namespace Memory
{

template<typename Type>
struct Constructor<Type, UIComponent>
{
    template<typename ...Arguments>
    inline static Type *Create(Arguments &&...arguments)
    {
        Type *component = Constructor<Type, UIComponent::Super>::Create(std::forward<Arguments>(arguments)...);
        component->onCreate();
        return component;
    }
};

}
