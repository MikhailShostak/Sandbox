//CLASSGEN GENERATED REGION: Includes
#include "TextField.gen.h"
#include <MetaObjectSerializationHelper.h>
//CLASSGEN END REGION
#include "Includes/RelativeLayout.gen.h"
#include "UITouchGestureRecognizer.h"
#include <Graphics>
#include <UIDarkTheme>
#include <algorithm>
#include "UIComponent.h"
#include <System>
bool OldFocusSupport = true;
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassImplementation
TextField::TextField()
{
}
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
void TextField::serialize(AJSONObject &object) const
{
    Super::serialize(object);
    object.insert("Text", toJSONValue(Text));
    object.insert("Placeholder", toJSONValue(Placeholder));
}
void TextField::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
    value = AJSONValue();
    object.read("Text", value);
    fromJSONValue(value, Text);
    value = AJSONValue();
    object.read("Placeholder", value);
    fromJSONValue(value, Placeholder);
}
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
String TextField::getText() const
{
    return this->Text;
}
void TextField::setText(String const &Text)
{
    this->Text = Text;
}
void TextField::setText(String &&Text)
{
    this->Text = std::move(Text);
}
String TextField::getPlaceholder() const
{
    return this->Placeholder;
}
void TextField::setPlaceholder(String const &Placeholder)
{
    this->Placeholder = Placeholder;
}
void TextField::setPlaceholder(String &&Placeholder)
{
    this->Placeholder = std::move(Placeholder);
}
//CLASSGEN END REGION
*/

AStaticRun(FieldViewMetaObject)
{
    CLASSGEN_GENERATED_REGION_META_OBJECT
    MetaObjectManager &manager = MetaObjectManager::getInstance();
    MetaObject &object = manager.getMetaObject<TextField>();
    object.serialize = [](const AObject &object, AJSONObject &data) { static_cast<const TextField&>(object).serialize(data); };
    object.deserialize = [](const AJSONObject &data, AObject &object) { static_cast<TextField&>(object).deserialize(data); };
    object.baseObject = &manager.getMetaObject<View>();
    object.registerMetaProperty<TextField, String>("Text", &TextField::getText, &TextField::setText, false);
    object.registerMetaProperty<TextField, UIOffsets>("Border", &TextField::getBorder, &TextField::setBorder, false);
    object.registerMetaProperty<TextField, SharedReference<Legacy::Graphics::Texture>>("BackgroundImage", &TextField::getBackgroundImage, &TextField::setBackgroundImage, false);
    object.registerMetaProperty<TextField, Core::Font>("Font", &TextField::getFont, &TextField::setFont, false);
    object.registerMetaProperty<TextField, Core::TextWrapping>("TextWrapping", &TextField::getTextWrapping, &TextField::setTextWrapping, false);
    object.registerMetaProperty<TextField, Math::IntegerVector>("ContentSize", &TextField::getContentSize, static_cast<void(TextField::*)(Math::IntegerVector const &)>(nullptr), false);
    object.registerMetaProperty<TextField, Math::IntegerRange>("Selection", &TextField::getSelection, &TextField::setSelection, false);
    manager.registerMetaObject("UI.TextField", object);
    CLASSGEN_END_REGION
}

CLASSGEN_GENERATED_REGION_OBJECT
void TextField::serialize(AJSONObject &object) const
{
    Super::serialize(object);
}
void TextField::deserialize(const AJSONObject &object)
{
    Super::deserialize(object);
    AJSONValue value;
}
Math::IntegerRange TextField::getSelection() const
{
    return this->selection;
}
void TextField::setSelection(Math::IntegerRange const &selection)
{
    this->selection = selection;

    lastUpdate = ASystemClock::now();
    caret->show();

    updateSelection();
}
CLASSGEN_END_REGION

