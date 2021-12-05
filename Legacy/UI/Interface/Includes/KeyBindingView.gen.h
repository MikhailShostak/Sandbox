#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "TextField.gen.h"

#include "Foundation"

//CLASSGEN END REGION
#include <Graphics>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class KeyBindingView : public UI::TextField
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef KeyBindingView This;
    typedef UI::TextField Super;
    typedef void Interfaces;
protected:
    Core::Shortcut Shortcut;
public:
    KeyBindingView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Core::Shortcut getShortcut() const;
    void setShortcut(Core::Shortcut const &Shortcut);
    void setShortcut(Core::Shortcut &&Shortcut);
    void onHierarchyCreate();
//CLASSGEN END REGION
    virtual void onKeyPressed(AWindowKeyPressEvent &event) override;
    virtual void onKeyReleased(AWindowKeyReleaseEvent &event) override;
    virtual void onCharEntered(AWindowKeyCharEvent &event) override;
};

class ShortcutChanged : public UIPropertyChangeEvent<Core::Shortcut>
{
public:
    using Super = UIPropertyChangeEvent<Core::Shortcut>;
    using Super::Super;
};


//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
