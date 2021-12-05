#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"
#include "Math"

//CLASSGEN END REGION
#include <Foundation>
#include "Graphics"
#include "Includes/View.gen.h"
#include "Includes/ImageView.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class BorderImageView : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef BorderImageView This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    Graphics::Texture Image;
Math::Offsets Border;
Boolean FillCenter;
Boolean UseOriginalContentSize;
public:
    BorderImageView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Graphics::Texture getImage() const;
    void setImage(Graphics::Texture const &Image);
    void setImage(Graphics::Texture &&Image);
    Math::Offsets getBorder() const;
    void setBorder(Math::Offsets const &Border);
    void setBorder(Math::Offsets &&Border);
    Boolean getFillCenter() const;
    void setFillCenter(Boolean const &FillCenter);
    void setFillCenter(Boolean &&FillCenter);
    Boolean getUseOriginalContentSize() const;
    void setUseOriginalContentSize(Boolean const &UseOriginalContentSize);
    void setUseOriginalContentSize(Boolean &&UseOriginalContentSize);
//CLASSGEN END REGION
};*/

class BorderImageView : public View
{
    CLASSGEN_GENERATED_REGION_OBJECT
public:
    typedef BorderImageView This;
    typedef View Super;
private:
    SharedReference<DynamicImageMaterial> topLeft;
    SharedReference<DynamicImageMaterial> top;
    SharedReference<DynamicImageMaterial> topRight;
    SharedReference<DynamicImageMaterial> left;
    SharedReference<DynamicImageMaterial> center;
    SharedReference<DynamicImageMaterial> right;
    SharedReference<DynamicImageMaterial> bottomLeft;
    SharedReference<DynamicImageMaterial> bottom;
    SharedReference<DynamicImageMaterial> bottomRight;
    UIOffsets border;
    bool fillCenter = true;
    Boolean UseOriginalContentSize = true;
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
    virtual SharedReference<Legacy::Graphics::Texture> const &getImage() const;
    virtual void setImage(SharedReference<Legacy::Graphics::Texture> const &image);
    virtual AColor const &getColor() const;
    virtual void setColor(AColor const &color);
    virtual UIOffsets const &getBorder() const;
    virtual void setBorder(UIOffsets const &border);
    virtual bool const &getFillCenter() const;
    virtual void setFillCenter(bool fillCenter);
    Boolean getUseOriginalContentSize() const;
    void setUseOriginalContentSize(Boolean const &UseOriginalContentSize);
    void setUseOriginalContentSize(Boolean &&UseOriginalContentSize);
    CLASSGEN_END_REGION
public:
    typedef BorderImageView This;
    typedef View Super;
public: //aliases
private: //fields
    SharedReference<Graphics::Texture> image;
public: //construction
    BorderImageView() { onCreate(); }
    virtual ~BorderImageView() {}
    void onCreate();

    Math::IntegerVector getContentSize() const override;
public:
    virtual void onLoad(ALoadEvent &event);
public:
    virtual void onDraw(AUpdateEvent &event);
public:
    virtual void updateOpaque();
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