TextField::TextField()
{
    ARegisterEventCallback(onFocusOut);
    ARegisterEventCallback(onFocusIn);

    setData({
        OverlayData{ { 0, 0, 0, 0 }, },
        OverlayData{ { 0, 0, 0, 0 }, },
        OverlayData{ { 4, 4, 4, 4 }, },
        OverlayData{ { 4, 4, 4, 4 }, },
    });

    setSizePolicy(SizePolicy::Expanded, SizePolicy::ContentWrapped);

    backgroundView = CreateShared<BorderImageView>();
    backgroundView->setName("BackgroundView");
    backgroundView->setSizePolicy(SizePolicy::Expanded);
    addView(backgroundView);    

    selectionImage = CreateShared<BorderImageView>();
    selectionImage->setName("SelectionImage");
    selectionImage->setVisible(false);
    selectionImage->setSizePolicy(SizePolicy::Fixed);
    selectionImage->setImage(Legacy::Graphics::Texture::getWhiteTexture());
    //selectionImage->setColor(AColor::fromHex(0xFF0099FF));
    selectionImage->setColor(AColor::fromHex(0xFF778811));
    addView(selectionImage);

    label = CreateShared<Label>();
    label->setName("Label");
    label->setSizePolicy(SizePolicy::Expanded);
    addView(label);

    placeholder = CreateShared<Label>();
    placeholder->setName("Placeholder");
    placeholder->setSizePolicy(SizePolicy::Expanded);
    //placeholder->setColor(AColorName::LightGray);
    placeholder->setAffectsParentLayout(false);
    addView(placeholder);

    selectionImage->setSize(Math::IntegerVector{ 1, Core::FontEngine::getInstance().getLineHeight(label->getFont()) });
    selectionImage->setAffectsParentLayout(false);

    caret = CreateShared<ImageView>();
    caret->setName("Caret");
    caret->setImage(Legacy::Graphics::Texture::getWhiteTexture());
    caret->setVisible(false);
    caret->setSize(Math::IntegerVector{ 1, Core::FontEngine::getInstance().getLineHeight(label->getFont()) });
    caret->setAffectsParentLayout(false);
    addView(caret);

    inFocus = false;
    addGestureRecognizer(CreateShared<TouchGestureRecognizer>());
    addGestureRecognizer(CreateShared<MoveGestureRecognizer>());
    addGestureRecognizer(CreateShared<DoubleTouchGestureRecognizer>());
    eventChannel.registerDelegate([this](TouchDownGestureEvent &event) {
        if (!event.isInside())
        {
            return;
        }

        if (!inFocus)
        {
            if(OldFocusSupport)
            {
                getOwner()->getWindow()->setFocus(*this);
            }
            else
            {
                SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
                component->setFocus(*this);
            }
        }
        selectionPoint = event.getPoint() - Math::IntegerVector { getTextPadding().left, getTextPadding().top };
        size_t selectionIndex = Core::FontEngine::getInstance().findIndexAt(getText(), getFont(), label->getTextAlign(), getTextWrapping(), label->getSize().x, selectionPoint);
        setSelection(Math::IntegerRange{ static_cast<int32_t>(selectionIndex), static_cast<int32_t>(selectionIndex) });
        inSelection = true;
        event.accept();
    });
    eventChannel.registerDelegate([this](TouchMoveGestureEvent &event) {
        if (!event.isInside())
        {
            return;
        }

        if (inSelection)
        {
            size_t startSelectionIndex = Core::FontEngine::getInstance().findIndexAt(getText(), getFont(), label->getTextAlign(), getTextWrapping(), label->getSize().x, selectionPoint);
            Math::IntegerVector endSelectionPoint = event.getPoint() - Math::IntegerVector { getTextPadding().left, getTextPadding().top };
            size_t endSelectionIndex = Core::FontEngine::getInstance().findIndexAt(getText(), getFont(), label->getTextAlign(), getTextWrapping(), label->getSize().x, endSelectionPoint);
            inversedSelection = startSelectionIndex > endSelectionIndex;
            setSelection(inversedSelection ? 
                Math::IntegerRange{ static_cast<int32_t>(endSelectionIndex), static_cast<int32_t>(startSelectionIndex) } :
                Math::IntegerRange{ static_cast<int32_t>(startSelectionIndex), static_cast<int32_t>(endSelectionIndex) }
            );
        }
    });
    eventChannel.registerDelegate([this](TouchUpGestureEvent &event) {
        if (inSelection)
        {
            inSelection = false;
        }
    });
    eventChannel.registerDelegate([this](DoubleTouchDownGestureEvent &event) {
        if (!event.isInside())
        {
            return;
        }

        Math::IntegerVector endSelectionPoint = event.getPoint() - Math::IntegerVector { getTextPadding().left, getTextPadding().top };
        size_t newSelectionIndex = Core::FontEngine::getInstance().findIndexAt(getText(), getFont(), label->getTextAlign(), getTextWrapping(), label->getSize().x, endSelectionPoint);
        if (this->selection.lowest == newSelectionIndex)
        {
            selectWordAt(this->selection.lowest);
        }
        else
        {
            selectionPoint = event.getPoint() - Math::IntegerVector { getTextPadding().left, getTextPadding().top };
            setSelection(Math::IntegerRange{ static_cast<int32_t>(newSelectionIndex), static_cast<int32_t>(newSelectionIndex) });
        }
        inSelection = true;

        event.accept();
    });

    eventChannel.registerDelegate([this](AWindowKeyPressEvent &event) {
        onKeyPressed(event);
    });
    eventChannel.registerDelegate([this](AWindowKeyReleaseEvent &event) {
        onKeyReleased(event);
    });
    eventChannel.registerDelegate<AWindowKeyCharEvent>([this](AWindowKeyCharEvent &event) {
        onCharEntered(event);
    });

    ApplyStyle(*this);
}

