#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "View.gen.h"

//CLASSGEN END REGION
#include "Graphics"
#include "Materials/UIImageMaterial.g.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION
/*
//CLASSGEN GENERATED REGION: ClassHeader
class ImageView : public UI::View
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef ImageView This;
    typedef UI::View Super;
    typedef void Interfaces;
protected:
    Legacy::Graphics::Texture Image;
public:
    ImageView();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    Legacy::Graphics::Texture getImage() const;
    void setImage(Legacy::Graphics::Texture const &Image);
    void setImage(Legacy::Graphics::Texture &&Image);
//CLASSGEN END REGION
};
*/

class ImageView : public View
{
    CLASSGEN_GENERATED_REGION_OBJECT
public:
    typedef ImageView This;
    typedef View Super;
private:
public:
    virtual void serialize(AJSONObject &object) const;
    virtual void deserialize(const AJSONObject &object);
    virtual SharedReference<Legacy::Graphics::Texture> const &getImage() const;
    virtual void setImage(SharedReference<Legacy::Graphics::Texture> const &image);
    virtual AColor const &getColor() const;
    virtual void setColor(AColor const &color);
    virtual Math::IntegerVector getContentSize() const;
    CLASSGEN_END_REGION

    virtual Math::Vector const &getImageOffset() const;
    virtual void setImageOffset(Math::Vector const &offset);
public:
    typedef ImageView This;
    typedef View Super;
public: //aliases
private: //fields
    SharedReference<Legacy::Graphics::Texture> image;
    AColor color;
    Math::IntegerVector contentSize;
    SharedReference<DynamicImageMaterial> material;
public: //construction
    ImageView() { onCreate(); }
    virtual ~ImageView() {}
    void onCreate();
public:
    virtual void onLoad(ALoadEvent &event) override;
    virtual void onUnload(AUnloadEvent &event) override;
public:
    virtual void onDraw(AUpdateEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
