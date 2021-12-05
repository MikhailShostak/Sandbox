//CLASSGEN GENERATED REGION: Includes
#include "KeyBindingView.gen.h"
#include <MetaObjectSerializationHelper.h>
#include "Foundation"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassImplementation
KeyBindingView::KeyBindingView()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void KeyBindingView::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void KeyBindingView::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
Core::Shortcut KeyBindingView::getShortcut() const
{
    return this->Shortcut;
}
void KeyBindingView::setShortcut(Core::Shortcut const &Shortcut)
{
    this->Shortcut = Shortcut;
}
void KeyBindingView::setShortcut(Core::Shortcut &&Shortcut)
{
    this->Shortcut = std::move(Shortcut);
}
void KeyBindingView::onHierarchyCreate()
{
    Super::onHierarchyCreate();
    setName("KeyBindingView");
}
//CLASSGEN END REGION

String getKeyNameFromKeyCode(uint64_t key)
{
    //Handle letters and numbers
    static Math::Range numbers(0x30, 0x39); //VK_0 - VK_9
    static Math::Range letters(0x41, 0x5A); //VK_A - VK_Z
    static Math::Range functional(VK_F1, VK_F24);
    static Math::Range numpad(VK_NUMPAD0, VK_NUMPAD9);

    static Math::Range specialKeys(VK_SPACE, VK_HELP);
    static Array<String> specialKeyNames = {
        "Space",
        "PgDn",
        "PgUp",
        "End",
        "Home",
        "Left",
        "Up",
        "Right",
        "Down",
        "Select",
        "Print",
        "Execute",
        "PrtScr",
        "Insert",
        "Delete",
        "Help",
    };

    if (numbers.contains(key))
    {
         return String(1, '0' + numbers.getStartOffset(key));
    }

    if (letters.contains(key))
    {
        return String(1, 'A' + letters.getStartOffset(key));
    }

    if (numpad.contains(key))
    {
        return String("Num ") + String(1, '0' + numpad.getStartOffset(key));
    }

    //Handle functional keys
    if (functional.contains(key))
    {
        return "F" + std::to_string(functional.getStartOffset(key) + 1);
    }

    //Handle special keys
    if (specialKeys.contains(key))
    {
        return specialKeyNames[specialKeys.getStartOffset(key)];
    }

    //Handle other keys
    switch (key)
    {
    case VK_ESCAPE:
        return "Esc";
    case VK_BACK:
        return "Backspace";
    case VK_CLEAR:
        return "Clear";
    case VK_RETURN:
        return "Enter";
    case VK_TAB:
        return "Tab";
    case VK_PAUSE:
        return "Pause";
    case VK_CAPITAL:
        return "CapsLock";
    case VK_LWIN:
        return "LeftWin";
    case VK_RWIN:
        return "RightWin";
    case VK_APPS:
        return "Menu";
    case VK_MULTIPLY:
        return "Num *";
    case VK_ADD:
        return "Num +";
    case VK_SUBTRACT:
        return "Num -";
    case VK_DECIMAL:
        return ".";
    case VK_DIVIDE:
        return "Num /";
    case VK_NUMLOCK:
        return "NumLock";
    case VK_SCROLL:
        return "Scroll";
    case VK_OEM_PLUS:
        return "+";
    case VK_OEM_COMMA:
        return ",";
    case VK_OEM_MINUS:
        return "-";
    case VK_OEM_PERIOD:
        return ".";

    //US OEM keys
    case VK_OEM_1:
        return ";";
    case VK_OEM_2:
        return "/";
    case VK_OEM_3:
        return "`";
    case VK_OEM_4:
        return "[";
    case VK_OEM_5:
        return "\\";
    case VK_OEM_6:
        return "]";
    case VK_OEM_7:
        return "'";
    }

    return String();
}

void KeyBindingView::onKeyPressed(AWindowKeyPressEvent &event)
{
    switch (event.getKey())
    {
    case VK_CONTROL:
        Shortcut.KeyModifier |= Core::KeyModifier::Ctrl;
        return;
    case VK_SHIFT:
        Shortcut.KeyModifier |= Core::KeyModifier::Shift;
        return;
    case VK_MENU:
        Shortcut.KeyModifier |= Core::KeyModifier::Alt;
        return;
    case VK_LWIN:
        Shortcut.KeyModifier |= Core::KeyModifier::Win;
        return;
    }

    String text;
    bool first = true;

    if (Shortcut.KeyModifier)
    {
        text = boost::join(Shortcut.KeyModifier.toStrings(), "+");
    }

    if (!text.empty())
    {
        text.append("+");
    }

    Shortcut.KeyCode = event.getKey();
    setText(text + getKeyNameFromKeyCode(Shortcut.KeyCode));
    
    ShortcutChanged e(*this, Shortcut);
    eventChannel.sendEvent(e);
}

void KeyBindingView::onKeyReleased(AWindowKeyReleaseEvent &event)
{
    switch (event.getKey())
    {
    case VK_CONTROL:
        Shortcut.KeyModifier &= ~Core::KeyModifier::Ctrl;
        return;
    case VK_SHIFT:
        Shortcut.KeyModifier &= ~Core::KeyModifier::Shift;
        return;
    case VK_MENU:
        Shortcut.KeyModifier &= ~Core::KeyModifier::Alt;
        return;
    case VK_LWIN:
        Shortcut.KeyModifier &= ~Core::KeyModifier::Win;
        return;
    }
}

void KeyBindingView::onCharEntered(AWindowKeyCharEvent &event)
{
    //Prevent default behavior
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