enum Key
{
    Unknown,

    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z,

    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,

    Minus, /* - */
    Equal, /* = */
    Comma, /* , */
    Period, /* . */
    Semicolon, /* ; */
    Apostrophe, /* ' */
    LeftBracket, /* [ */
    RightBracket, /* ] */
    Slash, /* / */
    Backslash, /* \ */
    GraveAccent, /* ` */

    Num0,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
 
    NumDecimal,
    NumDivide,
    NumMultiply,
    NumSubtract,
    NumAdd,
    NumEnter,
    NumEqual,

    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    F16,
    F17,
    F18,
    F19,
    F20,
    F21,
    F22,
    F23,
    F24,
    F25,

    Up,
    Right,
    Down,
    Left,

    PageUp,
    PageDown,
    
    Home,
    End,

    Space,
    Tab,
    Enter,

    Insert,
    Backspace,
    Delete,

    LeftCommand,
    LeftShift,
    LeftControl,
    LeftAlt,

    RightCommand,
    RightShift,
    RightControl,
    RightAlt,

    CapsLock,
    ScrollLock,
    NumLock,

    PrintScreen,
    Pause,
    Menu,

    Esc,
};

void TextField::onKeyPressed(AWindowKeyPressEvent &event)
{
    switch (Key(event.getKey()))
    {
    case Key::Home: //36: //Home
    {
        setSelection(Math::IntegerRange{ 0, 0 });
        break;
    }
    case Key::End: //35: //End
    {
        size_t lastIndex = label->getText().size();
        setSelection(Math::IntegerRange{ static_cast<int32_t>(lastIndex), static_cast<int32_t>(lastIndex) });
        break;
    }
    case Key::Left: //37: //Left Arrow
    {
        const String &text = label->getText();
        int32_t nextIndex = std::max<int32_t>(selection.lowest - 1, 0);
        setSelection(Math::IntegerRange{ nextIndex, nextIndex });
        break;
    }
    case Key::Right: //39: //Right Arrow
    {
        const String &text = label->getText();
        int32_t nextIndex = std::min<int32_t>(selection.highest + 1, text.size());
        setSelection(Math::IntegerRange{ nextIndex, nextIndex });
        break;
    }
    case Key::Backspace:
    {
        String text = label->getText();
        if (selection.lowest != selection.highest)
        {
            deleteSelectedText();
            break;
        }

        if (selection.lowest == 0)
        {
            break;
        }

        int32_t nextIndex = selection.lowest - 1;
        text = text.substr(0, nextIndex) + text.substr(selection.highest);
        label->setText(text);
        setSelection(Math::IntegerRange{ nextIndex, nextIndex });

        TextEditedEvent e(*this, *this, label->getText());
        eventChannel.sendEvent(e);
        if(OnTextEdit)
        {
            OnTextEdit(label->getText());
        }
        break;
    }
    case Key::Delete: //46: //Delete
    {
        String text = label->getText();
        if (selection.lowest == text.size())
        {
            return;
        }
        else if (selection.lowest != selection.highest)
        {
            deleteSelectedText();
            break;
        }

        int32_t nextIndex = selection.lowest;
        text = text.substr(0, nextIndex) + text.substr(selection.highest - 1);

        label->setText(text);
        setSelection(Math::IntegerRange{ nextIndex, nextIndex });
        
        TextEditedEvent e(*this, *this, label->getText());
        eventChannel.sendEvent(e);
        if(OnTextEdit)
        {
            OnTextEdit(label->getText());
        }
        break;
    }
    case Key::Enter: //13: //Enter
        TextEditFinishedEvent e(*this, *this, label->getText());
        eventChannel.sendEvent(e);
        if(OnTextEditFinish)
        {
            OnTextEditFinish(label->getText());
        }
        break;
    }
}

