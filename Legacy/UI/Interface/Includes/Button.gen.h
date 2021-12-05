#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Overlay.gen.h"

#include "Foundation"
#include "BorderImageView.gen.h"

//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class Button : public UI::Overlay
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef Button This;
    typedef UI::Overlay Super;
    typedef void Interfaces;
protected:
    SharedReference<Legacy::Graphics::Texture> BackgroundImage;
public:
    Button();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<Legacy::Graphics::Texture> getBackgroundImage() const;
    void setBackgroundImage(SharedReference<Legacy::Graphics::Texture> const &BackgroundImage);
    void setBackgroundImage(SharedReference<Legacy::Graphics::Texture> &&BackgroundImage);
    void updateTexture();
    SharedReference<UI::BorderImageView> background;
    void onHierarchyCreate();
//CLASSGEN END REGION
    ADelegate<void()> OnClick;
    bool touched = false;
    bool initialized = false;
    void onLoad(ALoadEvent &event);
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
