#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include "Foundation"

//CLASSGEN END REGION
#include "Includes/BorderImageView.gen.h"
#include "Includes/Label.gen.h"
#include "Overlay.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class TextField : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef TextField This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    String Text;
String Placeholder;
public:
    TextField();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    String getText() const;
    void setText(String const &Text);
    void setText(String &&Text);
    String getPlaceholder() const;
    void setPlaceholder(String const &Placeholder);
    void setPlaceholder(String &&Placeholder);
//CLASSGEN END REGION
};
*/

class TextField : public UI::Overlay
{
public:
    typedef TextField This;
    typedef UI::Overlay Super;
private:
    Math::IntegerRange selection;
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
    virtual String const &getText() const;
    virtual void setText(String const &text);
    virtual UIOffsets const &getBorder() const;
    virtual void setBorder(UIOffsets const &border);
    virtual SharedReference<Legacy::Graphics::Texture> const &getBackgroundImage() const;
    virtual void setBackgroundImage(SharedReference<Legacy::Graphics::Texture> const &backgroundImage);
    virtual Core::Font const &getFont() const;
    virtual void setFont(Core::Font const &font);
    virtual Core::TextWrapping getTextWrapping() const;
    virtual void setTextWrapping(Core::TextWrapping const &textWrapping);
    virtual Math::IntegerVector getContentSize() const;
    virtual Math::IntegerRange getSelection() const;
    virtual void setSelection(Math::IntegerRange const &selection);
private:
    SharedReference<BorderImageView> backgroundView;
    SharedReference<Legacy::Graphics::Texture> backgroundImage;
    SharedReference<BorderImageView> selectionImage;
    SharedReference<Label> placeholder;
    SharedReference<Label> label;
    SharedReference<ImageView> caret;
    bool inFocus = false;
    bool inSelection = false;
    bool inversedSelection = false;
    Math::IntegerVector selectionPoint = Math::IntegerVector{};
public:
    ADelegate<void(const String &text)> OnTextEditStart;
    ADelegate<void(const String &text)> OnTextEditFinish;
    ADelegate<void(const String &text)> OnTextEdit;
    Set<char> filter;

    TextField();
    TextField(const String &string);
    virtual ~TextField();

    Math::Offsets getTextPadding() const;
    void setTextPadding(const Math::Offsets &padding);

    const String &getPlaceholder() const { return placeholder->getText(); }
    void setPlaceholder(const String &text) { placeholder->setText(text); }
    const AColor &getPlaceholderColor() const { return placeholder->getColor(); }
    void setPlaceholderColor(const AColor &color) { placeholder->setColor(color); }
protected:
    void onFocusIn(AFocusInEvent &event);
    void onFocusOut(AFocusOutEvent &event);
    void onLayout(AUpdateEvent &event) override;
    void onUpdate(AUpdateEvent &event) override;
    void onUnload(AUnloadEvent &event) override;

    virtual void onKeyPressed(AWindowKeyPressEvent &event);
    virtual void onKeyReleased(AWindowKeyReleaseEvent &event);
    virtual void onCharEntered(AWindowKeyCharEvent &event);

    void deleteSelectedText();
    void selectWordAt(size_t index);
private:
    void updateSelection();
    ATimePoint<ASystemClock> lastUpdate;
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