void TextField::onKeyReleased(AWindowKeyReleaseEvent &event)
{

}

void TextField::onCharEntered(AWindowKeyCharEvent &event)
{
    String text = label->getText();
    bool changed = false;
    switch (event.getSymbol())
    {
    case 0x26: //Ctrl+Z
    {

        break;
    }
    case 0x18: //Ctrl+X
    {
        String clipboardText = text.substr(selection.lowest, selection.getLength());
        Clipboard::setData(clipboardText);
        if (selection.lowest != selection.highest)
        {
            deleteSelectedText();
            break;
        }
        break;
    }
    case 0x3: //Ctrl+C
    {
        String clipboardText = text.substr(selection.lowest, selection.getLength());
        Clipboard::setData(clipboardText);
        break;
    }
    case 0x16: //Ctrl+V
    {
        String clipboardText;
        if (Clipboard::getData(clipboardText))
        {
            text = text.substr(0, selection.lowest) + clipboardText + text.substr(selection.highest);
            int32_t selectionPosition = selection.lowest + clipboardText.size();
            setSelection(Math::IntegerRange{ selectionPosition, selectionPosition });
            changed = true;
        }
        break;
    }
    case '\b':
    {
        if (selection.lowest != selection.highest)
        {
            deleteSelectedText();
            return;
        }

        if (selection.lowest == 0)
        {
            return;
        }

        int32_t nextIndex = selection.lowest - 1;
        text = text.substr(0, nextIndex) + text.substr(selection.highest);
        setSelection(Math::IntegerRange{ nextIndex, nextIndex });
        changed = true;
        break;
    }
    case '\r':
    case '\n':
        break;
    default:
    {
        if (event.getSymbol() < 128 && std::iscntrl(event.getSymbol()))
        {
            //unhandled control symbol
            return;
        }

        if (!filter.empty() && filter.find(event.getSymbol()) != filter.end())
        {
            return;
        }

        text = text.substr(0, selection.lowest) + String(1, event.getSymbol()) + text.substr(selection.highest);
        int32_t nextIndex = selection.lowest + 1;
        setSelection(Math::IntegerRange{ nextIndex, nextIndex });
        changed = true;
        break;
    }
    }
    if (changed)
    {
        label->setText(text);
        TextEditedEvent e(*this, *this, label->getText());
        eventChannel.sendEvent(e);
        if(OnTextEdit)
        {
            OnTextEdit(label->getText());
        }
    }
}

