#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include "Foundation"
//CLASSGEN END REGION
#include <Graphics>
#include <Fonts>
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class Label : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Label This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    String Text;
Core::TextAlign TextAlign;
Core::TextWrapping TextWrapping;
public:
    Label();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    String getText() const;
    void setText(String const &Text);
    void setText(String &&Text);
    Core::TextAlign getTextAlign() const;
    void setTextAlign(Core::TextAlign const &TextAlign);
    void setTextAlign(Core::TextAlign &&TextAlign);
    Core::TextWrapping getTextWrapping() const;
    void setTextWrapping(Core::TextWrapping const &TextWrapping);
    void setTextWrapping(Core::TextWrapping &&TextWrapping);
//CLASSGEN END REGION
};*/

template<size_t size>
struct Atlas
{
    APixmap pixmap;
    StaticArray<Math::IntegerRectangle, size> slices;

    Math::Rectangle getUV(size_t index) const
    {
        Math::IntegerRectangle slice = slices[index];
        return Math::Rectangle{
            Math::remap2(slice.Position.getXY<Math::Vector>(), Math::Constants::NullVector, pixmap.getSize().getXY<Math::Vector>()),
            Math::remap2((slice.Size).getXY<Math::Vector>(), Math::Constants::NullVector, pixmap.getSize().getXY<Math::Vector>()),
        };
    }
};

struct TextMetrics
{
    Array<APair<char, Math::IntegerRectangle>> chars;
    Math::IntegerVector size;
    float lineSize = 1;

    Math::Rectangle getNormalizedCharMetrics(size_t index) const
    {
        return Math::Rectangle{
            chars[index].second.Position.getXY<Math::Vector>() / lineSize,
            chars[index].second.Size.getXY<Math::Vector>() / lineSize,
        };
    }
};

class Label : public View
{
    CLASSGEN_GENERATED_REGION_OBJECT
public:
    typedef Label This;
    typedef View Super;
private:
    const Atlas<256> *atlas = nullptr;
    TextMetrics metrics;
    SharedReference<Legacy::Graphics::Mesh> mesh;
    SharedReference<DynamicLabelMaterial> material;
    Core::Font font;
    Core::TextAlign textAlign;
    Core::TextWrapping textWrapping;
    String text;
    AColor color;
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
    virtual SharedReference<DynamicLabelMaterial> const &getMaterial() const;
    virtual void setMaterial(SharedReference<DynamicLabelMaterial> const &material);
    virtual Core::Font const &getFont() const;
    virtual void setFont(Core::Font const &font);
    virtual Core::TextAlign getTextAlign() const;
    virtual void setTextAlign(Core::TextAlign const &textAlign);
    virtual Core::TextWrapping getTextWrapping() const;
    virtual void setTextWrapping(Core::TextWrapping const &textWrapping);
    virtual String const &getText() const;
    virtual void setText(String const &text);
    virtual AColor const &getColor() const;
    virtual void setColor(AColor const &color);
    virtual Math::IntegerVector const &getSize() const;
    virtual void setSize(Math::IntegerVector const &size);
    virtual Math::IntegerVector getContentSize() const;
    CLASSGEN_END_REGION

public:
    typedef Label This;
    typedef View Super;
public: //aliases
private: //fields
    Legacy::Graphics::Texture textTexture;
public: //construction
    Label() { onCreate(); }
    Label(const String &text) { onCreate(); setText(text); }
    virtual ~Label() {}
    void onCreate();
private:
    void UpdateTextTexture();
public:
    virtual void onLoad(ALoadEvent &event);
public:
    virtual void onDraw(AUpdateEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
