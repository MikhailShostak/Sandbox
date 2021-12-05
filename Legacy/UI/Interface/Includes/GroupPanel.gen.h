#pragma once

//CLASSGEN GENERATED REGION: Includes
#include "Graphics"

//CLASSGEN END REGION
#include "Panel.gen.h"
#include "BorderImageView.gen.h"
#include "Label.gen.h"
//CLASSGEN GENERATED REGION: Namespace
namespace UI
//CLASSGEN END REGION
//CLASSGEN GENERATED REGION: NamespaceBegin
{
//CLASSGEN END REGION

//CLASSGEN GENERATED REGION: ClassHeader
class GroupPanel : public UI::Panel
//CLASSGEN END REGION
{
//CLASSGEN GENERATED REGION: ClassBody
public:
    typedef GroupPanel This;
    typedef UI::Panel Super;
    typedef void Interfaces;
public:
    GroupPanel();
#if METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    void serialize(class AJSONObject &object) const;
    void deserialize(const class AJSONObject &object);
#endif //METAOBJECT_SUPPORT || REFLECTION_SUPPORT
    SharedReference<UI::View> header;
        SharedReference<UI::BorderImageView> headerBackground;
        SharedReference<UI::Label> headerLabel;
    SharedReference<UI::View> body;
    void onHierarchyCreate();
//CLASSGEN END REGION
    void onLoad(ALoadEvent &event)
    {
        Super::onLoad(event);

        headerBackground->setImage(Legacy::Graphics::Texture::getWhiteTexture());
        headerBackground->setColor(AColor::BlackColor() * 0.2f);
    }
};

//CLASSGEN GENERATED REGION: NamespaceEnd
}
//CLASSGEN END REGION