void TextField::deleteSelectedText()
{
    AAssert(selection.getLength() > 0, "Text should be selected");
    int32_t position = selection.lowest;

    //TODO: string API?
    String text = label->getText();
    text = text.substr(0, position) + text.substr(selection.highest);
    setSelection(Math::IntegerRange{ position, position });
    label->setText(text);
    TextEditedEvent e(*this, *this, label->getText());
    eventChannel.sendEvent(e);
    if(OnTextEdit)
    {
        OnTextEdit(label->getText());
    }
}

TextField::TextField(const String &string):
    TextField()
{
    setText(string);
}

TextField::~TextField()
{
    AUnregisterEventCallback(onFocusIn);
    AUnregisterEventCallback(onFocusOut);
}

void TextField::onFocusIn(AFocusInEvent &event)
{
    inFocus = true;
    TextEditStartedEvent e(*this, *this, label->getText());
    eventChannel.sendEvent(e);
    if(OnTextEditStart)
    {
        OnTextEditStart(label->getText());
    }
    if(OldFocusSupport)
    {
        getOwner()->getWindow()->inputEventChannel.registerObserver(eventChannel);
    }
    else
    {
        SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
        component->inputEventChannel.registerObserver(eventChannel);
    }
    placeholder->hide();
}

void TextField::onFocusOut(AFocusOutEvent &event)
{
    if(OldFocusSupport)
    {
        getOwner()->getWindow()->inputEventChannel.unregisterObserver(eventChannel);
    }
    else
    {
        SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
        component->inputEventChannel.unregisterObserver(eventChannel);
    }
    caret->hide();
    selectionImage->hide();
    inFocus = false;
    TextEditFinishedEvent e(*this, *this, label->getText());
    eventChannel.sendEvent(e);
    if(OnTextEditFinish)
    {
        OnTextEditFinish(label->getText());
    }
    if (getText().empty())
    {
        placeholder->show();
    }
}

Math::IntegerVector TextField::getContentSize() const
{
    return (!label->getText().empty() ? label->getContentSize() : placeholder->getContentSize()) + Math::IntegerVector{ getTextPadding().getHorizontalSpace(), getTextPadding().getVerticalSpace() };
}

String const &TextField::getText() const
{
    return label->getText();
}

void TextField::setText(String const &text)
{
    label->setText(text);
    if (label->getText().empty())
    {
        selection = Math::IntegerRange{ 0, 0 };
    }

    if (inFocus)
    {
        lastUpdate = ASystemClock::now();
        caret->show();
    }

    placeholder->setVisible(!inFocus && label->getText().empty());

    updateSelection();
}

Core::Font const &TextField::getFont() const
{
    return label->getFont();
}

void TextField::setFont(Core::Font const &font)
{
    label->setFont(font);
    selectionImage->setSize(Math::IntegerVector{ 1, Core::FontEngine::getInstance().getLineHeight(font) });
    caret->setSize(Math::IntegerVector{ 1, Core::FontEngine::getInstance().getLineHeight(font) });
    updateSelection();
}

SharedReference<Legacy::Graphics::Texture> const &TextField::getBackgroundImage() const
{
    return backgroundView->getImage();
}

void TextField::setBackgroundImage(SharedReference<Legacy::Graphics::Texture> const &backgroundImage)
{
    backgroundView->setImage(backgroundImage);
}

UIOffsets const &TextField::getBorder() const
{
    return backgroundView->getBorder();
}

void TextField::setBorder(UIOffsets const &border)
{
    backgroundView->setBorder(border);
}

Math::Offsets TextField::getTextPadding() const
{
    return getData()[2].Padding;
}

void TextField::setTextPadding(const Math::Offsets &padding)
{
    auto data = getData();
    data[2].Padding = padding;
    data[3].Padding = padding;
    setData(data);
}

Core::TextWrapping TextField::getTextWrapping() const
{
    return label->getTextWrapping();
}

void TextField::setTextWrapping(Core::TextWrapping const &textWrapping)
{
    label->setTextWrapping(textWrapping);
    updateSelection();
}

bool isWordSymbol(char symbol)
{
    return std::isalnum(symbol);
}

void TextField::selectWordAt(size_t index)
{
    const String &text = label->getText();
    if (text.empty())
    {
        return;
    }

    size_t startIndex = ((index < text.size()) && (isWordSymbol(text[index]) || text[index] != ' ') || index == 0) ? index : index - 1;
    size_t endIndex = startIndex + 1;

    while (startIndex > 0)
    {
        --startIndex;
        if (!isWordSymbol(text[startIndex]))
        {
            ++startIndex;
            break;
        }
    }
    while (endIndex < text.size())
    {
        if (!isWordSymbol(text[endIndex]))
        {
            break;
        }
        ++endIndex;
    }

    setSelection(Math::IntegerRange{ static_cast<int32_t>(startIndex), static_cast<int32_t>(endIndex) });
}

void TextField::updateSelection()
{
    if (!inFocus) //TODO: need to support manual selection
    {
        return;
    }

    if (selection.lowest == 0 && selection.highest == 0)
    {
        caret->setPosition(label->getPosition());
        selectionImage->setVisible(false);
        return;
    }

    Math::IntegerVector startPosition = Core::FontEngine::getInstance().findTextPosition(getText(), getFont(), label->getTextAlign(), getTextWrapping(), label->getSize().x, selection.lowest);
    Math::IntegerVector endPosition = Core::FontEngine::getInstance().findTextPosition(getText(), getFont(), label->getTextAlign(), getTextWrapping(), label->getSize().x, selection.highest);
    Math::IntegerVector delta = endPosition - startPosition;
    if (delta.x > 0)
    {
        selectionImage->setPosition(label->getPosition() + Math::Vector{ static_cast<float>(startPosition.x), static_cast<float>(startPosition.y) });
        selectionImage->setSize(Math::IntegerVector{ delta.x, selectionImage->getSize().y });
        selectionImage->setVisible(true);
    }
    else
    {
        selectionImage->setVisible(false);
    }
    caret->setPosition(label->getPosition() + 
        (inversedSelection ?
            Math::Vector{ 
                static_cast<float>(startPosition.x), 
                static_cast<float>(startPosition.y),
                0.0f
            } - Math::Vector{ 1.0f, 0.0f, 0.0f } :
            Math::Vector{
                static_cast<float>(endPosition.x),
                static_cast<float>(endPosition.y),
                0.0f
            }
        )
    );
}

void TextField::onLayout(AUpdateEvent &event)
{
    const bool layout = isNeededLayoutUpdate();
    Super::onLayout(event);
    if (layout)
    {
        updateSelection();
    }
}

void TextField::onUpdate(AUpdateEvent &event)
{
    Super::onUpdate(event);
    if (inFocus)
    {
        if (ASystemClock::now() - lastUpdate > AMilliseconds(GetCaretBlinkTime()))
        {
            lastUpdate = ASystemClock::now();
            caret->setVisible(!caret->isVisible());
        }
    }
}

void TextField::onUnload(AUnloadEvent &event)
{
    Super::onUnload(event);
    if(OldFocusSupport)
    {
        getOwner()->getWindow()->removeFocus(*this);
    }
    else
    {
        SharedReference<GraphicsComponent> component = Core::Application2::getInstance().FindComponent<GraphicsComponent>();
        component->removeFocus(*this);
    }
}

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
